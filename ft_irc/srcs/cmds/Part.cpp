#include "Part.hpp"
#include "Operation.hpp"

Part::Part()
{
}

Part::~Part()
{
}

void Part::partOn()
{
}

std::map<CanChannel *, int> Part::getChannel(CanClient *client)
{
}

int Part::isLastMember(CanClient *client)
{
}

void Part::eraseChannel(CanClient *client)
{
}

void Part::channelClose(CanClient *client)
{
}

void Part::operatorChanged(CanClient *client)
{
}

int Part::isValidFormat(void)
{
}

int Part::checkClientLevel(CanClient *client)
{
	if (client->getMemberLevel() & CERTIFICATION_FIN == 0)
	{
		return (false);
	}
	return (true);
}

int Part::determineFlag(void)
{
	return (1);
}

const char *Part::noSuchChannelException::what() const throw()
{
	return ("Part : No such channel !");
}

const char *Part::notOnChannelException::what() const throw()
{
	return ("Part : Not on channel !");
}