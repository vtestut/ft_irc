/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ping.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:17:22 by nassim            #+#    #+#             */
/*   Updated: 2024/07/03 19:45:18 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"
#include "../../include/Command.hpp"
#include "../../include/Reply.hpp"

bool	PING_command(t_serv *server, std::string const & args, int sender_fd)
{
	if (server->client_map[sender_fd]->isRegistred() == false)
	{
		if (args.empty())
			send_message(server, PING(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), ""), sender_fd);
		else
			send_message(server, PING(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), args), sender_fd);
	}
	else
	{
		if (args.empty())
			send_message(server, PONG(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), ""), sender_fd);
		else
			send_message(server, PONG(client_id(server->client_map[sender_fd]->getNickname(), server->client_map[sender_fd]->getClientrname(), "localhost"), args), sender_fd);
	}
	return (true);
}
