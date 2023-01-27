#include "Nick.hpp"
#include "Operation.hpp"

char Nick::invalid[8] = {' ', ',', '*', '?', '!', '@', '.', '#'};

Nick::Nick() {}

Nick::Nick(CanServer *serv) : ACommand(serv)
{
}

Nick::~Nick() {}

void Nick::onCommand(CanClient *client)
{
	try
	{
		isValidFormat();
		checkClientLevel(client);
		validCheck();
		checkUsedNick();
		setClientNick(client);
		if (((client->getMemberLevel() & CERTIFICATION_FIN) == CERTIFICATION_FIN) && flag == 0)
		{
			welcome2CanServ(client);
			flag = 1;
		}
		else if ((client->getMemberLevel() & CERTIFICATION_FIN) == CERTIFICATION_FIN)
		{
			std::string msg = ":" + client->getNickname() + " NICK :" + cmd[2] + "\r\n";
			client->addSendBuff(msg);
			std::map<std::string, CanChannel *>::iterator it;
			for (it = client->getChannelList().begin(); it != client->getChannelList().end(); it++)
			{
				it->second->broadcast(msg, client);
			}
		}
	}
	catch (int numeric)
	{
		std::stringstream sstm;
		sstm << numeric << " " << client->getSockFd();
		std::string msgBuf = sstm.str();
		switch (numeric)
		{
		case ERR_UNKNOWNERROR:
			msgBuf += " NICK :Invalid Format error !";
			break;

		case ERR_NOTREGISTERED:
			msgBuf += " :You have not registered. Register PASS, USER, NICK !";
			break;

		case ERR_ERRONEUSNICKNAME:
			msgBuf += " " + cmd[2] + " :Erroneus nickname ";
			break;

		case ERR_NICKNAMEINUSE:
			msgBuf += " " + cmd[2] + " :Nickname is already in use";
			break;

		default:
			break;
		}

		msgBuf += "\r\n";
		client->addSendBuff(msgBuf);
	}
}

void Nick::welcome2CanServ(CanClient *client)
{
	// 001 <client> :<msg>
	std::string userName = cmd[2];
	std::string serverName = static_cast<std::string>(SERVERNAME);
	std::string msgBuf = "001 " + userName + " :Welcome, " + userName + "! Your host is " + serverName + "\r\n";
	client->addSendBuff(msgBuf);
}

int Nick::validCheck(void)
{
	// flag NICK <nickname>
	std::string nickName = cmd[2];
	for (int i = 0; i < 8; i++)
	{
		if (nickName.find(invalid[i]) != std::string::npos)
		{
			throw ERR_UNKNOWNERROR;
		}
	}
	if (nickName[0] == '$' || nickName[0] == ':')
	{
		throw ERR_UNKNOWNERROR;
	}
	return (TRUE);
}

int Nick::checkUsedNick(void)
{
	// flag NICK <nickname>
	std::map<int, CanClient *>::iterator cit;
	std::string nickName = cmd[2];

	for (cit = server->getClientList().begin();
		 cit != server->getClientList().end(); cit++)
	{
		if (cit->second->getNickname() == nickName)
		{
			throw ERR_NICKNAMEINUSE;
		}
	}
	return (TRUE);
}

int Nick::isValidFormat(void)
{
	// flag NICK <nickname>
	if (getSize() != 2)
	{
		throw ERR_UNKNOWNERROR;
	}
	return (TRUE);
}

void Nick::setClientNick(CanClient *client)
{
	// flag NICK <nickname>
	std::string nickName = cmd[2];
	if ((client->getMemberLevel() & CERTIFICATION_FIN) == CERTIFICATION_FIN)
	{
		std::string msg = ":" + client->getNickname() + " NICK :" + nickName + "\r\n";
		client->addSendBuff(msg);
	}
	client->setNickname(nickName);
	client->setMemberLevel(NICK_FIN);

	if ((client->getMemberLevel() & (PASS_FIN | USER_FIN)) == (PASS_FIN | USER_FIN))
		client->setMemberLevel(CERTIFICATION_FIN);
}

int Nick::checkClientLevel(CanClient *client)
{
	if ((client->getMemberLevel() & PASS_FIN) == 0)
	{
		throw ERR_NOTREGISTERED;
	}
	return (TRUE);
}

int Nick::determineFlag(void) { return (0); }

// // ERR_ERRONEUSNICKNAME (432) "<client> <nick> :Erroneus nickname"
// const char *Nick::invalidNickException::what() const throw() {
//   return ("Nick Error : invalid nick! \r\n");
// }

// // ERR_NICKNAMEINUSE (433)   "<client> <nick> :Nickname is already in use"
// const char *Nick::usedNickException::what() const throw() {
//   return ("Nick Error : already used nick! \r\n");
// }
