/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrintFunctions.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:21:24 by vtestut           #+#    #+#             */
/*   Updated: 2024/07/03 19:46:09 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

void	print_commandsargs(std::vector<std::pair<std::string, std::string> > commands)
{
	for (size_t i = 0; i < commands.size(); i++)
	{
		std::cout << "command: '" << commands[i].first << "'" << std::endl;
		std::cout << "args: '" << commands[i].second << "'" << std::endl; 
	}
}

void	print_vector(std::vector<int> fd)
{
	for (std::vector<int>::iterator it = fd.begin(); it != fd.end(); ++it)
		std::cout << "fd is: " << *it << std::endl;
}

void	print_client(std::map<int, Client*> clients_map)
{
	for (std::map<int, Client*>::iterator it = clients_map.begin(); it != clients_map.end(); ++it)
	{
		std::cout << "fd is: " << it->first << " client is: " << it->second << std::endl;
	}
}

void	print_channel(std::map<std::string, Channel*> channel_map)
{
	for (std::map<std::string, Channel*>::iterator it = channel_map.begin(); it != channel_map.end(); ++it)
	{
		std::cout << "channel_name is: " << it->first << " and the Channel is: " << it->second <<std::endl;
	}
}

void	print_epoll_status(t_serv *server, int i)
{
		std::cout << "fd: " << server->epoll.events[i].data.fd << std::endl;
		std::cout << "events: " << server->epoll.events[i].events << std::endl;
		std::cout << "EPOLLIN: " << EPOLLIN << std::endl;
		std::cout << "EPOLLRDHUP: " << EPOLLRDHUP << std::endl;
		std::cout << "EPOLLERR: " << EPOLLERR << std::endl;
		std::cout << "EPOLLHUP: " << EPOLLHUP << std::endl;
		std::cout << "EPOLLET: " << EPOLLET << std::endl;
		std::cout << "EPOLLONESHOT: " << EPOLLONESHOT << std::endl;
		std::cout << "EPOLLPRI: " << EPOLLPRI << std::endl;
		std::cout << "EPOLLOUT: " << EPOLLOUT << std::endl;
		std::cout << "EPOLLWAKEUP: " << EPOLLWAKEUP << std::endl;
		std::cout << "EPOLLEXCLUSIVE: " << EPOLLEXCLUSIVE << std::endl;
		std::cout << "EPOLL_CLOEXEC: " << EPOLL_CLOEXEC << std::endl;
		std::cout << "EPOLL_CTL_ADD: " << EPOLL_CTL_ADD << std::endl;
		std::cout << "EPOLL_CTL_MOD: " << EPOLL_CTL_MOD << std::endl;
		std::cout << "EPOLL_CTL_DEL: " << EPOLL_CTL_DEL << std::endl;
		std::cout << "EPOLL_CLOEXEC: " << EPOLL_CLOEXEC << std::endl;
		std::cout << "EPOLL_CLOEXEC: " << EPOLL_CLOEXEC << std::endl;
		std::cout << "EPOLL_CLOEXEC: " << EPOLL_CLOEXEC << std::endl;
		std::cout << "EPOLL_CLOEXEC: " << EPOLL_CLOEXEC << std::endl;
		std::cout << "EPOLL_CLOEXEC: " << EPOLL_CLOEXEC << std::endl;
		std::cout << "EPOLL_CLOEXEC: " << EPOLL_CLOEXEC << std::endl;
		std::cout << "EPOLL_CLOEXEC: " << EPOLL_CLOEXEC << std::endl;
}