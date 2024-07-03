/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:36:55 by vtestut           #+#    #+#             */
/*   Updated: 2024/07/03 19:45:42 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Channel.hpp"

Channel::Channel(std::string name, int fd): _channel_name(name), _topic(""),
		_pwd_channel(""), _fd_creator(fd), _is_invite_only(false), _isTopicSet(false),
		_isTopicProtected(false), _isChannelLocked(false), _hasclientLimit(false), _limit(0),
		_maxclientNb(1)
{
	(void)_fd_creator;
}

Channel::~Channel()
{}

std::string Channel::getChannelname() const
{
	return (this->_channel_name);
}

std::string Channel::getTopic() const
{
	return (this->_topic);
}

std::string	Channel::getChannelPwd() const
{
	return (this->_pwd_channel);
}

std::vector<int>	Channel::getclient() const
{
	return (this->_fd_clients);
}

std::vector<int>	Channel::getOperators() const
{
	return (this->_fd_operators);
}

bool	Channel::isInviteOnly() const
{
	return (this->_is_invite_only);
}

bool	Channel::isTopicSet() const
{
	return (this->_isTopicSet);
}

bool	Channel::isTopicProtected() const
{
	return (this->_isTopicProtected);
}

bool	Channel::isChannelLocked() const
{
	return (this->_isChannelLocked);
}

bool	Channel::hasclientLimit() const
{
	return (this->_hasclientLimit);
}

int	Channel::getMaxclientnb() const
{
	return (this->_maxclientNb);
}

int Channel::getNbclients() const
{
	return(this->_limit);
}


/////////////////////////////////////////////////



void	Channel::setChannelName(std::string name)
{
	this->_channel_name = name;
}

void	Channel::setTopic(std::string topic)
{
	this->_topic = topic;
	this->_isTopicSet = true;
}

void	Channel::setProtectedTopic(bool boolean)
{
	this->_isTopicProtected = boolean;
}


void	Channel::unsetTopic()
{
	this->_isTopicSet = false;
	this->_topic = "";
}

void	Channel::setChannelPwd(std::string const & pwd_channel)
{
	this->_pwd_channel = pwd_channel;
}

void	Channel::setInviteOnly(bool boolean)
{
	this->_is_invite_only = boolean;
	if (boolean == false)
		this->_fd_invited.clear();
}

void	Channel::setMaxclientNb(int nb_max_clients)
{
	this->_maxclientNb = nb_max_clients;
}

void	Channel::setHasclientLimit(bool boolean)
{
	this->_hasclientLimit = boolean;
}

void	Channel::setChannelHasPwd(bool boolean)
{
	this->_isChannelLocked = boolean;
}


///////////////////////////////////////////////////////////////


bool	Channel::is_client(int fd_client)
{
	for (std::vector<int>::iterator it = this->_fd_clients.begin(); it!= this->_fd_clients.end(); it++)
	{
		if (*it == fd_client)
			return (true);
	}
	return (false);
}

bool	Channel::is_operator(int fd_client)
{
	if (fd_client == -1)
		return (false);
	
	for (std::vector<int>::iterator it = this->_fd_operators.begin(); it != this->_fd_operators.end(); it++)
	{
		if (*it == fd_client)
			return (true);
	}
	return (false);
}

bool	Channel::is_invited(int fd_client)
{
	for (std::vector<int>::iterator it = this->_fd_invited.begin(); it != this->_fd_invited.end(); it++)
	{
		if (*it == fd_client)
			return (true);
	}
	return (false);	
}

void	Channel::broadcast(std::string message, int fd_sender)
{
	if (message.size() > 510) //linit set by IRC protocol
		message = message.substr(0, 510);
	message+= "\r\n";
	for (std::vector<int>::iterator it = this->_fd_clients.begin(); it != this->_fd_clients.end(); it++)
	{
		if (fd_sender == -1 || *it != fd_sender)
			send(*it, message.c_str(), message.size(), 0);
	}
	message.clear();
}

void	Channel::addClient(int fd_client)
{
	if (this->_fd_clients.empty())
		this->_fd_operators.push_back(fd_client);
	this->_fd_clients.push_back(fd_client);
}

void	Channel::kickClient(int fd_client)
{
	for (std::vector<int>::iterator it = this->_fd_clients.begin(); it != this->_fd_clients.end(); it++)
	{
		if (*it == fd_client)
		{
			this->_fd_clients.erase(it);
			break;
		}
	}
	if (is_operator(fd_client) == true)
	{
		for (std::vector<int>::iterator it = this->_fd_operators.begin(); it != this->_fd_operators.end(); it++)
		{
			if (*it == fd_client)
			{
				this->_fd_operators.erase(it);
				break;
			}
		}
	}
}

void	Channel::inviteClient(int fd_client)
{
	if (is_invited(fd_client) == false)
		this->_fd_invited.push_back(fd_client);
}

void	Channel::part(int fd_client)
{
	this->_fd_clients.erase(find(this->_fd_clients.begin(), this->_fd_clients.end(), fd_client));
	if (is_operator(fd_client) == true)
		this->_fd_operators.erase(find(this->_fd_operators.begin(), this->_fd_operators.end(), fd_client));
	if (is_invited(fd_client) == true)
		this->_fd_invited.erase(find(this->_fd_invited.begin(), this->_fd_invited.end(), fd_client));
}

void	Channel::add_operator_client(int fd_client)
{
	if (is_operator(fd_client) == false)
		this->_fd_operators.push_back(fd_client);
}

void	Channel::del_operator_client(int fd_client)
{
	this->_fd_operators.erase(find(this->_fd_operators.begin(), this->_fd_operators.end(), fd_client));
}

void	Channel::incrementLimit()
{
	this->_limit++;
}
