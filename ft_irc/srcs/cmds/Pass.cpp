#include "Pass.hpp"
#include "Operation.hpp"

Pass::Pass()
{
}

Pass::~Pass()
{
}

void Pass::passOn(void)
{
}

void Pass::passCmp(void)
{
}

int Pass::isValidFormat(void)
{
}

int Pass::checkClientLevel(CanClient *client)
{
	if (client->getMemberLevel() & PASS_FIN == 0)
	{
		return (true);
	}
	return (false);
}

int Pass::determineFlag(void)
{
	return (-1);
}

const char *Pass::incorrectPassException::what() const throw()
{
	return ("Pass : Incorrect Password !");
}
