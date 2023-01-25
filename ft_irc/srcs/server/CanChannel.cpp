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
    this->getClientList().insert(std::make_pair(fd, pNewClient));
    int ret = 12;

    std::cout << "clientList size :: " << this->getClientList().size() << std::endl;
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
    // 클라이언트가 write불가능한 상황일 수 있기 때문
    // 클라이언트의 버퍼에 msg를 저장한 뒤
    // select함수에서, write가능한 상황인지 확인 후 fd들을 순차적으로 전송
    std::map<int, CanClient *>::iterator it;
    
    for (it = this->getClientList().begin(); it != this->getClientList().end(); it++)
    {
        it->second->addSendBuff(msg);
    }
}


const char* CanChannel::addClientException::what() const throw()
{
    return "CanChannel add Client : Failed ! \r\n";
}

// virtual const char*	CanChannel::deleteClientException::what() const throw()
// {
// 	return " \r\n";
// }
