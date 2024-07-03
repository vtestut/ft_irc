/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Unknown.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 10:31:37 by nassim            #+#    #+#             */
/*   Updated: 2024/07/03 19:45:34 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/Server.hpp"
#include "../../include/Command.hpp"
#include "../../include/Reply.hpp"

bool	UNKNOWN_command(t_serv *server, std::string const & command, int sender_fd)
{
	if (command == "CAP" || command.empty())
		return (true);
	send_message(server, ERR_UNKNOWNCOMMAND(int_to_str(sender_fd), command), sender_fd);
	return (false);
}
