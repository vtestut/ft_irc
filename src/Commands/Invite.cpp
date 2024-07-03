/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Invite.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 09:53:05 by nassim            #+#    #+#             */
/*   Updated: 2024/07/03 19:44:58 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"
#include "../../include/Command.hpp"
#include "../../include/Reply.hpp"

Channel* getChannel(std::string const & channel_name, t_serv *server) {
    std::map<std::string, Channel*>::iterator it = server->channels.find(channel_name);
    if (it != server->channels.end())
        return it->second;
    else
        return (NULL);
}

Client* getClientFromIrssi(std::string const & nick, t_serv* server) {
    Client* myClient = NULL;

    for (std::map<int, Client*>::iterator it = server->client_map.begin(); it != server->client_map.end(); ++it)
	{
        myClient = it->second;
        if (nick == myClient->getNickname())
		{
            return myClient;
        }
    }
    return (NULL);
}

bool    INVITE_command(t_serv *server, std::string const & args, int sender_fd)
{
    std::string nickname = get_channel_name(args);
    std::string channel_name = get_key(args);

    if (args.empty() || nickname.empty() || channel_name.empty())
	{
        send_message(server, ERR_NEEDMOREPARAMS(server->client_map[sender_fd]->getNickname(), "INVITE"), sender_fd);
   		return (false);
    }
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
    Channel* myChannel = getChannel(channel_name, server);
	
    if (myChannel == NULL)
	{
        send_message(server, ERR_NOSUCHCHANNEL(server->client_map[sender_fd]->getNickname(), channel_name), sender_fd);
        return (false);
    }
    if (myChannel->is_client(sender_fd) == false)
	{
		send_message(server, ERR_NOTONCHANNEL(channel_name, nickname), sender_fd);
		return (false);
	}
    Client* target_client = getClientFromIrssi(nickname, server);
    if (target_client == NULL)
	{
        send_message(server, ERR_NOSUCHNICKCHANNEL(nickname), sender_fd);
        return (false);
    }
    if (myChannel->isInviteOnly() == true && (myChannel->is_operator(sender_fd) == false && server->client_map[sender_fd]->isOperator() == false))
	{
        send_message(server, ERR_CHANOPRIVSNEEDED(server->client_map[sender_fd]->getNickname(), channel_name), sender_fd);
        return (false);
    }
    if (myChannel->is_invited(target_client->get_fd()))
	{
        send_message(server, ERR_CLIENTONCHANNEL(server->client_map[sender_fd]->getNickname(), nickname, channel_name), sender_fd);
        return (false);
    }
    send_message(server, RPL_INVITING(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), server->client_map[sender_fd]->getNickname(), target_client->getNickname(), channel_name), sender_fd);
	myChannel->inviteClient(target_client->get_fd());
    myChannel->inviteClient(sender_fd);
    myChannel->broadcast(INVITE(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), target_client->getNickname(), channel_name), target_client->get_fd());
    std::string invite_msg = "You have been invited to join " + channel_name + " by " + server->client_map[sender_fd]->getNickname();
    std::string sender_name;
    
    for (std::map<int, Client*>::iterator it = server->client_map.begin(); it != server->client_map.end(); it++)
    {
        if (server->client_map[it->first]->get_fd() == sender_fd)
            sender_name = server->client_map[it->first]->getNickname();    
    }
    std::string  comment = target_client->getNickname() + " : "  + invite_msg;
    PRIVMSG_command(server, comment, target_client->get_fd());
    return (true);
}
