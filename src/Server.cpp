/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:43:04 by vtestut           #+#    #+#             */
/*   Updated: 2024/07/03 19:46:13 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

bool    Open = true;

void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		Open = false;
	}
}


void    coreIRC(t_serv *server)
{
	std::cout << BOLDGREEN << "Port is: " << server->_port << std::endl;
	std::cout << "Password is: " << server->_Pwd << RESET << std::endl;
	
	struct sigaction sa = {};
	std::cout << YELLOW << "Initializing server..." << RESET << std::endl;
	if (!initServer(server))
		clear_data(server);
	sa.sa_handler = signal_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGINT, &sa, NULL))
		clear_data(server);
	std::cout << YELLOW << "Initializing client..." << RESET << std::endl;
	initClients(server);
}

bool    initServer(t_serv *server)
{
	server->opt = 1;
	server->server_fd  = socket(AF_INET, SOCK_STREAM, 0);
	if (server->server_fd < 0)
		return (false);
	if (setsockopt(server->server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &server->opt, sizeof(server->opt)) < 0)
		return (false);
	
	server->serv_addr = sockaddr_in();
	server->serv_addr.sin_family = AF_INET;
	server->serv_addr.sin_port = htons(server->_port);
	server->serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(server->server_fd, (struct sockaddr *)&server->serv_addr, sizeof(server->serv_addr)) < 0)
		return (false);
	
	server->size = sizeof(server->serv_addr);
	
	if (listen(server->server_fd, MAX_EVENTS) < 0)
		return (false);
	
	return (true);
}