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
    this->server->s_On();
}

Operation::Operation(char* s1, char* s2)
{
    this->server = new CanServer();
    this->server->setServer(s1, s2);
    this->server->s_On();
}

Operation::Operation(const Operation& obj)
{
    *this = obj;
}

// deep copy
Operation& Operation::operator=(const Operation& obj)
{
    if (this != &obj)
    {
        this->setFd = obj.setFd;
        this->result = obj.result;
        for (int i = 0; i < bufferSize; i++)
        {
            this->buffer[i] = obj.buffer[i];
        }

        // deep copy
        Operation replica(obj);

        CanServer* dummy = this->server;
        this->server = replica.server;
		(void) dummy;
    }
    return *this;
}

Operation::~Operation()
{
    delete server;
}

void Operation::Transmission()
{

    server->s_Select();
    this->setFd = server->Transmission(); // return i(fd)
    if (this->setFd == server->getSocketFd())
    {
        std::cout << "accept client " << std::endl;
    }
    else
    {
        try
        {
            cRecv(this->setFd);
            CanClient*               targetClient = findClient(this->setFd);
            std::vector<std::string> cmd = util.splitArr(this->buffer);
            CommandChecker(cmd, targetClient);
            memset(this->buffer, 0, this->bufferSize);
        }
        catch (std::exception& e)
        {
            std::cout << e.what() << std::endl;
        }
    }
    // command 따라서 파싱 하고 실행..?
    // write 테스트
}

CanClient* Operation::findClient(int fd)
{
    return (server->getClientList()->find(fd)->second);
}

void Operation::CommandChecker(std::vector<std::string> argv, CanClient* targetClient)
{
    std::string cmd[] = {"PASS", "NICK", "USER", "PING", "JOIN", "PART", "KICK", "NOTICE", "PRIVMSG"};

    for (size_t i = 0; i < sizeof(cmd) / sizeof(std::string); i++)
    {
        if (argv.front() == cmd[i])
        {

            switch (i)
            {
            case 0:
                this->Pass(argv, targetClient);
                return;
            case 1:
                this->Nick(argv, targetClient);
                return;
            case 2:
                this->User(argv, targetClient);
                return;
            case 3:
                this->Ping(argv, targetClient);
                return;
            case 4:
                this->Join(argv, targetClient);
                return;
            case 5:
                this->Part(argv, targetClient);
                return;
            case 6:
                this->Kick(argv, targetClient);
                return;
            case 7:
                this->Notice(argv, targetClient);
                return;
            case 8:
                this->PrivateMSG(argv, targetClient);
                return;
            default:;
                //  인자가 더해져 들어옴! (자동)
                // ./jisookim #42Seoul : hihi!
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
        throw(CanException::recvSocketClosedException()); // TODO: make exception more specifically.
}

void Operation::Client2ServSend(int fd)
{
	(void) fd;
    // need to think about it more ...
}

void Operation::Serv2ClientSend(int fd)
{
	(void) fd;
    // need to think about it more ...
}

void Operation::Pass(std::vector<std::string> argv, CanClient* targetClient)
{
    // std::cout << "Pass Called!" << std::endl;
    std::vector<std::string>::iterator it;
    it = argv.end() - 1;

    if (targetClient->getMemberLevel() == USER_FIN || targetClient->getMemberLevel() == NICK_FIN ||
        targetClient->getMemberLevel() == CERTIFICATION_FIN)
        return;
    else if (server->getInputPasswordNum() == *it)
        targetClient->setMemberLevel(PASS_FIN);
    else
        throw(CanException::PasswordNotSameException());
}

int Operation::Nick(std::vector<std::string> argv, CanClient* targetClient)
{
    std::string reply;
    if (targetClient->getMemberLevel() < PASS_FIN)
        throw(CanException::NotCertificatedException());
    std::vector<std::string>::iterator it;
    it = argv.end() - 1;
    for (std::map<int, CanClient*>::iterator it2 = server->getClientList()->begin();
         it2 != server->getClientList()->end(); ++it2)
    {
        if (it2->second->getNickname() == *it)
            throw(CanException::existNickException());
    }
    if (targetClient->getNickname().empty() != true)
    {
        reply = *(argv.begin()) + " " + *(argv.end() - 1) + "\n";
        ioctl(targetClient->getSockFd(), TIOCFLUSH, 2);
        send(targetClient->getSockFd(), &reply, sizeof(reply), 0);
    }
    targetClient->setNickname(*it);
    if (targetClient->getMemberLevel() == USER_FIN)
        targetClient->setMemberLevel(CERTIFICATION_FIN);
    else
        targetClient->setMemberLevel(NICK_FIN);
    return (0);
}

int Operation::User(std::vector<std::string> argv, CanClient* targetClient)
{
    if (targetClient->getMemberLevel() < PASS_FIN)
        throw(CanException::NotCertificatedException());
    std::vector<std::string>::iterator it;
    it = argv.end() - 1;
    std::map<int, CanClient*>::iterator it2;
    for (it2 = server->getClientList()->begin(); it2 != server->getClientList()->end(); it2++)
    {
        if (it2->second->getUsername() == *it)
            throw(CanException::existUserException());
    }
    targetClient->setUsername(*it);
    if (targetClient->getMemberLevel() == NICK_FIN)
        targetClient->setMemberLevel(CERTIFICATION_FIN);
    else
        targetClient->setMemberLevel(USER_FIN);
    return (0);
}

void Operation::Ping(std::vector<std::string> argv, CanClient* targetClient)
{
    if (targetClient->getMemberLevel() != CERTIFICATION_FIN)
        throw(CanException::NotCertificatedException());
    std::string reply = *(argv.begin()) + " " + *(argv.end() - 1) + "\n";
    ioctl(targetClient->getSockFd(), TIOCFLUSH, 2);
    send(targetClient->getSockFd(), &reply, sizeof(reply), 0);
    // send 'pong'
	(void) argv;
}

void Operation::Quit(std::vector<std::string> argv, CanClient* targetClient)
{
	(void) argv;
	(void) targetClient;
}

// void    Pong(std::vector<std::string> argv, CanClient* targetClient);
void Operation::Join(std::vector<std::string> argv, CanClient* targetClient)
{
    if (targetClient->getMemberLevel() != CERTIFICATION_FIN)
        throw(CanException::NotCertificatedException());
    std::cout << "join Called!" << std::endl;
	(void) argv;
	(void) targetClient;
}

void Operation::Part(std::vector<std::string> argv, CanClient* targetClient)
{
    if (targetClient->getMemberLevel() != CERTIFICATION_FIN)
        throw(CanException::NotCertificatedException());
    std::cout << "part Called!" << std::endl;
	(void) argv;
	(void) targetClient;
}

void Operation::Kick(std::vector<std::string> argv, CanClient* targetClient)
{
    if (targetClient->getMemberLevel() != CERTIFICATION_FIN)
        throw(CanException::NotCertificatedException());
    std::cout << "kick Called!" << std::endl;
	(void) argv;
	(void) targetClient;
}

void Operation::Notice(std::vector<std::string> argv, CanClient* targetClient)
{
    if (targetClient->getMemberLevel() != CERTIFICATION_FIN)
        throw(CanException::NotCertificatedException());
    std::cout << "notice Called!" << std::endl;
	(void) argv;
	(void) targetClient;
}

void Operation::PrivateMSG(std::vector<std::string> argv, CanClient* targetClient)
{
    if (targetClient->getMemberLevel() != CERTIFICATION_FIN)
        throw(CanException::NotCertificatedException());
    std::cout << "privatemsg Called!" << std::endl;
	(void) argv;
	(void) targetClient;
}