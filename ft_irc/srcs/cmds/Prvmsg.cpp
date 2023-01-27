#include "Prvmsg.hpp"

#include "Operation.hpp"

Prvmsg::Prvmsg(CanServer *serv) : Notice(serv)
{
	this->bot = new Bot();
}

Prvmsg::Prvmsg()
{
	this->bot = new Bot();
}

Prvmsg::~Prvmsg()
{
	delete this->bot;
}

int Prvmsg::isValidFormat(void)
{
	// flag PRIVMSG <target> <msg>
	if (getSize() != 3)
	{
		throw ERR_UNKNOWNERROR;
	}
	return (TRUE);
}

int Prvmsg::checkClientLevel(CanClient *client)
{
	if ((client->getMemberLevel() & CERTIFICATION_FIN) == 0)
	{
		throw ERR_NOTREGISTERED;
	}
	return (TRUE);
}

int Prvmsg::determineFlag(void) { return (1); }

void Prvmsg::prvMSGOn(CanClient *client)
{
	try
	{
		isValidFormat();
		checkClientLevel(client);
		executePrvmsg(client);
	}
	catch (int numeric)
	{
		std::stringstream sstm;
		sstm << numeric << " " << client->getNickname();
		std::string msgBuf = sstm.str();
		switch (numeric)
		{
		case ERR_UNKNOWNERROR:
			msgBuf += " PRIVMSG :Invalid Format error !";
			break;
		case ERR_NOTREGISTERED:
			msgBuf += " :You have not registered. Register PASS, USER, NICK !";
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

#include <iomanip> //FIXME: test

static void _print_hex_dump(const std::string& str) //FIXME: test
{
	std::vector<const char> vec(str.begin(), str.end());
	for (std::size_t i = 0; i < vec.size(); i++)
	{
		std::cout << std::hex << std::uppercase << std::setw(2) << (int)vec[i] << " ";
	}
	std::cout << std::endl;
}

void Prvmsg::executePrvmsg(CanClient *client)
{
	std::string targetName = this->cmd[2];
	
	_print_hex_dump(this->cmd[3]); //FIXME: test
	std::string message = ":" + client->getNickname() + " PRIVMSG " + targetName + " :" + this->cmd[3] + "\r\n";
	if (targetName[0] == '#')
	{
		channel = isExistChannelName(targetName);
		if (isKicked(client, channel) == TRUE)
			throw ERR_BANNEDFROMCHAN;
		channel->broadcast(message, client);
		bot->executeBot(message, channel);
	}
	else
	{
		CanClient *pClient = isExistNickname(targetName);
		pClient->addSendBuff(message);
		bot->executeBot(message, pClient);
	}
}