/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Topic.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:31:34 by nassim            #+#    #+#             */
/*   Updated: 2024/07/03 19:45:29 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"
#include "../../include/Command.hpp"
#include "../../include/Reply.hpp"

std::string get_topic(std::string const & args)
{
	std::string topic = "";
	
	for (size_t i = 0; i < args.size(); i++)
	{
		if (args[i] == ' ')
		{
			topic = args.substr(i + 1);
			break;
		}
	}
	return (topic);
}

bool	TOPIC_command(t_serv *server, std::string const & args, int sender_fd)
{
	if (args.size() < 2 || args.empty())
	{
		send_message(server, ERR_NEEDMOREPARAMS(int_to_str(sender_fd), "TOPIC"), sender_fd);
		return (false);
	}

	Client* 									target_client = server->client_map[sender_fd];
	Channel 									*myChannel = NULL;
	std::string 								channel_name = get_channel_name(args);

	if (channel_name[0] != '#')
	{
		send_message(server, ERR_BADCHANMASK(channel_name), sender_fd);
        return (false);
	}
		
	std::string 								topic = get_topic(args);
	std::map<std::string, Channel*>::iterator	it = server->channels.find(channel_name);
	
	if (it != server->channels.end())
	{
		myChannel = it->second;
		if (!myChannel->is_client(sender_fd))
		{
			send_message(server, ERR_NOTONCHANNEL(channel_name, server->client_map[sender_fd]->getNickname()), sender_fd);
			return (false);
		}
		if (topic.empty())
		{
			if (myChannel->isTopicSet())
				send_message(server, RPL_TOPIC(target_client->getNickname(), target_client->getClientrname(), "localhost", channel_name, myChannel->getTopic()), sender_fd);
			else
				send_message(server, RPL_NOTOPIC(target_client->getNickname(), target_client->getClientrname(), "localhost", channel_name), sender_fd);
			return (true);
		}
		else
		{
			if (myChannel->isTopicProtected() == true && myChannel->is_operator(sender_fd) == false)
			{
				send_message(server, ERR_CHANOPRIVSNEEDED(server->client_map[sender_fd]->getNickname(), channel_name), sender_fd);
				return (false);
			}
			if (topic.size() <= 1)
			{
				myChannel->unsetTopic();
				myChannel->broadcast(RPL_TOPIC2(target_client->getNickname(), target_client->getClientrname(), "localhost", channel_name, topic), -1);
			}
			else
			{
				myChannel->setTopic(topic);
				myChannel->broadcast(RPL_TOPIC2(target_client->getNickname(), target_client->getClientrname(), "localhost", channel_name, topic), -1);
			}
			return (true);
		}
	}
	else
	{
		send_message(server, ERR_NOSUCHCHANNEL(target_client->getNickname(), channel_name), sender_fd);
		return (false);
	}
	return (true);
}
