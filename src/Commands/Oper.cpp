/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Oper.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 08:51:54 by nassim            #+#    #+#             */
/*   Updated: 2024/07/03 19:45:11 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"
#include "../../include/Command.hpp"
#include "../../include/Reply.hpp"

std::string	get_name(std::string args)
{
	std::string name;
	size_t		i = 0;
	
	while (args[i] != ' ' && i < args.size())
	{
		name += args[i];
		i++;
	}
	return (name);
}

std::string 	get_pwd(std::string args)
{
	std::string	pwd;
	size_t		i = 0;
	
	while (args[i] != ' ' && i < args.size())
		i++;
	i++;
	while (i < args.size())
	{
		pwd += args[i];
		i++;
	}
	return (pwd);
}

bool	OPER_command(t_serv *server, std::string const & args, int sender_fd)
{
	std::string name = get_name(args);
	std::string pwd = get_pwd(args);
	
	std::cout << "args = " << args << std::endl;
	if (args.empty() || args.size() < 2)
	{
		send_message(server, ERR_NEEDMOREPARAMS(int_to_str(sender_fd), "OPER"), sender_fd);
		return (false);
	}
	if (server->client_map[sender_fd]->isRegistred() == true)
	{
		if (name == server->client_map[sender_fd]->getNickname() || pwd != server->_Pwd)
		{
			send_message(server, ERR_PWDMISMATCH(int_to_str(sender_fd)), sender_fd);
			return (false);
		}
		else
		{
			server->client_map[sender_fd]->set_isOperator(true);
			send_message(server, RPL_YOUREOPER(server->client_map[sender_fd]->getNickname()), sender_fd);
			server->operator_fds.push_back(sender_fd);
			return (true);
		}
	}
	return (false);
}
