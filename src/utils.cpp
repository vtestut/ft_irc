/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:00:35 by vtestut           #+#    #+#             */
/*   Updated: 2024/07/03 19:46:17 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void	clear_data(t_serv *server)
{
	if (server->server_fd > -1)
	{
		close(server->server_fd);
		server->server_fd = -1;
	}
	if (server->new_fd > -1)
	{
		close(server->new_fd);
		server->new_fd = -1;
	}
	if (server->epoll.fd > -1)
		close(server->epoll.fd);
	for (int i = 0; i < server->epoll.nb_events; ++i) {
		close(server->epoll.events[i].data.fd);
	}
	for (std::map<int, Client*>::iterator it = server->client_map.begin(); it != server->client_map.end(); ++it)
	{
			delete it->second;
	}
	for (t_channels::iterator it_channels = server->channels.begin(); it_channels != server->channels.end(); it_channels++)
		delete it_channels->second;
	shutdown(server->server_fd, SHUT_RDWR);
	throw std::runtime_error("Data Cleaned");
}

int find_client_fd(int fd, t_serv *server)
{
	for (std::map<int, Client*>::iterator it = server->client_map.begin(); it != server->client_map.end(); ++it)
	{
		if (it->first == fd)
			return (it->first);
	}
	return (-1);
}

void	gethostname()
{
	char hostname[128];
	gethostname(hostname, 128);
	std::cout << PURPLE << "Hostname : " << hostname << RESET << std::endl;
}

std::string	int_to_str(int n)
{
	std::stringstream ss;

	ss << n;
	return  ss.str();
}

