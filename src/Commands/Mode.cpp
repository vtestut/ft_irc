/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Mode.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:41:21 by nassim            #+#    #+#             */
/*   Updated: 2024/07/03 19:44:11 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"
#include "../../include/Command.hpp"
#include "../../include/Reply.hpp"

std::string	get_mode(std::string const & args)
{
	std::string mode = "";
	size_t		i = 0;

	while (i < args.size() && args[i] != ' ')
		i++;
	i++;
	while (i < args.size() && args[i] != ' ')
	{
		mode += args[i];
		i++;
	}
	return (mode);
}

std::string	get_str(std::string const & args)
{
	std::string	str = "";
	size_t		i = 0;

	while (i < args.size() && args[i] != ' ')
        i++;
    i++;
    while (i < args.size() && args[i] != ' ')
        i++;
    i++;
    while (i < args.size() && args[i] != ' ') {
        str += args[i];
        i++;
    }
    return (str);
}

bool    MODE_command(t_serv *server, std::string const & args, int sender_fd)
{
    std::string channel_name = get_channel_name(args);
    std::string mode = get_mode(args);
    std::string str = get_str(args);

    if (args.empty())
	{
        send_message(server, ERR_NEEDMOREPARAMS(server->client_map[sender_fd]->getNickname(), "MODE"), sender_fd);
        return (false);
    }
    if (mode == "" || args[0] != '#')
        return (true);
    
    Channel* myChannel = getChannel(channel_name, server);

    if (myChannel == NULL)
	{
        send_message(server, ERR_NOSUCHCHANNEL(server->client_map[sender_fd]->getNickname(), channel_name), sender_fd);
        return (false);
    }
    if (myChannel->is_client(sender_fd) == false)
	{
        send_message(server, ERR_NOTONCHANNEL(channel_name, server->client_map[sender_fd]->getNickname()), sender_fd);
        return (false);
    }
    if (myChannel->is_operator(sender_fd) == false)
	{
        send_message(server, ERR_NOPRIVILEGES(server->client_map[sender_fd]->getNickname()), sender_fd);
        return (false);
    }
    if (mode[0] == '+')
	{
        if (mode[1] == 'i')
		{
            myChannel->setInviteOnly(true);
		    myChannel->broadcast(MODE2(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), channel_name, "+i", "is now invite-only."), -1);
        }
        else if (mode[1] == 't')
		{
            myChannel->setProtectedTopic(true);
		    myChannel->broadcast(MODE2(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), channel_name, "+t", "topic is now protected."), -1);
        }
        else if (mode[1] == 'k')
		{
            if (str == "")
			{
                send_message(server, ERR_NEEDMOREPARAMS(server->client_map[sender_fd]->getNickname(), "MODE"), sender_fd);
                return (false);
            }
            else if (myChannel->isChannelLocked() == true)
			{
                send_message(server, ERR_KEYSET(channel_name), sender_fd);
                return (false);
            }
            else
			{
                myChannel->setChannelHasPwd(true);
                myChannel->setChannelPwd(str);
                myChannel->broadcast(MODE2(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), channel_name, "+k", "is now locked."), -1);
            }
        }
        else if (mode[1] == 'o')
		{
            if (str == "")
			{
                send_message(server, ERR_NEEDMOREPARAMS(server->client_map[sender_fd]->getNickname(), "MODE"), sender_fd);
                return (false);
            }
            Client *client_operator = getClient(myChannel->getChannelname(), str, server);
            if (client_operator == NULL)
			{
                send_message(server, ERR_NOSUCHNICKCHANNEL(str), sender_fd);
                return (false);
            }
            else if (myChannel->is_client(client_operator->get_fd()) == false)
			{
                send_message(server, ERR_NOTONCHANNEL(myChannel->getChannelname(), str), sender_fd);
                return (false);
            }
            myChannel->add_operator_client(client_operator->get_fd());
            std::string comment = client_operator->getNickname() + " is now a channel operator";
            myChannel->broadcast(MODE2(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), channel_name, "+o",  comment), -1);
            return (true);
        }
        else if (mode[1] == 'l')
		{
            if (str == "")
			{
                send_message(server, ERR_NEEDMOREPARAMS(server->client_map[sender_fd]->getNickname(), "MODE"), sender_fd);
                return (false);
            }
            int value = 0;

            value = atoi(str.c_str());
            if (value < 1)
                return (false);
            myChannel->setMaxclientNb(value);
            myChannel->setHasclientLimit(true);
            myChannel->broadcast(MODE2(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), channel_name, "+l", "is now limited to " + str + " clients."), -1);
        }
        else
		{
            send_message(server, ERR_UNKNOWNMODE(mode), sender_fd);
            return (false);
        }
    }
    else if (mode[0] == '-')
	{
        if (mode[1] == 'i')
		{
            myChannel->setInviteOnly(false);
		    myChannel->broadcast(MODE2(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), channel_name, "-i", "is no longer invite-only."), -1);
        }
        else if (mode[1] == 't')
		{
            myChannel->setProtectedTopic(false);
		    myChannel->broadcast(MODE2(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), channel_name, "-t", "topic is no longer protected."), -1);
        }
        else if (mode[1] == 'k')
		{
            myChannel->setChannelPwd("");
            myChannel->setChannelHasPwd(false);
            myChannel->broadcast(MODE2(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), channel_name, "-k", "is no longer locked."), -1);
        }
        else if (mode[1] == 'o')
		{
            if (str == "") 
			{    
				send_message(server, ERR_NEEDMOREPARAMS(server->client_map[sender_fd]->getNickname(), "MODE"), sender_fd);
                return (false);
            }
			
            Client *client_operator = getClient(myChannel->getChannelname(), str, server);
			
            if (client_operator == NULL)
			{
                send_message(server, ERR_NOSUCHNICKCHANNEL(str), sender_fd);
                return (false);
            }
            else if (myChannel->is_client(client_operator->get_fd()) == false)
			{
                send_message(server, ERR_NOTONCHANNEL(myChannel->getChannelname(), str), sender_fd);
                return (false);
            }
            std::string comment = client_operator->getNickname() + " is not a channel operator anymore";
            myChannel->del_operator_client(client_operator->get_fd());
            myChannel->broadcast(MODE2(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), channel_name, "-o", comment), -1);
            return (true);
        }
        else if (mode[1] == 'l')
		{
            myChannel->setHasclientLimit(false);
            myChannel->broadcast(MODE2(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), channel_name, "-l", "is no longer limited in members."), -1);
        }
        else
		{
            send_message(server, ERR_UNKNOWNMODE(mode), sender_fd);
            return (false);
        }
    }
    else
	{
        send_message(server, ERR_UNKNOWNMODE(mode), sender_fd);
        return (false);
    }
   return (true);
}
