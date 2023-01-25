#include "CanClient.hpp"
#include "CanChannel.hpp"
#include "Operation.hpp"
#include <map>
#include <utility>

CanClient::CanClient() : socketFd(-1), nickname(), username(), realname(), addr(), isMember(0)
{
	setMemberLevel(UNCERTIFICATION);
}

CanClient::CanClient(int fd) : socketFd(fd), nickname(), username(), realname(), addr(), isMember(0)
{
	setMemberLevel(UNCERTIFICATION);
	memset(&this->addr, 0, sizeof(this->addr));
}

CanClient::CanClient(const CanClient &ref)
{
	*this = ref;
}

CanClient &CanClient::operator=(const CanClient &ref)
{
	if (this != &ref)
	{
	}
	return (*this);
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

void CanClient::addChannelElement(const std::string &key, CanChannel *pNewChannel)
{

	// if (ret.second == false)
	if (this->channelList.insert(std::make_pair(key, pNewChannel)).second == false)
	{
		throw(CanClient::addChannelException());
	}
}

void CanClient::deleteChannelElement(std::string key)
{
	(void)key;
}

void CanClient::sendToClient()
{
    try
    {
		if (this->sendBuff.length() == 0)
			return ;

        int ret = send(socketFd, this->sendBuff.c_str(), this->sendBuff.length(), 0);
        if (ret < 0)
        {
            throw CanClient::sendToClientException();
        }
		this->sendBuff = "";
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void CanClient::addSendBuff(std::string message)
{
	this->sendBuff += message;
}

// void CanClient::cRecv(std::string msg)
// {
//     setrecvBuff(msg);
// }

void CanClient::setSendBuff(const std::string &msg)
{
    this->sendBuff = msg;
}

// void CanClient::setrecvBuff(const std::string &msg)
// {
//     this->recvBuff += msg;
// }

std::string& CanClient::getsendBuff(void)
{
    return (this->sendBuff);
}

// std::string& CanClient::getrecvBuff(void)
// {
//     return (this->recvBuff);
// }

std::map<std::string, CanChannel *> &CanClient::getChannelList(void)
{
	return (this->channelList);
}

const char *CanClient::addChannelException::what() const throw()
{
	return "CanClient addChhannel : Failed !\n";
}

const char* CanClient::sendToClientException::what() const throw()
{
    return "CanClient sendToClient : couldn't send socket !\n";
}
