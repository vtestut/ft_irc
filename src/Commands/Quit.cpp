/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Quit.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:30:00 by nassim            #+#    #+#             */
/*   Updated: 2024/07/03 19:45:24 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"
#include "../../include/Command.hpp"
#include "../../include/Reply.hpp"

bool	QUIT_command(t_serv *server, std::string const & reason, int sender_fd)
{
	if (reason == ":leaving \r\n")
	{
		send_message(server, QUIT(server->client_map[sender_fd]->getNickname(), reason), sender_fd);
		client_disconnection(server, sender_fd);
		return (false);
	}
	return (true);
}