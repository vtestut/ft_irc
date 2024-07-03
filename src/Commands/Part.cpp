/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Part.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:06:50 by nassim            #+#    #+#             */
/*   Updated: 2024/07/03 19:44:11 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"
#include "../../include/Command.hpp"
#include "../../include/Reply.hpp"

std::string get_reason(std::string const & args)
{
	std::string reason;
	
	for (size_t i = 0; i < args.size(); i++)
	{
		if (args[i] == ':')
		{
			reason = args.substr(i + 1);
			break;
		}
	}
	return (reason);
}

bool	PART_command(t_serv *server, std::string const & args, int sender_fd)
{
	if (args.empty())
	{
		send_message(server, ERR_NEEDMOREPARAMS(int_to_str(sender_fd), "PART"), sender_fd);
		return (false);
	}
	
	std::string channel_name = get_channel_name(args);
	std::string reason = get_reason(args);
	
	if (channel_name[0] != '#')
	{
		send_message(server, ERR_BADCHANMASK(channel_name), sender_fd);
        return (false);
	}
	
	channel_name.erase(std::remove(channel_name.begin(), channel_name.end(), ' '), channel_name.end());
	
	std::map<std::string, Channel*>::iterator it = server->channels.find(channel_name);
	
	if (it != server->channels.end())
	{
		Channel *myChannel = it->second;
		
		if (!myChannel->is_client(sender_fd))
		{
			send_message(server, ERR_NOTONCHANNEL(channel_name, server->client_map[sender_fd]->getNickname()), sender_fd);
			return (false);
		}
		if (reason.empty())
		{
			myChannel->broadcast(PART_WOREASON(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "127.0.0.1", channel_name), -1);
		}
		else
		{
			myChannel->broadcast(PART_WREASON(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "127.0.0.1", channel_name, reason), -1);
		}
		myChannel->part(sender_fd);
		if (myChannel->getclient().empty())
		{
			delete (myChannel);
			server->channels.erase(it);
		}
		return (true);
	}
	else
	{
		send_message(server, ERR_NOSUCHCHANNEL(server->client_map[sender_fd]->getNickname(), channel_name), sender_fd);
		return (false);
	}
	return (true);
}
