#include "Operation.hpp"
#include "Parsing.hpp"
#include <exception>
#include <iostream>
#include <string>
#include <sys/ioctl.h>
#include <vector>

Operation::Operation()
	: server(new CanServer()),
	  cmdUser(this->server),
	  cmdQuit(this->server),
	  cmdPrvmsg(this->server),
	  cmdPing(this->server),
	  cmdPass(this->server),
	  cmdPart(this->server),
	  cmdNotice(this->server),
	  cmdNick(this->server),
	  cmdKick(this->server),
	  cmdJoin(this->server)
{
	this->server->s_On();
}

Operation::Operation(char *s1, char *s2)
	: server(new CanServer()),
	  cmdUser(this->server),
	  cmdQuit(this->server),
	  cmdPrvmsg(this->server),
	  cmdPing(this->server),
	  cmdPass(this->server),
	  cmdPart(this->server),
	  cmdNotice(this->server),
	  cmdNick(this->server),
	  cmdKick(this->server),
	  cmdJoin(this->server)
{
	this->server->setServer(s1, s2);
	this->server->s_On();
}


Operation::~Operation()
{
	delete this->server;
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

				std::string sCmd;
				while (getCommandFromRecvBuffer(this->buffer, sCmd) == TRUE)
				{

					std::vector<std::string> cmd = Parsing::parseOn(sCmd);

					// check command
					CommandChecker(cmd, targetClient);
				}
			}
        }
    }
    CanClient * pClient = NULL;
    for (int i = 0; i < MAX_FD;i++)
    {
		// NOTE: 위에 read 검사 했을때랑 합쳐도 될 것 같은데?
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
			ACommand* cmd;
			switch (i)
			{
			case 0:
				cmd = &this->cmdPass;
				break;
			case 1:
				cmd = &this->cmdNick;
				break;
			case 2:
				cmd = &this->cmdUser;
				break;
			case 3:
				cmd = &this->cmdPing;
				break;
			case 4:
				cmd = &this->cmdJoin;
				break;
			case 5:
				cmd = &this->cmdPart;
				break;
			case 6:
				cmd = &this->cmdKick;
				break;
			case 7:
				cmd = &this->cmdNotice;
				break;
			case 8:
				cmd = &this->cmdPrvmsg;
				break;
			case 9:
				cmd = &this->cmdQuit;
				break;
			default:
				cmd = NULL;
				break;
			}

			if (cmd != NULL)
			{
				cmd->setCmd(argv);
				try
				{
					cmd->isValidFormat();
					cmd->checkClientLevel(targetClient);
					cmd->onCommand(targetClient);
				}
				catch (const CanException& e)
				{
					// cmd->onError(e.getErrorNumber());
				}
			}
		}
	}
}


void Operation::cRecv(int fd)
{
	int ret = recv(fd, buffer + offset, bufferSize - offset, 0);
	std::cout << "client to server : " << this->buffer << std::endl;
	if (ret < 0)
	{
		FD_CLR(fd, server->getReads());
		FD_CLR(fd, server->getWrites());
        close(fd);
		server->deleteClientElement(fd);
		std::cout << "recv error ~~ " << std::endl;
		throw(CanException::recvSocketErrorException());
	}
	if (ret == 0)
	{
		FD_CLR(fd, server->getReads());
		FD_CLR(fd, server->getWrites());
        close(fd);
		server->deleteClientElement(fd);
		std::cout << "recv error ~~ " << std::endl;
		throw(CanException::recvSocketClosedException());
	}
}

int Operation::getCommandFromRecvBuffer(char *cOriginBuf, std::string &sCmd)
{
    std::string sOriginBuf(cOriginBuf);
    if (sOriginBuf.length() == 0)
    {
        return (FALSE);
    }

	size_t	findIdx = sOriginBuf.find("\r\n");
    if ( findIdx != std::string::npos)
    {
		sCmd = sOriginBuf.substr(0, findIdx);
		memmove(cOriginBuf, cOriginBuf + findIdx + 2, sOriginBuf.length() - (findIdx + 2));
		cOriginBuf[sOriginBuf.length() - (findIdx + 2)] = '\0'; //FIXME: ):

		// char reloadBuf[bufferSize];
        // char commandBuf[findIdx + 1];

        // memset(reloadBuf, 0, bufferSize);
		// std::size_t len = sOriginBuf.copy(commandBuf, findIdx, 0);
		// commandBuf[len] = '\0';
		// sOriginBuf.copy(reloadBuf, sOriginBuf.length() - (findIdx), findIdx + 1);
		// sCmd = commandBuf;
		// memcpy(cOriginBuf, reloadBuf, bufferSize);
    }
    else
    {
		(void)sCmd;
        return (FALSE);
    }
    return (TRUE);
}

void Operation::serverClose(void)
{
    server->serverClose();
}