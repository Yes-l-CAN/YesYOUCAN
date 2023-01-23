#include "Join.hpp"
#include "Operation.hpp"

Join::Join() {}

Join::~Join() {}

void joinOn()
{
}

int Join::isKicked(CanClient *client)
{
	if (client->getisKicked() == true)
		return (1);
	return (0);
}

void Join::leaveAll(CanClient *client)
{
}

void Join::addClient(CanClient *client)
{
}

void Join::addChannel(CanClient *client)
{
}

void Join::sendMSG(CanClient *client)
{
}

int Join::isValidFormat(void)
{
}

int Join::checkClientLevel(CanClient *client)
{
	if (client->getMemberLevel() & CERTIFICATION_FIN == 0)
	{
		return (false);
	}
	return (true);
}

int Join::determineFlag(void)
{
	return (0);
}

const char *Join::invalidChannelException::what() const throw()
{
	return "Join : Invalid Channel !";
}

const char *Join::alreadyJoinedException::what() const throw()
{
	return "Join : Already joined !";
}

const char *Join::channelOverflowException::what() const throw()
{
	return "Join : channel Overflow";
}
