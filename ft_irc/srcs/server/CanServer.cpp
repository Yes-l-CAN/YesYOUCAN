#include "CanServer.hpp"
#include "CanChannel.hpp"

CanServer::CanServer() : socketFd(-1), maxFd(1000)
{
    setServAddr();
    FD_ZERO(&reads);
    FD_ZERO(&copyReads);
    FD_ZERO(&writes);
    FD_ZERO(&copyWrites);
}

CanServer::~CanServer()
{
    CanClient*  pClient;
    CanChannel* pChannel;

    while (clientList.empty() == false)
    {
        pClient = clientList.begin()->second;
        deleteClientElement(pClient->getSockFd());
    }

    while (channelList.empty() == false)
    {
        pChannel = channelList.begin()->second;
        deleteChannelElement(pChannel->getChannelName());
    }
}

void CanServer::addChannelElement(const std::string channelName, CanChannel* pNewChannel)
{
    this->getChannelList().insert(std::make_pair(channelName, pNewChannel));
}

void CanServer::deleteChannelElement(const std::string channelName)
{
    CanChannel* pDel = this->getChannelList().find(channelName)->second;
    this->getChannelList().erase(channelName);
    delete pDel;
}

void CanServer::deleteClientElement(const int fd)
{
    CanClient* pDel = this->getClientList().find(fd)->second;
    this->getClientList().erase(fd);
    delete pDel;
}

void CanServer::setServer(char* port, char* pw)
{
    this->port = std::atoi(port);
    std::cout << "port ::" << this->port << std::endl;
    if (this->port < 1025 || this->port > 65536)
        throw(CanException::invalidPortException());
    this->password = static_cast<std::string>(pw);
}

void CanServer::s_On()
{
    try
    {
        s_Socket();

        int option = true;
        setsockopt(this->socketFd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

        setServAddr();
        s_Bind();
        s_Listen();
        FD_SET(this->socketFd, &reads);
        std::cout << "server on!" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}

void CanServer::setServAddr()
{
    this->addr.sin_family = AF_INET;
    this->addr.sin_addr.s_addr = htonl(INADDR_ANY);
    this->addr.sin_port = htons(this->port);
}

void CanServer::s_Socket()
{
    int fd;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0)
        throw(CanException::socketCreateException());
    this->socketFd = fd;
}

void CanServer::s_Bind()
{
    int res;

    res = bind(this->socketFd, (struct sockaddr*)&(this->addr), sizeof(this->addr));
    if (res < 0)
        throw(CanException::bindException());
}

void CanServer::s_Listen()
{
    if (listen(this->socketFd, MAX_FD) < 0)
    {
        throw(CanException::listenException());
    }
}

void CanServer::s_Select()
{
    int            res;
    struct timeval timeout;

    while (1)
    {
        timeout.tv_sec = 5;
        timeout.tv_usec = 500;
        this->copyReads = this->reads;
        this->copyWrites = this->writes;

        res = select(this->maxFd + 1, &(this->copyReads), &(this->copyWrites), NULL, &timeout);
        if (res < 0)
            throw(CanException::selectException());
        else if (res == 0)
            continue;
        else
            break;
    }
}

void CanServer::s_Accept()
{
    int                clientSockFd = -1;
    struct sockaddr_in clientAddr;
    unsigned int       size = sizeof(clientAddr);

    clientSockFd = accept(this->socketFd, (struct sockaddr*)&clientAddr, &size);
    if (clientSockFd < 0)
    {
        throw(CanException::acceptException());
    }
    fcntl(clientSockFd, F_SETFL, O_NONBLOCK);

    FD_SET(clientSockFd, &reads);
    FD_SET(clientSockFd, &writes);

    CanClient* temp = new CanClient(clientAddr, clientSockFd);

    clientList.insert(std::make_pair(clientSockFd, temp));
    std::map<int, CanClient*>::iterator it;
    if (clientSockFd > MAX_FD)
    {
        throw(CanException::tooManyClientFDException());
    }
}

// utils
void CanServer::setFdSet()
{
    fd_set* reads_addr = &this->reads;
    fd_set* writes_addr = &this->writes;
    FD_ZERO(reads_addr);
    FD_ZERO(writes_addr);
    FD_SET(this->socketFd, reads_addr);
}

void CanServer::findFd()
{
    for (int i = 0; i < this->maxFd + 1; i++)
    {
        if (FD_ISSET(i, &this->copyReads) && i == this->socketFd)
        // if(FD_ISSET(i, &this->copyReads) == this->socketFd)
        {
            try
            {
                s_Accept();
            }
            catch (std::exception& e)
            {
                std::cout << e.what() << std::endl;
                return;
            }
        }
    }
}

void CanServer::leaveAll(int fd)
{
    CanClient* client = this->getClientList().find(fd)->second;
    if (client != NULL)
    {
        std::map<std::string, CanChannel*>::iterator it = client->getChannelList().begin();
        std::string                                  msgBuf;
        // for(it = client->getChannelList().begin(); it != client->getChannelList().end(); it++)
        while (client->getChannelList().size() != 0)
        {
            it = client->getChannelList().begin();
            msgBuf = ":" + client->getNickname() + " PART " + it->second->getChannelName() + "\r\n";
            it->second->broadcast(msgBuf, client);
            it->second->deleteClientElement(client->getSockFd());
            if (it->second->getClientList().size() == 0)
            {
                deleteChannelElement(it->second->getChannelName());
            }
            client->deleteChannelElement(it->second->getChannelName());
        }
    }
}

int CanServer::getInputPortNum() const
{
    return (this->inputPortNum);
}

std::string CanServer::getInputPasswordNum() const
{
    return (this->inputPassword);
}

int CanServer::getPort() const
{
    return (this->port);
}

std::string CanServer::getPassWord() const
{
    return (this->password);
}

int CanServer::getSocketFd() const
{
    return (this->socketFd);
}

struct sockaddr_in CanServer::getAddr() const
{
    return (this->addr);
}

fd_set* CanServer::getReads()
{
    return (&(this->reads));
}

fd_set* CanServer::getCopyReads()
{
    return (&(this->copyReads));
}

fd_set* CanServer::getWrites()
{
    return (&(this->writes));
}

fd_set* CanServer::getCopyWrites()
{
    return (&(this->copyWrites));
}

std::map<int, CanClient*>& CanServer::getClientList()
{
    return (this->clientList);
}

std::map<std::string, CanChannel*>& CanServer::getChannelList()
{
    return (this->channelList);
}

int CanServer::getCurrentMaxFd() const
{
    return (this->maxFd);
}

void CanServer::serverClose(void)
{
    std::string closeMsg = "CanServer Closed! \r\n";

    std::map<int, CanClient*>::iterator it;
    for (it = this->clientList.begin(); it != this->clientList.end(); it++)
    {
        send(it->second->getSockFd(), closeMsg.c_str(), closeMsg.length(), 0);
    }
}