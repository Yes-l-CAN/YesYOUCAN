#include "Operation.hpp"
#include "Utility.hpp"

#include <exception>
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <vector>

Operation::Operation()
{
	this->server = new CanServer();
	this->parser = Parsing();
	this->server->s_On();

	// new commands
	this->cmdUser = new User();
	this->cmdQuit = new Quit();
	this->cmdPrvmsg = new Prvmsg();
	this->cmdPing = new Ping();
	this->cmdPass = new Pass();
	this->cmdPart = new Part();
	this->cmdNotice = new Notice();
	this->cmdNick = new Nick();
	this->cmdJoin = new Join();
}

Operation::Operation(char *s1, char *s2)
{
	this->server = new CanServer();
	this->parser = Parsing();
	this->server->setServer(s1, s2);
	this->server->s_On();

	// new commands
	this->cmdUser = new User();
	this->cmdQuit = new Quit();
	this->cmdPrvmsg = new Prvmsg();
	this->cmdPing = new Ping();
	this->cmdPass = new Pass();
	this->cmdPart = new Part();
	this->cmdNotice = new Notice();
	this->cmdNick = new Nick();
	this->cmdJoin = new Join();
}

// Operation::Operation(const Operation &obj)
// {
// 	// Deprecated.
// }

// // deep copy
// Operation &Operation::operator=(const Operation &obj)
// {
// 	// Deprecated.
// 	return (*this);
// }

Operation::~Operation()
{
	delete server;
	delete cmdUser;
	delete cmdQuit;
	delete cmdPrvmsg;
	delete cmdPing;
	delete cmdPass;
	delete cmdPart;
	delete cmdNotice;
	delete cmdNick;
	delete cmdJoin;
}

void Operation::Transmission()
{

	server->s_Select();
	this->setFd = server->Transmission(); // return i(fd) // reads fd
	if (this->setFd == server->getSocketFd())
	{
		std::cout << "accept client " << std::endl;
	}
	else
	{
		try
		{
			cRecv(this->setFd);
			CanClient *targetClient = findClient(this->setFd);
							
			// parsing
			std::vector<std::string> cmd = parser.parseOn(this->buffer);

			// check command
			CommandChecker(cmd, targetClient);
			memset(this->buffer, 0, this->bufferSize);
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	// write set
}

CanClient *Operation::findClient(int fd)
{
	return (server->getClientList()->find(fd)->second);
}

void Operation::CommandChecker(std::vector<std::string> argv, CanClient *targetClient)
{
	std::string cmd[] = {"PASS", "NICK", "USER", "PING", "JOIN", "PART", "KICK", "NOTICE", "PRIVMSG"};

	for (size_t i = 0; i < sizeof(cmd) / sizeof(std::string); i++)
	{

		if ((argv.size() >= 2) && (argv[1] == cmd[i]))
		{
			switch (i)
			{
			case 0:
				this->cmdPass->passOn(targetClient);
				return;
			case 1:
				this->cmdNick->nickOn(targetClient);
				return;
			case 2:
				this->cmdUser->userOn(targetClient);
				return;
			case 3:
				this->cmdPing->pingOn(targetClient);
				return;
			case 4:
				this->cmdJoin->joinOn(targetClient);
				return;
			case 5:
				this->cmdPart->partOn(targetClient);
				return;
			case 6:
				this->cmdKick->kickOn(targetClient);
				return;
			case 7:
				this->cmdNotice->noticeOn(targetClient);
				return;
			case 8:
				this->cmdPrvmsg->prvMSGOn(targetClient);
				return;
			default:;
			}
		}
	}
}


void Operation::cRecv(int fd)
{
	int ret = recv(fd, buffer, bufferSize, 0);
	if (ret < 0)
		throw(CanException::recvSocketErrorException());
	if (ret == 0)
		throw(CanException::recvSocketClosedException());
}

void Operation::Client2ServSend(int fd)
{
	(void)fd;
	// need to think about it more ...
}

void Operation::Serv2ClientSend(int fd)
{
	(void)fd;
	// need to think about it more ...
}
