/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtestut <vtestut@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 11:01:22 by vtestut           #+#    #+#             */
/*   Updated: 2024/07/03 19:45:47 by vtestut          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Client.hpp"

Client::Client(int fd): _clientname(""), _nickname(""), _messages(""), _partial_data(""),
		_fd(fd), _isOperator(false), _isRegistred(false), _hasNickname(false), _hasclientname(false),
		_hasPwd(false)
{
}

Client::~Client()
{
	if (this->_fd != -1)
		close(this->_fd);
}






std::string Client::getClientrname() const
{
	return (this->_clientname);
}

std::string Client::getRealname() const
{
	return (this->_realname);
}

std::string Client::getNickname() const
{
	return (this->_nickname);
}

std::string Client::getMessage() const
{
	return (this->_messages);
}

std::string Client::getPartialData() const
{
	return (this->_partial_data);
}

int Client::get_fd() const
{
	return (this->_fd);
}

bool    Client::isOperator() const
{
	return (this->_isOperator);
}

bool    Client::isRegistred() const
{
	return (this->_isRegistred);
}

bool    Client::hasNickname() const
{
	return (this->_hasNickname);
}

bool    Client::hasclientname() const
{
	return (this->_hasclientname);
}

bool    Client::hasPwd() const
{
	return (this->_hasPwd);
}

Channel*    Client::getChannels(std::string const & channel_name) const
{
	for (size_t i = 0; i < this->_channels.size(); ++i)
	{
		if (this->_channels[i]->getChannelname() == channel_name)
			return (this->_channels[i]);
	}
	return (NULL);
}





void    Client::setClientname(std::string const & clientname)
{
	this->_clientname = clientname;
}

void    Client::setRealName(std::string const & realname)
{
	this->_realname = realname;
}

void	Client::setNickname(std::string const & nickname)
{
	this->_nickname = nickname;
}

void	Client::setMessages(std::string const & message)
{
	this->_messages = message;
}

void	Client::append_partial_data(std::string const & data)
{
	std::cout << "bufferize: " << data << std::endl;
	this->_partial_data += data;
}

void	Client::setPartialdata(std::string const & data)
{
	this->_partial_data = data;
}

void	Client::set_fd(int fd)
{
	this->_fd = fd;
}

void	Client::set_isOperator(bool boolean)
{
	this->_isOperator = boolean;
}

void	Client::set_isRegistred(bool boolean)
{
	this->_isRegistred = boolean;
}

void	Client::set_hasNickname(bool boolean)
{
	this->_hasNickname = boolean;
}

void	Client::set_Hasclientname(bool boolean)
{
	this->_hasclientname = boolean;
}

void	Client::set_hasPwd(bool boolean)
{
	this->_hasPwd = boolean;
}






void    Client::addChannel(Channel *channel)
{
	this->_channels.push_back(channel);
}

bool    Client::remove_channel(std::string const & channel_name)
{
	for (std::vector<Channel*>::iterator it = this->_channels.begin(); it != this->_channels.end(); ++it)
	{
		if ((*it)->getChannelname() == channel_name)
		{
			this->_channels.erase(it);
			return (true);
		}
	}
	std::cout << "This channel : " << channel_name << " doesn't exist can't remove it" << std::endl;
	return (false);
}

std::vector<std::pair<std::string, std::string> >   Client::splitBuffer(std::string const & buffer)
{
	std::vector<std::pair<std::string, std::string> > result;
	size_t  start = 0;
	size_t  end = buffer.find("\r\n");

	while (end != std::string::npos)
	{
		std::string line = buffer.substr(start, end - start);
		size_t      pos = line.find(" ");
		if (pos != std::string::npos)
		{
			std::string command = line.substr(0, pos);
			std::string args = line.substr(pos + 1);
			result.push_back(make_pair(command, args));
		}
		else
		{
			result.push_back(make_pair(line, ""));
		}
		start = end + 2;
		end = buffer.find("\r\n", start);
	}
	return (result);
}