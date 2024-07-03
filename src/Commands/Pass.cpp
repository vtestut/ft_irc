/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pass.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 09:14:13 by nassim            #+#    #+#             */
/*   Updated: 2024/07/03 19:44:11 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"
#include "../../include/Command.hpp"
#include "../../include/Reply.hpp"

bool    PASS_command(t_serv *server, std::string const & password, int sender_fd)
{
	if (server->client_map[sender_fd]->hasPwd() == true)
	{
		send_message(server, ERR_ALREADYREGISTERED(int_to_str(sender_fd)), sender_fd);
		return (false);
	}
	else if (password.size() == 0)
	{
		send_message(server, ERR_NEEDMOREPARAMS(int_to_str(sender_fd), "PASS"), sender_fd);
		return (false);
	}
	else if (password == server->_Pwd)
		server->client_map[sender_fd]->set_hasPwd(true);
	else  if (password != server->_Pwd)
	{
		send_message(server, ERR_PWDMISMATCH(int_to_str(sender_fd)), sender_fd);
		return (false);
	}
	return (true);
}