/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   User.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:33:43 by nassim            #+#    #+#             */
/*   Updated: 2024/07/03 19:45:38 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"
#include "../../include/Command.hpp"
#include "../../include/Reply.hpp"

std::string	get_clientname(std::string args)
{
	std::string clientname;
	size_t      i = 0;
    
	while (args[i] != ' ' && i < args.size())
	{
		clientname += args[i];
		i++;
	}
	return (clientname);
}

std::string	get_realname(std::string args)
{
	std::string realname;
	size_t      i = 0;
    
	while (args[i] != ':' && i < args.size())
		i++;
	i++;
	while (i < args.size())
	{
		realname += args[i];
		i++;
	}
	return (realname);
}

bool	USER_command(t_serv *server, std::string const & args, int sender_fd)
{
	std::string clientname = get_clientname(args);
	std::string realname = get_realname(args);

	/* Check si mot de pass incorrect */
	if (server->client_map[sender_fd]->hasPwd() == false)
    {
		if (server->client_map[sender_fd]->hasNickname() == true)
			send_message(server, ERR_NOPRIVILEGES(int_to_str(sender_fd)), sender_fd);
		return (false);
	}
	if (args.empty())
    {
		if (server->client_map[sender_fd]->hasclientname() == true)
			send_message(server, ERR_NEEDMOREPARAMS(int_to_str(sender_fd), "CLIENT"), sender_fd);
		return (false);
	}
	if (server->client_map[sender_fd]->hasclientname() == true)
	{
		send_message(server, ERR_ALREADYREGISTERED(int_to_str(sender_fd)), sender_fd);
		return (false);
	}

	/* Set the clientname */
	server->client_map[sender_fd]->setClientname(clientname);
	server->client_map[sender_fd]->setRealName(realname);
	server->client_map[sender_fd]->set_Hasclientname(true);
	if (server->client_map[sender_fd]->hasNickname() == true && server->client_map[sender_fd]->hasPwd() == true && server->client_map[sender_fd]->isRegistred() == false)
	{
		server->client_map[sender_fd]->set_isRegistred(true);
		send_message(server, RPL_WELCOME(server->client_map[sender_fd]->getNickname(), clientname, int_to_str(server->_port), LOCAL_HOST), sender_fd);
	}
	return (true);
}
