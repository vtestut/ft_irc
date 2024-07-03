/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:17:41 by vtestut           #+#    #+#             */
/*   Updated: 2024/07/03 19:44:51 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <iomanip>
# include <map>
# include <vector>
# include "Client.hpp"
# include "Channel.hpp"
# include "Irc.hpp"
# include "Colors.hpp"

struct Server_operator
{
	std::string	name;
	std::string	host;
	std::string	password;
};


class Client;

class Channel;

typedef std::map<int, Client*>	t_client;
typedef std::map<std::string, Channel*> t_channels;

typedef struct s_epoll
{
	int					fd;
	int					nb_events;
	struct epoll_event event;
	struct epoll_event events[MAX_EVENTS];
}	t_epoll;


typedef struct s_serv
{
	int					_port;
	std::string			_Pwd;
	int					server_fd;
	struct sockaddr_in serv_addr;
	socklen_t			size;
	int					opt;
	int					new_fd;
	
	std::vector<int>	open_fds;
	std::vector<int>	operator_fds;
	
	t_epoll				epoll;
	t_client			client_map;
	t_channels			channels;
}	t_serv;

bool	parsing(std::string & port, std::string & pwd);
bool	is_valid_port(std::string const & port);
bool	is_valid_pwd(std::string const & pwd);

void	coreIRC(t_serv *server);
bool	initServer(t_serv *server);
void	initClients(t_serv *server);
void	handleClientEvents(t_serv *server, int i);
void	client_connection(t_serv *server);
void	client_disconnection(t_serv *server, int fd);
void	receive_byts(t_serv *server, int i);
void	execute_commands(t_serv *server, std::vector<std::pair<std::string, std::string> > commands, int sender_fd);

void	clear_data(t_serv	*server);

void	signal_handler(int signal);

void	print_commandsargs(std::vector<std::pair<std::string, std::string> > commands);
void	print_client(std::map<int, Client*> clients_map);
void	print_channel(std::map<std::string, Channel*> channels_map);
void	print_vector(std::vector<int> fd);
void	print_epoll_status(t_serv *server, int i);
void	Hello_IRC(t_serv *server);
std::string	welcome_msg();

bool		send_message(t_serv *server, std::string const & message, int sender_fd);

int			find_client_fd(int fd, t_serv *server);
std::string	int_to_str(int n);

