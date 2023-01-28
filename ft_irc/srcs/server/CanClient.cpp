#include "CanClient.hpp"
#include "CanChannel.hpp"
#include "Operation.hpp"
#include <map>
#include <utility>

CanClient::CanClient() : socketFd(-1), nickname(), username(), realname(), addr(), isMember(0)
{
    memset(buffer, 0, bufferSize);
    setMemberLevel(UNCERTIFICATION);
}

CanClient::CanClient(int fd) : socketFd(fd), nickname(), username(), realname(), addr(), isMember(0)
{
    setMemberLevel(UNCERTIFICATION);
    memset(&this->addr, 0, sizeof(this->addr));
    memset(buffer, 0, bufferSize);
}

CanClient::~CanClient()
{
}

CanClient::CanClient(const struct sockaddr_in addr) : addr(addr), isMember(0)
{
    setMemberLevel(UNCERTIFICATION);
}

CanClient::CanClient(const struct sockaddr_in addr, const int fd) : socketFd(fd), addr(addr), isMember(0)
{
    setMemberLevel(UNCERTIFICATION);
}

void CanClient::setNickname(const std::string name)
{
    this->nickname = name;
}

std::string CanClient::getNickname(void) const
{
    return (this->nickname);
}

void CanClient::setUsername(const std::string name)
{
    this->username = name;
}

void CanClient::setMemberLevel(int lev)
{
    if (lev == UNCERTIFICATION || lev == USER_FIN || lev == NICK_FIN || lev == PASS_FIN || lev == CERTIFICATION_FIN)
        this->isMember |= lev;
}

int CanClient::getMemberLevel(void) const
{
    return (this->isMember);
}

std::string CanClient::getUsername(void) const
{
    return (this->username);
}

void CanClient::setRealname(const std::string name)
{
    this->username = name;
}

std::string CanClient::getRealname(void) const
{
    return (this->username);
}

int CanClient::getSockFd(void) const
{
    return (this->socketFd);
}

int CanClient::getisMember(void) const
{
    return (this->isMember);
}

void CanClient::addChannelElement(const std::string& key, CanChannel* pNewChannel)
{

    // if (ret.second == false)
    if (this->channelList.insert(std::make_pair(key, pNewChannel)).second == false)
    {
        throw(CanClient::addChannelException());
    }
}

void CanClient::deleteChannelElement(std::string key)
{
    if (this->getChannelList().find(key) != this->getChannelList().end())
        this->getChannelList().erase(key);
}

void CanClient::sendToClient()
{
    try
    {
        if (this->sendBuff.length() == 0)
            return;
        std::cout << "[Server->Client]" << this->sendBuff << std::endl;
        int ret = send(socketFd, this->sendBuff.c_str(), this->sendBuff.length(), 0);
        if (ret < 0)
        {
            throw CanClient::sendToClientException();
        }
        this->sendBuff.clear();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
    }
}

void CanClient::addSendBuff(std::string message)
{
    this->sendBuff += message;
}

void CanClient::setSendBuff(const std::string& msg)
{
    this->sendBuff = msg;
}

std::string& CanClient::getsendBuff(void)
{
    return (this->sendBuff);
}
void CanClient::setRecvBuff(const std::string& msg)
{
    this->recvBuff = msg;
}

std::string& CanClient::getRecvBuff(void)
{
    return (this->recvBuff);
}
char* CanClient::getBuffer(void)
{
    return (this->buffer);
}
void CanClient::addRecvBuff(std::string& message)
{
    this->recvBuff += message;
}
int CanClient::recvClient(void)
{
    memset(buffer, 0, bufferSize);
    int ret = recv(this->socketFd, this->buffer, bufferSize, 0);

    std::cout << std::endl << "[Client->Server]" << this->buffer << std::endl;
    std::string recvMsg(this->buffer);

    if (ret == 512 && (recvMsg.find("\r\n") == std::string::npos))
    {
    }
    else
    {
        addRecvBuff(recvMsg);
    }

    return (ret);
}

std::map<std::string, CanChannel*>& CanClient::getChannelList(void)
{
    return (this->channelList);
}

const char* CanClient::addChannelException::what() const throw()
{
    return "CanClient addChhannel : Failed ! \r\n";
}

const char* CanClient::sendToClientException::what() const throw()
{
    return "CanClient sendToClient : couldn't send socket ! \r\n";
}
