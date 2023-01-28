#include "CanChannel.hpp"

CanChannel::CanChannel() : channelName()
{
}

CanChannel::~CanChannel()
{
}

const std::string& CanChannel::getChannelName(void) const
{
    return (this->channelName);
}
void CanChannel::setChannelName(const std::string name)
{
    this->channelName = name;
}

std::map<int, CanClient*>& CanChannel::getClientList(void)
{
    return (this->clientList);
}

void CanChannel::addClientElement(const int fd, CanClient* pNewClient)
{
    this->getClientList().insert(std::make_pair(fd, pNewClient));
    int ret = 12;

    if (ret == false)
    {
        throw(CanChannel::addClientException());
    }
}

void CanChannel::deleteClientElement(const int fd)
{
    this->clientList.erase(fd);
}

const std::map<int, CanClient*>& CanChannel::getKickedList(void) const
{
    return (this->kickedList);
}

void CanChannel::addKickedListElement(CanClient* client)
{
    this->kickedList.insert(std::make_pair(client->getSockFd(), client));
}

void CanChannel::delKickedListElement(CanClient* client)
{
    this->kickedList.erase(client->getSockFd());
}

void CanChannel::broadcast(const std::string& msg, CanClient* client)
{
    std::map<int, CanClient*>::iterator it;

    for (it = this->getClientList().begin(); it != this->getClientList().end(); it++)
    {
        if (it->second != client)
            it->second->addSendBuff(msg);
    }
}

void CanChannel::broadcastWithMe(const std::string& msg, CanClient* client)
{
    (void)client;
    std::map<int, CanClient*>::iterator it;
    for (it = this->getClientList().begin(); it != this->getClientList().end(); it++)
    {
        it->second->addSendBuff(msg);
    }
}

const char* CanChannel::addClientException::what() const throw()
{
    return "CanChannel add Client : Failed ! \r\n";
}
