/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Kick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:58:24 by nassim            #+#    #+#             */
/*   Updated: 2024/07/03 19:44:11 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"
#include "../../include/Command.hpp"
#include "../../include/Reply.hpp"

std::string get_comment(std::string const & args)
{
	std::string comment;
	
	for (size_t i = 0; i < args.size(); i++)
	{
		if (args[i] == ':')
		{
			comment = args.substr(i + 1);
			break ;
		}
	}
	return (comment);
}

std::string get_nickname(std::string const & args)
{
	std::string nickname;
	size_t      i = 0;

	while (i < args.size() && args[i] != ' ')
		i++;
	i++;
	while (i < args.size() && args[i] != ' ')
	{
		nickname += args[i];
		i++;
	}
	return (nickname);
}

Client*  getClient(std::string channel_name, std::string nick, t_serv   *server)
{
	Client*             myclient;
	
	std::vector<int>    client_fds = server->channels[channel_name]->getclient();

	for (std::vector<int>::iterator it = client_fds.begin(); it != client_fds.end(); ++it)
	{
		int	client_fd = *it;
		myclient = server->client_map.at(client_fd);
		if (nick == myclient->getNickname())
			return (myclient);
	}
	return (NULL);
}

bool	KICK_command(t_serv *server, std::string const & args, int sender_fd)
{
	std::string	channel_name = get_channel_name(args);
	
	std::string	nickname = get_nickname(args);
	if (channel_name[0] != '#')
	{
		send_message(server, ERR_BADCHANMASK(channel_name), sender_fd);
        return (false);
	}
	if (server->channels.find(channel_name) == server->channels.end())
	{
		send_message(server, ERR_NOSUCHCHANNEL( channel_name, channel_name), sender_fd);
		return (false);
	}
	std::string comment = get_comment(args);
	Client		*target_client = getClient(channel_name, nickname, server);

	if (target_client == NULL)
	{
		send_message(server, ERR_NOSUCHNICKCHANNEL(nickname), sender_fd);
		return (false);
	}
	if (channel_name.empty() || nickname.empty())
	{
		send_message(server, ERR_NEEDMOREPARAMS(int_to_str(sender_fd), "KICK"), sender_fd);
		return (false);
	}
	if (server->client_map[sender_fd]->getNickname() == nickname)
	{
		send_message(server, "Cannot kick ourself\r\n", sender_fd);
		return (false);
	}
	if (server->channels[channel_name]->getChannelname() != channel_name)
	{
		send_message(server, ERR_NOSUCHCHANNEL(target_client->getNickname(), channel_name), sender_fd);
		return (false);
	}
	if (server->channels[channel_name]->is_client(target_client->get_fd()) == false)
	{
		send_message(server, ERR_NOTONCHANNEL(channel_name, target_client->getNickname()), sender_fd);
		return (false);
	}
	if (server->channels[channel_name]->is_operator(sender_fd) == false && server->client_map[sender_fd]->isOperator() == false)
	{
		send_message(server, ERR_CHANOPRIVSNEEDED(server->client_map[sender_fd]->getNickname(), channel_name), sender_fd);
		return (false);
	}
	if (server->channels[channel_name]->is_client(sender_fd) == false)
	{
		send_message(server, ERR_CLIENTNOTINCHANNEL(nickname, channel_name), sender_fd);
		return (false);
	}
	if (comment != "")
	{
		server->channels[channel_name]->broadcast(":" + target_client->getNickname() + "!" + server->client_map[sender_fd]->getNickname() + "localhost" + " KICK " + channel_name + " " + nickname + "\r\n", sender_fd);
	}
	else
	{
		server->channels[channel_name]->broadcast(":" + target_client->getNickname() + " KICK " + channel_name + " " + nickname + " :" + comment + "\r\n", sender_fd);
	}
	server->channels[channel_name]->kickClient(target_client->get_fd());
	return (true);
}