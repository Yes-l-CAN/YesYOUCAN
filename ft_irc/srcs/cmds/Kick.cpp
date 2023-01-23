#include "Kick.hpp"
#include "Operation.hpp"

Kick::Kick() {}

Kick::~Kick() {}

void Kick::kickOn()
{
}

std::map<CanChannel *, int> Kick::getChannel(CanClient *client)
{
}

int Kick::isOperator(CanClient *client)
{
}

void Kick::changeChannelStatus(CanClient *client)
{
}

void Kick::snedMSG(CanClient *client)
{
}

int Kick::isValidFormat(void)
{
}

int Kick::checkClientLevel(CanClient *client)
{
	if (client->getMemberLevel() & CERTIFICATION_FIN)
	{
		return (false);
	}
	return (true);
}

int Kick::determineFlag(void)
{
	return (1);
}

const char *Kick::notOperatorException::what() const throw()
{
	return "Kick : not Operator ! No authority ";
}

const char *Kick::noSuchUserException::what() const throw()
{
	return "Kick : No such user !";
}

const char *Kick::noSuchChannelException::what() const throw()
{
	return "Kick : No such channel !";
}
