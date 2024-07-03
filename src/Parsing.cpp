/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:44:21 by vtestut           #+#    #+#             */
/*   Updated: 2024/07/03 19:46:05 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Server.hpp"

bool	is_valid_port(std::string const & port)
{
	 if (port.empty())
        return false;
		
    int p = atoi(port.c_str());

	if (p != 0 && p >= 1024 && p <= 49151)
    	return (true);
	return (false);
}

bool	is_valid_pwd(std::string const & pwd)
{
	if (pwd.empty() || pwd.size() < 1)
		return (false);
	return (true);
}

bool	parsing(std::string & port, std::string & pwd)
{
	if (!is_valid_port(port) || !is_valid_pwd(pwd))
		return (false);
	return (true);
}