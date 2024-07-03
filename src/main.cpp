/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:59:40 by vtestut           #+#    #+#             */
/*   Updated: 2024/07/03 19:46:01 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Irc.hpp"
#include "../include/Colors.hpp"
#include "../include/Server.hpp"

int main (int ac, char **av)
{
	if (ac != 3) {
		std::cout << PURPLE << "Usage: ./ircserv [port] [password]" << RESET << std::endl;
		return (1);
	}
	std::string port = av[1];
	std::string pwd = av[2];
	if (!parsing(port, pwd))
	{
		std::cerr << BOLDCYAN << "Error: port must be a valid number and password must be a valid string." << RESET << std::endl;
		return (1);
	}
	t_serv serv = {};
	serv._port = atoi(port.c_str());
	serv._Pwd = pwd;
	try
	{
		coreIRC(&serv);
	}
	catch (std::exception &e)
	{
		std::cout << BOLDCYAN << e.what() << RESET << std::endl;
		return (1);
	}
	return (0);
}