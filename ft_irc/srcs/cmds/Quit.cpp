#include "Quit.hpp"

#include "Operation.hpp"

Quit::Quit() {}

Quit::Quit(CanServer *serv) : ACommand(serv){}

Quit::~Quit() {}

// Quit::Quit(const Quit &obj)
// {
// 	// Deprecated.
// }

// Quit &Quit::operator=(const Quit &obj)
// {
// 	// Deprecated.
// 	return (*this);
// }

void Quit::quitOn(CanClient *client)
{
	try
	{
		int clientFd = client->getSockFd();

		isValidFormat();
		msgToAllJoinedChannel(client);
		eraseFromList(client);
		FD_CLR(clientFd, server->getReads());
		FD_CLR(clientFd, server->getWrites());
		close(clientFd);
	}
	catch(const std::exception& e)
	{
    	std::string msgBuf = e.what();
    	client->addSendBuff(msgBuf);  	
	}
}

void Quit::eraseFromList(CanClient *client)
{
	int clientFd = client->getSockFd();

	std::map<std::string, CanChannel *>::iterator it;
	for(it = client->getChannelList().begin(); it != client->getChannelList().end(); it++)
	{	
		it->second->deleteClientElement(clientFd);
	}

	for(it = server->getChannelList().begin(); it != server->getChannelList().end(); it++)
	{
		if (it->second->getKickedList().find(clientFd) != it->second->getKickedList().end())
		{
			it->second->delKickedListElement(client);
		}
	}
	server->deleteClientElement(clientFd);
}

void Quit::msgToAllJoinedChannel(CanClient *client)
{
	// 	:<source> QUIT :Quit: <reason>	
	std::string msgBuf = ":" + client->getNickname() + " QUIT :Quit";
	if (getSize() == 2)
	{
		msgBuf += cmd[2];
	}
	msgBuf += "\n";

	std::map<std::string, CanChannel *>::iterator it;
	for (it = client->getChannelList().begin(); it != client->getChannelList().end(); it++)
	{
		it->second->broadcast(msgBuf, client);
	}
}

int Quit::isValidFormat(void) 
{
	// flag QUIT [reason]
	if (getSize() > 2)
	{
		throw invalidFormatException();	
	}
	return (TRUE);
}

int Quit::checkClientLevel(CanClient *client) 
{
	int clientFd = client->getSockFd();
	(void)clientFd;
  	return (TRUE);
}

int Quit::determineFlag(void) { return (1); }
