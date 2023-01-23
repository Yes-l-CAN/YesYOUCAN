#include "CanClient.hpp"
#include "CanChannel.hpp"
#include "Operation.hpp"
#include <map>
#include <utility>

CanClient::CanClient() : socketFd(-1), nickname(), username(), realname(), addr(), isMember(0), isKicked(false)
{
}

CanClient::CanClient(int fd) : socketFd(fd), nickname(), username(), realname(), addr(), isMember(0), isKicked(false)
{
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

CanClient::CanClient(const struct sockaddr_in addr) : addr(addr)
{
}

CanClient::CanClient(const struct sockaddr_in addr, const int fd) : socketFd(fd), addr(addr)
{
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
	if (lev == USER_FIN || lev == NICK_FIN || lev == PASS_FIN || lev == CERTIFICATION_FIN)
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

bool CanClient::getisKicked(void) const
{
	return (this->isKicked);
}

void CanClient::addChannelElement(std::string key, CanChannel *pNewChannel)
{

	// if (ret.second == false)
	if (this->channelList.insert(std::make_pair(key, pNewChannel)).second == false)
	{
		throw(CanClient::addChannelException());
	}
}

const char *CanClient::addChannelException::what() const throw()
{
	return "";
}