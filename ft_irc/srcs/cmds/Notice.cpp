#include "Notice.hpp"

#include "Operation.hpp"

Notice::Notice() {}

Notice::Notice(CanServer *serv) : ACommand(serv) {}

Notice::~Notice() {}

void Notice::onCommand(CanClient *client)
{
	// flag NOTICE <target> <text to be sent>
	try
	{
		isValidFormat();
		checkClientLevel(client);
		executeNotice(client);
	}
	catch (int numeric)
	{
		std::stringstream sstm;
		sstm << numeric << " " << client->getNickname();
		std::string msgBuf = sstm.str();
		switch (numeric)
		{
		case ERR_UNKNOWNERROR:
			msgBuf += " NOTICE :Invalid Format error !";
			break;

		case ERR_NOTREGISTERED:
			msgBuf += " :You have not registered. Register PASS, USER, NICK !";
			break;

		case ERR_NOSUCHCHANNEL:
			msgBuf += " " + cmd[2] + " :No such channel";
			break;

		case ERR_NOSUCHNICK:
			msgBuf += " " + cmd[2] + " :No such nick/channel";
			break;

		case ERR_BANNEDFROMCHAN:
			msgBuf += " " + cmd[2] + " :Banned from channel!";
			break;

		default:
			break;
		}

		msgBuf += "\r\n";
		client->addSendBuff(msgBuf);
	}
}

void Notice::executeNotice(CanClient *client)
{
	std::string targetName = this->cmd[2];
	std::string message = "Notice " + targetName + " : " + this->cmd[3] + "\n";
	if (targetName[0] == '#')
	{
		channel = isExistChannelName(targetName);
		if (isKicked(client, channel) == TRUE)
			throw ERR_BANNEDFROMCHAN;
		channel->broadcast(message, client);
	}
	else
	{
		CanClient *pClient = isExistNickname(targetName);
		pClient->addSendBuff(message);
	}
}

void Notice::noticeToChannel(void) {}

CanChannel *Notice::isExistChannelName(std::string name)
{
	std::map<std::string, CanChannel *>::iterator it;
	it = server->getChannelList().find(name);
	if (it == server->getChannelList().end())
	{
		throw ERR_NOSUCHCHANNEL;
	}
	return (it->second);
}

CanClient *Notice::isExistNickname(std::string name)
{
	std::map<int, CanClient *>::iterator it;
	for (it = server->getClientList().begin(); it != server->getClientList().end(); it++)
	{
		if (it->second->getNickname() == name)
		{
			return (it->second);
		}
	}
	throw ERR_NOSUCHNICK;
}

int Notice::isKicked(CanClient *client, CanChannel *channel)
{
	int clientFd = client->getSockFd();
	if (channel->getKickedList().find(clientFd) != channel->getKickedList().end())
	{
		return (TRUE);
	}
	return (FALSE);
}

int Notice::isValidFormat(void)
{
	// flag NOTICE <target> <text to be sent>
	if (getSize() != 3)
	{
		throw ERR_UNKNOWNERROR;
	}
	return (TRUE);
}

int Notice::checkClientLevel(CanClient *client)
{
	if ((client->getMemberLevel() & CERTIFICATION_FIN) == 0)
	{
		throw ERR_NOTREGISTERED;
	}
	return (TRUE);
}

int Notice::determineFlag(void) { return (1); }

// // ERR_NOSUCHNICK (401)   "<client> <nickname> :No such nick/channel"
// const char *Notice::noSuchNickException::what() const throw() {
//   return (":No such nick/channel\r\n");
// }

// // ERR_NOSUCHCHANNEL (403)   "<client> <channel> :No such channel"
// const char *Notice::noSuchChannelException::what() const throw() {
//   return (":No such channel\r\n");
// }

// // 사용 안함
// // const char *Notice::replyAnywayException::what() const throw() {
// //   return ("Notice Error! : replied anyway! \r\n");
// // }

// // ERR_BANNEDFROMCHAN (474) "<client> <channel> :Cannot join channel"
// 메시지 내용은 변경하기
// const char *Notice::kickedUserException::what() const throw() {
//   return ("Notice Error! : Already kicked user! \r\n");
// }
