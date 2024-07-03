/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 15:16:30 by vtestut           #+#    #+#             */
/*   Updated: 2024/07/03 19:44:26 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

# include <iostream>
# include <iomanip>
# include <map>
# include <vector>

# include "Client.hpp"

class Client;

class Channel
{
	private:
		std::string			_channel_name;
		std::string			_topic;
		std::string			_pwd_channel;
		int					_fd_creator;
		std::vector<int>	_fd_clients;
		std::vector<int>	_fd_operators;
		std::vector<int>	_fd_invited;
		bool				_is_invite_only;
		bool				_isTopicSet;
		bool				_isTopicProtected;
		bool				_isChannelLocked;
		bool				_hasclientLimit;
		int					_limit;
		int					_maxclientNb;

		public:
								Channel(std::string name, int fd);
								~Channel();

			std::string			getChannelname() const;
			std::string			getTopic() const;
			std::string			getChannelPwd() const;
			std::vector<int>	getclient() const;
			std::vector<int>	getOperators() const;
			bool				isInviteOnly() const;
			bool				isTopicSet() const;
			bool				isTopicProtected() const;
			bool				isChannelLocked() const;
			bool				hasclientLimit() const;
			int					getMaxclientnb() const;
			int					getNbclients() const;

			void				setChannelName(std::string name);
			void				setTopic(std::string topic);
			void				setProtectedTopic(bool boolean);
			void				unsetTopic();
			void				setChannelPwd(std::string const & pwd_channel);
			void				setInviteOnly(bool boolean);
			void				setMaxclientNb(int nb_max_clients);
			void				setHasclientLimit(bool boolean);
			void				setChannelHasPwd(bool boolean);

			bool				is_client(int fd_client);
			bool				is_operator(int fd_client);
			bool				is_invited(int fd_client);
			void				broadcast(std::string message, int fd_sender);
			void				addClient(int fd_client);
			void				kickClient(int fd_client);
			void				inviteClient(int fd_client);
			void				part(int fd_client);
			void				add_operator_client(int fd_client);
			void				del_operator_client(int fd_client);
			void				incrementLimit();
};