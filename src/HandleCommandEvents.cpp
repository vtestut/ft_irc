/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HandleCommandEvents.cpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:41:43 by vtestut           #+#    #+#             */
/*   Updated: 2024/07/03 19:45:56 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/Command.hpp"
#include "../include/Reply.hpp"

bool	send_message(t_serv *server, std::string const & message, int sender_fd)
{
	(void) server;
	std::string tmp = message;
	if (tmp.size() > 510)
		tmp = tmp.substr(0, 510) + "\r\n";
	send(sender_fd, tmp.c_str(), tmp.size(), 0);
	std::cout << MAGENTA << "message sent: " << tmp << RESET << std::endl;
	return (true);
}

void    execute_commands(t_serv *server, std::vector<std::pair<std::string, std::string> > commands, int sender_fd)
{
	print_commandsargs(commands);
    for (size_t i = 0; i < commands.size(); i++)
	{
		std::pair<std::string, std::string> command_pair = commands[i];
		std::cout << "Command[" << i << "].first = " << command_pair.first << std::endl;
        std::cout << "Command[" << i << "].second = " << command_pair.second << std::endl;
		
        if (commands[i].first == "PASS")
		{
			if (PASS_command(server, commands[i].second, sender_fd) == false) {
				client_disconnection(server, sender_fd);
				break ;
			}
		}
        else if (commands[i].first == "NICK")
		{
			if (check_pwd(server, sender_fd) == false)
			{
				client_disconnection(server, sender_fd);
				break ;
			}
			NICK_command(server, commands[i].second, sender_fd);
		}
		else if (commands[i].first == "USER")
			USER_command(server, commands[i].second, sender_fd);
		else if (commands[i].first == "PING")
			PING_command(server, commands[i].second, sender_fd);
		else if (commands[i].first == "OPER")
			OPER_command(server, commands[i].second, sender_fd);
		else if (commands[i].first == "QUIT")
			QUIT_command(server, commands[i].second, sender_fd);
		else if (commands[i].first == "JOIN")
			JOIN_command(server, commands[i].second, sender_fd);
		else if (commands[i].first == "PRIVMSG")
			PRIVMSG_command(server, commands[i].second, sender_fd);
		else if (commands[i].first == "KICK")
		{
			KICK_command(server, commands[i].second, sender_fd);
		}
		else if (commands[i].first == "PART")
			PART_command(server, commands[i].second, sender_fd);
		else if (commands[i].first == "TOPIC")
			TOPIC_command(server, commands[i].second, sender_fd);
		else if (commands[i].first == "INVITE")
			INVITE_command(server, commands[i].second, sender_fd);
		else if (commands[i].first == "MODE")
			MODE_command(server, commands[i].second, sender_fd);
		else
			UNKNOWN_command(server, commands[i].first, sender_fd);
    }
}

void	receive_byts(t_serv *server, int i)
{
	int		sender_fd = server->epoll.events[i].data.fd;
	char	buffer[BUFFER_SIZE];
	int		read_bytes = recv(sender_fd, buffer, BUFFER_SIZE, 0);
	
	if (read_bytes <= 0)
		client_disconnection(server,sender_fd);
	else
	{
		std::string new_data(buffer, read_bytes);
		server->client_map[sender_fd]->append_partial_data(new_data);
		size_t pos;
		while ((pos = server->client_map[sender_fd]->getPartialData().find("\r\n")) != std::string::npos)
		{
			std::string	command = server->client_map[sender_fd]->getPartialData().substr(0, pos + 2);
			std::vector<std::pair<std::string, std::string> > commands = server->client_map[sender_fd]->splitBuffer(command);
			execute_commands(server, commands, sender_fd);
			try
			{
				Client *client = server->client_map.at(sender_fd);
				client->setPartialdata(client->getPartialData().substr(pos +2));
			}
			catch (const std::out_of_range & oor)
			{
				std::cerr << BOLDRED << "Inexistant client with fd: " << sender_fd << RESET << std::endl;
				break;
			}
		}
	}
}