#include "Quit.hpp"
#include "Operation.hpp"

int Quit::isValidFormat(void)
{

}

int Quit::checkClientLevel(CanClient *client)
{
	if (client->getMemberLevel() & CERTIFICATION_FIN == 0)
	{
		return (false);
	}
	return (true);
}

int Quit::determineFlag(void)
{
	return (1);
}
