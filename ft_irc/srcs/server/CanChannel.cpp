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
const std::map<int, CanClient*>& CanChannel::getClientList(void) const
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

const char* CanChannel::addClientException::what() const throw()
{
    return "";
}

// virtual const char*	CanChannel::deleteClientException::what() const throw()
// {
// 	return "";
// }