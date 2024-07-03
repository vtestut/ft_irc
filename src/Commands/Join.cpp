/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 10:22:59 by nassim            #+#    #+#             */
/*   Updated: 2024/07/03 19:44:11 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"
#include "../../include/Command.hpp"
#include "../../include/Reply.hpp"

std::string    get_channel_name(std::string const & args)
{
    std::string	channel_name;
	
    for (size_t i = 0; i < args.size(); i++) {
        if (args[i] == ' ')
            break;
        channel_name += args[i];
    }
    return (channel_name);
}

std::string get_key(std::string const & args)
{
    std::string key = "";
	
    for (size_t i = 0; i < args.size(); i++) {
        if (args[i] == ' ') {
            key = args.substr(i + 1);
            break;
        }
    }
    return (key);
}

void print_names(t_serv *server, std::string const & channel_name, int sender_fd)
{
    Client* target_client = server->client_map[sender_fd];
    Channel* myChannel = getChannel(channel_name, server);

    if (myChannel == NULL)
        return;

    std::string clients_info = "";

    const std::vector<int>& client_fds = myChannel->getclient();

    for (size_t i = 0; i < client_fds.size(); ++i)
	{
        int client_fd = client_fds[i];

        if (client_fd <= 0 || client_fd > MAX_EVENTS)
            break;

        Client* client = server->client_map[client_fd];

        if (myChannel->is_operator(client_fd) || client->isOperator())
            clients_info += "@";

        clients_info += client->getNickname();

        if (i < client_fds.size() - 1)
            clients_info += " ";
    }
    send_message(server, RPL_NAMREPLY(channel_name, target_client->getNickname(), target_client->getClientrname(), "127.0.0.1", clients_info), sender_fd);
    send_message(server, RPL_ENDOFNAMES(channel_name, target_client->getNickname(), target_client->getClientrname(), "127.0.0.1"), sender_fd);
}

bool    JOIN_command(t_serv *server, std::string const & args, int sender_fd)
{
    if (args.empty())
	{
        send_message(server, ERR_NEEDMOREPARAMS(int_to_str(sender_fd), "JOIN"), sender_fd);
        return (false);
    }
    std::string channel_name = get_channel_name(args);
    
    channel_name.erase(std::remove(channel_name.begin(), channel_name.end(), ' '), channel_name.end()); // Supprimer les espaces
    std::string key = get_key(args);
    Channel *myChannel = NULL;

    if (args[0] != '#')
	{
        send_message(server, ERR_BADCHANMASK(channel_name), sender_fd);
        return (false);
    }
    else
	{
        std::map<std::string, Channel*>::iterator it = server->channels.find(channel_name);
        if (it != server->channels.end())
		{
            myChannel = it->second;
            if (myChannel->isInviteOnly() == true && myChannel->is_invited(sender_fd) == false)
			{
                send_message(server, ERR_INVITEONLYCHAN(server->client_map[sender_fd]->getNickname(), channel_name), sender_fd);
                return (false);
            }
            if (myChannel->hasclientLimit() == true && myChannel->getNbclients() >= myChannel->getMaxclientnb())
            {
                send_message(server, ERR_CHANNELISFULL(server->client_map[sender_fd]->getNickname(), channel_name), sender_fd);
                return (false);
            }
            if (myChannel->getChannelPwd() != key)
			{
                send_message(server, ERR_BADCHANNELKEY(server->client_map[sender_fd]->getNickname(), channel_name), sender_fd);
                return (false);
            }
            if (myChannel->is_client(sender_fd))
                return (true);
            myChannel->addClient(sender_fd);
            myChannel->incrementLimit();
        }
        else {
            Channel *new_channel = new Channel(channel_name, sender_fd);
            if (!key.empty()) {
                new_channel->setChannelPwd(key);
                new_channel->setChannelHasPwd(true);
            }
            send_message(server, CREATEDCHANNEL(channel_name), sender_fd);
            server->channels[channel_name] = new_channel;
            myChannel = new_channel;
            myChannel->addClient(sender_fd);
            myChannel->incrementLimit();
        }
    }
    myChannel->broadcast(JOIN(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "127.0.0.1", channel_name), -1);
    if (myChannel->isTopicSet() == true)
        send_message(server, RPL_TOPIC(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "127.0.0.1", channel_name, myChannel->getTopic()), sender_fd);
    print_names(server, channel_name, sender_fd);
    return true;
}