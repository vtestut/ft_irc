/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Nick.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:41:44 by nassim            #+#    #+#             */
/*   Updated: 2024/07/03 19:45:07 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"
#include "../../include/Command.hpp"
#include "../../include/Reply.hpp"

bool	check_pwd(t_serv *server, int sender_fd)
{
	if (!server->client_map[sender_fd]->hasPwd()) {
		send_message(server, ERR_NEEDMOREPARAMS(int_to_str(sender_fd), "PASS"), sender_fd);
		return (false);
	}
	return (true);
}

bool    NICK_command(t_serv *server, std::string nickname, int sender_fd)
{
	if (nickname.empty())
	{
		if (server->client_map[sender_fd]->hasNickname())
			send_message(server, ERR_NONICKNAMEGIVEN(server->client_map[sender_fd]->getNickname()), sender_fd);
		else
			send_message(server, ERR_NONICKNAMEGIVEN(int_to_str(sender_fd)), sender_fd);
		return (false);
	}

	char firstChar = nickname[0];
	if (!(isalpha(firstChar) || firstChar == '[' || firstChar == ']' || firstChar == '{' || firstChar == '}' ||  firstChar == '\\' || firstChar == '|'))
	{
		if (server->client_map[sender_fd]->hasNickname())
			send_message(server, ERR_ERRONEUSNICKNAME(int_to_str(sender_fd), nickname), sender_fd);
		else
			send_message(server, ERR_ERRONEUSNICKNAME(int_to_str(sender_fd), nickname), sender_fd);
		return (false);
	}
	
	for (size_t i = 0; i < server->open_fds.size(); i++)
	{
		if (server->client_map[server->open_fds[i]]->getNickname() == nickname)
		{
			if (server->client_map[sender_fd]->hasNickname() == true)
			{
				send_message(server, ERR_NICKNAMEINUSE(int_to_str(sender_fd), nickname), sender_fd);
				return (false);
			}
			nickname = nickname + "_";
			break;
		}
	}

	if (server->client_map[sender_fd]->hasNickname() == true)
	{
		for (size_t i = 0; i <= server->open_fds.size(); i++)
		{
			if (server->client_map[server->open_fds[i]]->isRegistred() == true)
			{
				send_message(server, NICK(server->client_map[sender_fd]->getNickname(), "client", LOCAL_HOST, nickname), sender_fd);
				server->client_map[sender_fd]->setNickname(nickname);
				return (true);
			}
		}
	}
	server->client_map[sender_fd]->setNickname(nickname);
	server->client_map[sender_fd]->set_hasNickname(true);
	if (server->client_map[sender_fd]->hasclientname() == true && server->client_map[sender_fd]->hasPwd() == true && server->client_map[sender_fd]->isRegistred() == false)
	{
		server->client_map[sender_fd]->set_isRegistred(true);
		send_message(server, RPL_WELCOME(nickname, server->client_map[sender_fd]->getClientrname(), int_to_str(server->_port), LOCAL_HOST), sender_fd);
	}
	return (true);
}