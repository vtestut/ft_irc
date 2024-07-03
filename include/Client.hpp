/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 11:16:54 by vtestut           #+#    #+#             */
/*   Updated: 2024/07/03 19:44:31 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <iomanip>
# include <string>
# include <map>
# include "Irc.hpp"

# include "Server.hpp"

class Server;
class Channel;

class Client
{
	private:
		std::string				_clientname;
		std::string				_realname;
		std::string				_nickname;
		std::string				_messages;
		std::string				_partial_data;
		int						_fd;
		bool					_isOperator;
		bool					_isRegistred;
		bool					_hasNickname;
		bool					_hasclientname;
		bool					_hasPwd;
		
		std::vector<Channel *>	_channels;

	public:
		Client(int fd);
		~Client();

		std::string	getClientrname() const;
		std::string	getRealname() const;
		std::string getNickname() const;
		std::string	getMessage() const;
		std::string	getPartialData() const;
		int			get_fd() const;
		bool		isOperator() const;
		bool		isRegistred() const;
		bool		hasNickname() const;
		bool		hasclientname() const;
		bool		hasPwd() const;
		Channel		*getChannels(std::string const & channel_name) const;

		void		setClientname(std::string const & clientname);
		void		setRealName(std::string const & realname);
		void		setNickname(std::string const & nickname);
		void		setMessages(std::string const & messages);
		void		setPartialdata(std::string const & data);
		void		set_fd(int fd);
		void		set_isOperator(bool boolean);
		void		set_isRegistred(bool boolean);
		void		set_hasNickname(bool boolean);
		void		set_Hasclientname(bool boolean);
		void		set_hasPwd(bool boolean);

		void		addChannel(Channel *channel);
		bool		remove_channel(std::string const & channel_name);
		void		append_partial_data(std::string const & data);
		
		std::vector<std::pair<std::string, std::string> > splitBuffer(std::string const & buffer);
};
