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
				/*
				1. /r/n이 있는지 확인하고
				만약에 있으면
				 /r/n 까지 newStr 넣어주고
				 buffer -> /r/n 뒤부터 남아있고
				 return true
				 false;
				*/
                // parsing
				/*
				todo 
					저희 버퍼 메세지를 받고 커맨드를 만들 때 공백 기준으로 처리를 해주었었는데 
					들어오는 커맨드 자체가 처음부터 끝까지 한 번에 들어온다는 보장이 없어서 
					buffer에 냅다 담아놓고 /r/n이 들어오면 그 때서야 /r/n기준으로 짤라서 
					그 앞을 커맨드 처리 해주어야 한다고 하더라구요.!! 
					그래서 지금처럼 1recv 1command 형태가 아니라 n recv 1 command 형태가 될 것 같습니당..
					일단 냅다 버퍼에 넣어두고 계속 /r/n있는지 확인한다음에 있으면 그 때서야 파싱하고 커맨드 처리 해줄 것 같아요!!
				*/
                std::vector<std::string> cmd = parser.parseOn(this->buffer);
				parser.parseClear();

                // check command
                CommandChecker(cmd, targetClient);
                memset(this->buffer, 0, this->bufferSize);
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
				this->cmdPass->setCmd(argv);
				this->cmdPass->passOn(targetClient);
				return;
			case 1:
				this->cmdNick->setCmd(argv);
				this->cmdNick->nickOn(targetClient);
				return;
			case 2:
				this->cmdUser->setCmd(argv);
				this->cmdUser->userOn(targetClient);
				return;
			case 3:
				this->cmdPing->setCmd(argv);
				this->cmdPing->pingOn(targetClient);
				return;
			case 4:
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
	if (ret < 0)
	{
		FD_CLR(fd, server->getReads());
		FD_CLR(fd, server->getWrites());
        close(fd);
		throw(CanException::recvSocketErrorException());
	}
	if (ret == 0)
	{
		FD_CLR(fd, server->getReads());
		FD_CLR(fd, server->getWrites());
        close(fd);
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
