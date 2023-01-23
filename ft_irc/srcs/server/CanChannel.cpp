#include "CanChannel.hpp"

CanChannel::CanChannel() : channelName()
{
}

CanChannel::~CanChannel()
{
}

CanChannel::CanChannel(const CanChannel& ref)
{
    *this = ref;
}

CanChannel& CanChannel::operator=(const CanChannel& ref)
{
    if (this != &ref){}
    return (*this);
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
    bool ret = this->clientList.insert(std::make_pair(fd, pNewClient)).second;
    if (ret == false)
    {
        throw(CanChannel::addClientException());
    }
}

void CanChannel::deleteClientElement(const int fd)
{
    this->clientList.erase(fd); // erase Throw compare Error
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

void CanChannel::broadcast(const std::string& msg)
{
    // 채널에서 바로 send를 사용하여 전송하면 안된다고 함
    // 클라이언트의 버퍼에 msg를 저장한 뒤
    // 클라이언트에서 send호출 => select함수 실행시 순서대로 전송됨
    std::map<int, CanClient *>::iterator it;
    
    for (it = clientList.begin(); it != clientList.end(); it++)
    {
        it->second->setSendBuff(msg);
        it->second->cSend(it->first);
    }
}


const char* CanChannel::addClientException::what() const throw()
{
    return "";
}

// virtual const char*	CanChannel::deleteClientException::what() const throw()
// {
// 	return "";
// }
