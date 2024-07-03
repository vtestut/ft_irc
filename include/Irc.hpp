/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Irc.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:35:39 by vtestut           #+#    #+#             */
/*   Updated: 2024/07/03 19:44:45 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include "Colors.hpp"
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# include <cstring>
# include <cstdlib>
# include <iostream>
# include <map>
# include <vector>
# include <poll.h>
# include <unistd.h>
# include <sstream>
# include <string>
# include <cerrno>
# include <ctime>
# include <time.h>
# include <signal.h>
# include <fstream>
# include <algorithm>
# include <syslog.h>
# include <sys/epoll.h>
# include <signal.h>
# include <stdexcept>
# include <iostream>
# include <iomanip>


# define LOCAL_HOST "127.0.0.1"
# define BUFFER_SIZE 1024
# define MAX_EVENTS 10
# define MAX_CHANNELS 1

extern bool	Open;
