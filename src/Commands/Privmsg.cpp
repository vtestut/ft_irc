/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Privmsg.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:23:15 by nassim            #+#    #+#             */
/*   Updated: 2024/07/03 19:44:11 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"
#include "../../include/Command.hpp"
#include "../../include/Reply.hpp"

std::string  get_target(std::string const & args)
{
	size_t pos = args.find(":");
	
	if (pos == std::string::npos)
		return ("");
	return (args.substr(0, pos));
}

std::string  get_message(std::string const & args)
{
	size_t pos = args.find(":");
	
	if (pos == std::string::npos)
		return ("");
	return (args.substr(pos + 1));
}

bool    PRIVMSG_command(t_serv *server, std::string const & args, int sender_fd)
{
	// ecrire /msg <target> <message>
	std::string	target = get_target(args);
	target.erase(std::remove(target.begin(), target.end(), ' '), target.end()); // Supprimer les espaces
	std::string message = get_message(args);
	
	
	if (target.empty()) {
		send_message(server, ERR_NOSUCHNICKCHANNEL(target), sender_fd);
		return (false);
	}
	if (target[0] == '#')
	{
		std::map<std::string, Channel*>::iterator it = server->channels.find(target);

		if (it != server->channels.end())
		{
			Channel *myChannel = it->second;
			if (!myChannel->is_client(sender_fd))
			{
				send_message(server, ERR_NOTONCHANNEL(target, server->client_map[sender_fd]->getNickname()), sender_fd);
				return (false);
			}
			myChannel->broadcast(PRIVMSG2(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "127.0.0.1", target, message), sender_fd);
		}
		else
		{
			send_message(server, ERR_NOSUCHCHANNEL(server->client_map[sender_fd]->getNickname(), target), sender_fd);
			return (false);
		}
	}
	else
	{
		for (std::map<int, Client*>::iterator it = server->client_map.begin(); it != server->client_map.end(); ++it)
		{
			if (server->client_map[it->first]->getNickname() == target)
			{
				send_message(server, PRIVMSG(server->client_map[sender_fd]->getNickname(), target, message), server->client_map[it->first]->get_fd());
				return (true);
			}
		}
		send_message(server, ERR_NOSUCHNICKCHANNEL(target), sender_fd);
		return (false);
	}
	return (true);
}
