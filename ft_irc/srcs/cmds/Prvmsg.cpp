#include "Prvmsg.hpp"

#include "Operation.hpp"

Prvmsg::Prvmsg(CanServer *serv): Notice(serv) {this->bot = new Bot();}
Prvmsg::~Prvmsg() { this->bot = new Bot();}
Prvmsg::~Prvmsg() { delete this->bot;}

// Prvmsg::Prvmsg(const Prvmsg &obj)
// {
// 	// Deprecated.
// }

// Prvmsg &Prvmsg::operator=(const Prvmsg &obj)
// {
// 	// Deprecated.
// 	return (*this);
// }

// Prvmsg::Prvmsg() { this->bot = new Bot(); }

//Prvmsg::~Prvmsg() { delete this->bot; }

int Prvmsg::isValidFormat(void) 
{
	// flag PRIVMSG <target> <msg>
	if (getSize() != 3)
	{
		throw invalidFormatException();
	}
	return (TRUE);
}

int Prvmsg::checkClientLevel(CanClient *client) {
  if ((client->getMemberLevel() & CERTIFICATION_FIN) == 0) {
    throw noAuthorityException();
  }
  return (TRUE);
}

int Prvmsg::determineFlag(void) { return (1); }


void Prvmsg::prvMSGOn(CanClient *client)
{
	try{
		isValidFormat();
		checkClientLevel(client);
		executePrvmsg(client);
	} catch(std::exception &e)
	{
		std::string msgBuf = e.what();
    	client->addSendBuff(msgBuf);
	}
}

void Prvmsg::executePrvmsg(CanClient *client)
{
	std::string targetName = this->cmd[2];
	std::string message = "PRIVMSG " + targetName + " : " + this->cmd[3] + "\n";
	if (targetName[0] == '#')
	{
		channel = isExistChannelName(targetName);
		if (isKicked(client, channel) == TRUE)
			throw(kickedUserException());
		channel->broadcast(message);
		bot->executeBot(message, channel);
	} else {
				// send to Client ? 보다는 buffer에 저장이 더 맞을 듯...?=
		CanClient *pClient = isExistNickname(targetName);
		pClient->addSendBuff(message);
		bot->executeBot(message, pClient);
	}
}