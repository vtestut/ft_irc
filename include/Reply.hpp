#pragma once

// GENERAL MESSAGE
# define    RPL_WELCOME(nick, client, port, host) ("001 " + nick + " Welcome to the " + port + " Network, " + nick + "!" + client + "@" + host + "\r\n")
# define    ERR_UNKNOWNCOMMAND(client, command) (": 421 " + client + " " + command + " Unknown command(custom)\r\n")
# define    ERR_NEEDMOREPARAMS(client, command) (": 461 " + client + " " + command + " Not enough parameters\r\n")
# define    client_id(nick, client, host) (":" + nick + "!" + client + "@" + host)
/*  ****************************************************************************** */
/*  ******************************** client messages ******************************* */
/*  ****************************************************************************** */

// client MESSAGE ERRRORS
# define    ERR_NOPRIVILEGES(nick) ("481 " + nick + " :Permission denied-\r\n")
# define    ERR_ALREADYREGISTERED(client) ("462 " + client + " " ":You may not reregister\r\n")

// PASS MESSAGE ERRORS
# define    ERR_PWDMISMATCH(client) (":464 " + client + " :Password incorrect" + "\r\n")

// NICK MESSAGE ERRORS
# define    NICK(old_nick, client, host, nick) (":" + old_nick + "!" + client + "@" + host + " NICK " + nick + "\r\n")
# define    ERR_NONICKNAMEGIVEN(client) (" 431 " + client + " : No nickame given\r\n")
# define    ERR_ERRONEUSNICKNAME(client, nick) (" 432 " + client + " " + nick + " :Erroneus nickname\r\n")
# define    ERR_NICKNAMEINUSE(client, nick) (" 433 " + client + " " + nick + " :Nickname is alreay in use\r\n")

/*  PING OR PONG   */
# define    PING(client_id, param) (client_id + " PING :" + param + "\r\n")
# define    PONG(client_id, param) (client_id + " PONG :" + param + "\r\n")

/*  OPERATOR messages   */
# define    RPL_YOUREOPER(nick) ("381 " + nick + " :You are now an IRC operator\r\n")

/*  QUIT   */
# define    QUIT(client_id, reason) (client_id + " QUIT :" + reason + "\r\n")

/*  Kill    */
# define    KILL(source, reason) ("You have been disconeected from the server by " + source + ", because " + reason + "\r\n")
# define    KILL_WOREASON(source) ("You have been disconeected from the server by " + source + "\r\n")

/*  ****************************************************************************** */
/*  ******************************** CHANNEL messages ******************************* */
/*  ****************************************************************************** */
# define    ERR_NOSUCHCHANNEL(nick, channel) (": 403 " + nick + " " + channel + " :No such channel\r\n")
# define	ERR_CLIENTNOTINCHANNEL(nick, channel) (": 441 " + nick + " " + channel + " :They aren't on that channel\r\n")
# define 	ERR_NOTONCHANNEL(channel, nick) (": 442 " + channel + " :" + nick + " not on channel\r\n")
# define 	ERR_CLIENTONCHANNEL(nick, invitenick, channel) (": 443 " + nick + " " + invitenick + " " + channel + ":is already on channel\r\n")
# define    ERR_BADCHANMASK(channel) (": 476 " + channel + " :Bad Channel Mask\r\n")

# define    ERR_NOSUCHNICKCHANNEL(nick) ("401 " + nick + " :No such nick\r\n")

/*  Join    */
# define    JOIN(nick, client, host, channel) (":" + nick + "!" + client + "@" + host + " JOIN :" + channel)
# define    CREATEDCHANNEL(channel) (channel + " channel created\r\n")
# define    ERR_INVITEONLYCHAN(nick, channel) ("473 " + nick + " " + channel + " :Cannot join channel (+i)\r\n")
# define    ERR_BADCHANNELKEY(nick, channel) ("475 " + nick + " " + channel + " :Cannot join channel (+k)\r\n")
# define    ERR_CHANNELISFULL(nick, channel) ("471 " + nick + " " + channel + " :Cannot join channel (+l)\r\n")
# define    ERR_TOOMANYCHANNELS(nick, channel) ("405 " + nick + " " + channel + " :You have joined too many channels\r\n")

/*  Invite  */
# define 	RPL_INVITING(client_id, nick, nickinvite, channel) (client_id + " 341 " + nick + " " + nickinvite + " " + channel + ": inviting " + nickinvite + " to " + channel + "\r\n")
# define	INVITE(client_id, nickinvite, channel)  (client_id + " INVITE " + nickinvite + " " + channel + "\r\n")

/*  Names   */
# define    RPL_NAMREPLY(channel, nick, client, host, clients) (": 353 " + nick + "!" + client + "@" + host + " = " + channel + " :" + clients + "\r\n")
# define    RPL_ENDOFNAMES(channel, nick, client, host) (": 366 " + nick + "!" + client + "@" + host + " " + channel + " :End of /NAMES list.\r\n")

/*  KICK    */
# define    RPL_KICK(client_id, channel, kicked, reason) (client_id + " KICK " + channel + " " + kicked + " " + reason + "\r\n")
# define    RPL_KICK2(client_id, channel, kicked, reason) (client_id + " KICK " + channel + " " + kicked + " " + reason)
/*  PART    */
# define    PART_WOREASON(nick, client, host, channel) (":" + nick + "!" + client + "@" + host + " PART " + channel + " :Default reason")
# define    PART_WREASON(nick, client, host, channel, reason) (":" + nick + "!" + client + "@" + host + " PART " + channel + " :" + reason)
/*  Topic   */
# define	RPL_TOPIC(nick, client, name, channel, topic) (": 332 " + nick + "!" + client + "@" + name + " " + channel + " :" + topic + "\r\n")
# define	RPL_TOPIC2(nick, client, name, channel, topic) (": 332 " + nick + "!" + client + "@" + name + " " + channel + " :" + topic)
# define	RPL_NOTOPIC(nick, client, name, channel) (": 331 " + nick + "!" + client + "@" + name + " " + channel + " :No topic is set\r\n")
# define	RPL_NOTOPIC2(nick, client, name, channel) (": 331 " + nick + "!" + client + "@" + name + " " + channel + " :No topic is set")
/*  Modes   */
# define	ERR_CHANOPRIVSNEEDED(client_id, channel) (": 482 " + client_id + " " + channel + " :You're not channel operator\r\n")
# define	MODE(channel, mode, comment) (": MODE " + channel + " " + mode + " :" + comment + "\r\n")
# define	MODE2(client_id, channel, mode, comment) (client_id + " MODE " + channel + " " + mode + " :" + comment)
# define    RPL_UMODEIS(nick) (": 221 " + nick + " +io\r\n")
# define    ERR_KEYSET(channel) (": 467 " + channel + " :Channel key already set\r\n")
# define    RPL_CHANNELMODEIS(nick, channel) ("324 " + nick + " " + channel + " +itkol\r\n")
# define    ERR_UNKNOWNMODE(mode) (": 472 " + mode + " :is unknown char to me\r\n")

// # define    PRIVMSG(nick, dest, message) (":" + nick + " PRIVMSG " + dest + " :" + message + "\n")
# define    PRIVMSG(nick, dest, str) (":" + nick + " PRIVMSG " + dest + " :" + str + "\r\n")
# define    PRIVMSG2(nick, client, host, dest, str) (":" + nick + "!" + client + "@" + "localhost" + " PRIVMSG " + dest + " :" + str)
# define    RPL_AWAY(nick, client, host, dest, str) (":" + nick + "!" + client + "@" + "localhost" + " 301 " + dest + " " + str + "\r\n")
