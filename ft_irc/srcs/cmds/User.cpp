#include "User.hpp"
#include "Operation.hpp"

int User::validCheck(void)
{
	// if
}

void User::setClientUser(CanClient *client)
{
	if (cmd.size() != 5)
	{
		throw invalidFormatException();
	}

	if (client->getMemberLevel() < NICK_FIN)
	{
		throw noNickExistException();
	}

	if (client->getMemberLevel() > NICK_FIN)
	{
		throw alreadyRegisteredException();
	}

	if (validCheck() == FALSE)
	{
	}
}

void User::noticeNameReplaced(void)
{
}

void User::welcome2CanServ(void)
{
}

int User::isValidFormat(void)
{
}

int User::checkClientLevel(CanClient *client)
{
	if (client->getMemberLevel() & PASS_FIN == 0 || \
		client->getMemberLevel() & USER_FIN == 1)
	{
		return (false);
	}
	return (true);
}

int User::determineFlag(void)
{
	return (0);
}

const char *User::noNickExistException::what() const throw()
{
	return ("USER: Nick command needed");
}

const char *User::alreadyRegisteredException::what() const throw()
{
	return ("USER : You already registered");
}

const char *User::minUserLenException::what() const throw()
{
	return ("USER : ");
}

const char *User::spaceWithoutColonException::what() const throw()
{
	return ("USER : incorrect password");
}