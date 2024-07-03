/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Command.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 10:32:31 by vtestut           #+#    #+#             */
/*   Updated: 2024/07/03 19:44:40 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Irc.hpp"
# include "Server.hpp"

bool 	    PASS_command(t_serv *server, std::string const & password, int sender_fd);
bool        NICK_command(t_serv *server, std::string nickname, int sender_fd);
bool	    USER_command(t_serv *server, std::string const & clientname, int sender_fd);
bool	    UNKNOWN_command(t_serv *server, std::string const & command, int sender_fd);
bool	    PING_command(t_serv *server, std::string const & args, int sender_fd);
bool	    OPER_command(t_serv *server, std::string const & args, int sender_fd);
bool	    QUIT_command(t_serv *server, std::string const & reason, int sender_fd);
bool        PRIVMSG_command(t_serv *server, std::string const & args, int sender_fd);
bool	    JOIN_command(t_serv *server, std::string const & args, int sender_fd);
bool	    PART_command(t_serv *server, std::string const & args, int sender_fd);
bool        KICK_command(t_serv *server, std::string const & args, int sender_fd);
bool	    TOPIC_command(t_serv *server, std::string const & args, int sender_fd);
bool	    INVITE_command(t_serv *server, std::string const & args, int sender_fd);
bool        MODE_command(t_serv *server, std::string const & args, int sender_fd);


bool	    check_pwd(t_serv *server, int sender_fd);
std::string	get_channel_name(std::string const & args);
std::string	get_key(std::string const & args);
Client*		getClient(std::string channel_name, std::string nick, t_serv *server);
Channel*	getChannel(std::string const & channel_name, t_serv *server);
std::string  get_target(std::string const & args);
