#include "Prvmsg.hpp"
#include "Operation.hpp"

Prvmsg::Prvmsg()
{
	this->bot = new Bot();
}

Prvmsg::~Prvmsg()
{
	delete this->bot;
}

int Prvmsg::isValidFormat(void)
{
}

int Prvmsg::checkClientLevel(CanClient *client)
{
	if (client->getMemberLevel() & CERTIFICATION_FIN == 0)
	{
		return (false);
	}
	return (true);
}

int Prvmsg::determineFlag(void)
{
	return (1);
}
