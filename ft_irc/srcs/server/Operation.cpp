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
	this->cmdUser = new User(this->server);
	this->cmdQuit = new Quit(this->server);
	this->cmdPrvmsg = new Prvmsg(this->server);
	this->cmdPing = new Ping(this->server);
	this->cmdPass = new Pass(this->server);
	this->cmdPart = new Part(this->server);
	this->cmdNotice = new Notice(this->server);
	this->cmdNick = new Nick(this->server);
	this->cmdJoin = new Join(this->server);
}

Operation::Operation(char *s1, char *s2)
{
	this->server = new CanServer();
	this->parser = Parsing();
	this->server->setServer(s1, s2);
	this->server->s_On();

	// new commands
	this->cmdUser = new User(this->server);
	this->cmdQuit = new Quit(this->server);
	this->cmdPrvmsg = new Prvmsg(this->server);
	this->cmdPing = new Ping(this->server);
	this->cmdPass = new Pass(this->server);
	this->cmdPart = new Part(this->server);
	this->cmdNotice = new Notice(this->server);
	this->cmdNick = new Nick(this->server);
	this->cmdJoin = new Join(this->server);
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

    for(int i = 0; i < MAX_FD; i++)
    {
        if(FD_ISSET(i, (server->getCopyReads())))
        {
			this->setFd = i;
            if(i == server->getSocketFd())
            {
                server->s_Accept();
                std::cout << "Accepted socket fd!\n";
            }
            else
            {
                cRecv(this->setFd);
                CanClient *targetClient = findClient(this->setFd);

				std::cout << "whats in buffer? :: " << this->buffer << std::endl;
				std::string sCmd;
				while (getCommandFromRecvBuffer(this->buffer, sCmd) == TRUE)
				{

					std::cout << "sCmd :::: " << sCmd << std::endl;
					std::vector<std::string> cmd = parser.parseOn(sCmd);
					std::vector<std::string>::iterator it;
					for(it = cmd.begin() ; it != cmd.end(); it ++)
						std::cout << "Cmd :::: " << *it << std::endl;
					parser.parseClear();

					// check command
					CommandChecker(cmd, targetClient);
				}
			}
        }
    }
    CanClient * pClient = NULL;
    for (int i = 0; i < MAX_FD;i++)
    {
        if (FD_ISSET(i, server->getCopyWrites()))
        {
            if(i == server->getSocketFd())
            {
                continue;
            }
			if(server->getClientList().find(i) != server->getClientList().end())
			{
				pClient = server->getClientList().find(i)->second;
				if (pClient->getsendBuff().size() != 0)
				{
					pClient->sendToClient();
				}
			}
        }
    }

	// write set
}

CanClient *Operation::findClient(int fd)
{
	return (server->getClientList().find(fd)->second);
}

void Operation::CommandChecker(std::vector<std::string> argv, CanClient *targetClient)
{
	std::string cmd[] = {"PASS", "NICK", "USER", "PING", "JOIN", "PART", "KICK", "NOTICE", "PRIVMSG", "QUIT"};

	for (size_t i = 0; i < sizeof(cmd) / sizeof(std::string); i++)
	{

		if ((argv.size() >= 2) && (argv[1] == cmd[i]))
		{
			switch (i)
			{
			case 0:
				std::cout << "PASS" << std::endl;
				this->cmdPass->setCmd(argv);
				this->cmdPass->passOn(targetClient);
				return;
			case 1:
				std::cout << "NICK" << std::endl;
				this->cmdNick->setCmd(argv);
				this->cmdNick->nickOn(targetClient);
				return;
			case 2:
				std::cout << "USER" << std::endl;
				this->cmdUser->setCmd(argv);
				this->cmdUser->userOn(targetClient);
				return;
			case 3:
				std::cout << "PING" << std::endl;
				this->cmdPing->setCmd(argv);
				this->cmdPing->pingOn(targetClient);
				return;
			case 4:
				std::cout << "JOIN" << std::endl;
				this->cmdJoin->setCmd(argv);
				this->cmdJoin->joinOn(targetClient);
				return;
			case 5:
				this->cmdPart->setCmd(argv);
				this->cmdPart->partOn(targetClient);
				return;
			case 6:
				this->cmdKick->setCmd(argv);
				this->cmdKick->kickOn(targetClient);
				return;
			case 7:
				this->cmdNotice->setCmd(argv);
				this->cmdNotice->noticeOn(targetClient);
				return;
			case 8:
				this->cmdPrvmsg->setCmd(argv);
				this->cmdPrvmsg->prvMSGOn(targetClient);
				return;
			case 9:
				this->cmdQuit->setCmd(argv);
				this->cmdQuit->quitOn(targetClient);
				return;
			default:;
			}
		}
	}
}


void Operation::cRecv(int fd)
{
	int ret = recv(fd, buffer, bufferSize, 0);
	std::cout << "you are in recv ~~ " << std::endl;
	if (ret < 0)
	{
		FD_CLR(fd, server->getReads());
		FD_CLR(fd, server->getWrites());
        close(fd);
		std::cout << "recv error ~~ " << std::endl;
		throw(CanException::recvSocketErrorException());
	}
	if (ret == 0)
	{
		FD_CLR(fd, server->getReads());
		FD_CLR(fd, server->getWrites());
        close(fd);
		std::cout << "recv error ~~ " << std::endl;
		throw(CanException::recvSocketClosedException());
	}
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


int Operation::getCommandFromRecvBuffer(char *cOriginBuf, std::string &sCmd)
{
    std::string sOriginBuf(cOriginBuf);
    if (sOriginBuf.length() == 0)
    {
        return (FALSE);
    }

    size_t findIdx = sOriginBuf.find("\r\n");
    if (findIdx != std::string::npos)
    {
        char reloadBuf[bufferSize];
        char commandBuf[findIdx + 2];

        memset(reloadBuf, 0, bufferSize);
		std::size_t len = sOriginBuf.copy(commandBuf, findIdx + 1, 0);
		commandBuf[len] = '\0';
		sOriginBuf.copy(reloadBuf, sOriginBuf.length() - (findIdx + 1), findIdx + 2);
		sCmd = commandBuf;
		std::cout << "sCmd" << sCmd <<std::endl;
		memcpy(cOriginBuf, reloadBuf, bufferSize);
		std::cout << "sCmd" << sCmd <<std::endl;
		std::cout << "cOriginBuf :: " << cOriginBuf << std::endl;
    }
    else
    {
		(void)sCmd;
        return (FALSE);
    }
    return (TRUE);
}