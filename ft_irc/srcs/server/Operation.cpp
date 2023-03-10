#include "Operation.hpp"
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

    this->cmdUser = new User(this->server);
    this->cmdQuit = new Quit(this->server);
    this->cmdPrvmsg = new Prvmsg(this->server);
    this->cmdPing = new Ping(this->server);
    this->cmdPass = new Pass(this->server);
    this->cmdPart = new Part(this->server);
    this->cmdNotice = new Notice(this->server);
    this->cmdNick = new Nick(this->server);
    this->cmdJoin = new Join(this->server);
    this->cmdKick = new Kick(this->server);
}

Operation::Operation(char* s1, char* s2)
{
    this->server = new CanServer();
    this->parser = Parsing();
    this->server->setServer(s1, s2);
    this->server->s_On();

    this->cmdUser = new User(this->server);
    this->cmdQuit = new Quit(this->server);
    this->cmdPrvmsg = new Prvmsg(this->server);
    this->cmdPing = new Ping(this->server);
    this->cmdPass = new Pass(this->server);
    this->cmdPart = new Part(this->server);
    this->cmdNotice = new Notice(this->server);
    this->cmdNick = new Nick(this->server);
    this->cmdJoin = new Join(this->server);
    this->cmdKick = new Kick(this->server);
}

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
    delete cmdKick;
}

void Operation::Transmission()
{
    server->s_Select();

    for (int i = 0; i < MAX_FD; i++)
    {
        if (FD_ISSET(i, (server->getCopyReads())))
        {
            this->setFd = i;
            if (i == server->getSocketFd())
            {
                server->s_Accept();
                std::cout << "Accepted socket fd!\n";
            }
            else
            {
                cRecv(this->setFd);
                CanClient* targetClient = findClient(this->setFd);

                std::string sCmd;
                while (getCommandFromRecvBuffer(targetClient, sCmd) == TRUE)
                {
                    std::vector<std::string> cmd = parser.parseOn(sCmd);
                    parser.parseClear();

                    CommandChecker(cmd, targetClient);
                }
            }
        }
    }
    CanClient* pClient = NULL;
    for (int i = 0; i < MAX_FD; i++)
    {
        if (FD_ISSET(i, server->getCopyWrites()))
        {
            if (i == server->getSocketFd())
            {
                continue;
            }
            if (server->getClientList().find(i) != server->getClientList().end())
            {
                pClient = server->getClientList().find(i)->second;
                if (pClient->getsendBuff().size() != 0)
                {
                    pClient->sendToClient();
                }
            }
        }
    }
}

CanClient* Operation::findClient(int fd)
{
    return (server->getClientList().find(fd)->second);
}

void Operation::CommandChecker(std::vector<std::string> argv, CanClient* targetClient)
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
    int ret = this->server->getClientList().find(fd)->second->recvClient();

    if (ret < 0)
    {
        FD_CLR(fd, server->getReads());
        FD_CLR(fd, server->getWrites());
        close(fd);
        server->deleteClientElement(fd);
        server->leaveAll(fd);
        std::cout << "recv error ~~ " << std::endl;
        throw(CanException::recvSocketErrorException());
    }
    if (ret == 0)
    {
        FD_CLR(fd, server->getReads());
        FD_CLR(fd, server->getWrites());
        close(fd);
        server->deleteClientElement(fd);
        server->leaveAll(fd);
        throw(CanException::recvSocketClosedException());
    }
}

int Operation::getCommandFromRecvBuffer(CanClient* client, std::string& sCmd)
{
    std::string sOriginBuf = client->getRecvBuff();
    if (client->getRecvBuff().length() == 0)
    {
        return (FALSE);
    }

    size_t findIdx = sOriginBuf.find("\r\n");
    if (findIdx != std::string::npos)
    {
        sCmd = sOriginBuf.substr(0, findIdx);
        client->setRecvBuff(sOriginBuf.substr(findIdx + 2, sOriginBuf.length()-(findIdx + 2)));
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