/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handleClientEvents.cpp                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:15:41 by vtestut           #+#    #+#             */
/*   Updated: 2024/07/03 19:45:51 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"
#include "../include/Reply.hpp"

void	initClients(t_serv *server)
{
	int	nb_events = 0;
	
	server->epoll.fd = epoll_create1(0);
	if (server->epoll.fd < 0)
		clear_data(server);
	server->epoll.event.events = EPOLLIN;
	server->epoll.event.data.fd = server->server_fd;
	if (epoll_ctl(server->epoll.fd, EPOLL_CTL_ADD, server->server_fd, &server->epoll.event) < 0)
	{
		clear_data(server);
	}
	
	while (Open)
	{
		nb_events = epoll_wait(server->epoll.fd, server->epoll.events, MAX_EVENTS, -1);
		if (nb_events < 0)
			clear_data(server);
		for (int i = 0; i < nb_events; i++)
			handleClientEvents(server, i);
	}
}

void 	client_connection(t_serv *server)
{
		struct sockaddr_in socket_new_con = sockaddr_in();
		struct epoll_event event_new_con = epoll_event();
		socklen_t socket_new_con_len = sizeof(socket_new_con);
	
		server->new_fd = accept(server->server_fd, (struct sockaddr *)&socket_new_con, &socket_new_con_len);
		if (server->new_fd < 0)
			clear_data(server);

		Client *new_client = new Client(server->new_fd);
		server->client_map.insert(std::pair<int, Client*>(server->new_fd, new_client));
		server->open_fds.push_back(server->new_fd);
		event_new_con.events = EPOLLIN | EPOLLRDHUP;
		event_new_con.data.fd = server->new_fd;
		if (epoll_ctl(server->epoll.fd, EPOLL_CTL_ADD, server->new_fd, &event_new_con) < 0)
			clear_data(server);
}

void	client_disconnection(t_serv *server, int disc_fd)
{
    epoll_ctl(server->epoll.fd, EPOLL_CTL_DEL, disc_fd, &server->epoll.event);
    if (disc_fd > -1)
        close(disc_fd);

    t_client::iterator client_it = server->client_map.find(disc_fd);
    if (client_it != server->client_map.end())
    {
        close(disc_fd);

        if (client_it->second)
            delete client_it->second;

        server->client_map.erase(client_it);
    }

    std::vector<int>::iterator it = server->open_fds.begin();
    while (it != server->open_fds.end())
    {
        if (*it == disc_fd) {
            it = server->open_fds.erase(it);
            break;
        }
        else
            ++it;
    }
}

void	handleClientEvents(t_serv *server, int i)
{
	const int client_fd = find_client_fd(server->epoll.events[i].data.fd, server);
	
	if (server->epoll.events[i].data.fd == server->server_fd)
		client_connection(server);
	if ((server->epoll.events[i].events & EPOLLERR) || (server->epoll.events[i].events & EPOLLHUP)
		|| (server->epoll.events[i].events & EPOLLRDHUP) || !(server->epoll.events[i].events & EPOLLIN))
		client_disconnection(server, server->epoll.events[i].data.fd);
	else if (client_fd != -1)
		receive_byts(server, i);
}