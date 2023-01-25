#include "User.hpp"
#include "Operation.hpp"

User::User() {}

User::User(CanServer *serv) : ACommand(serv){}

User::~User() {}

// User::User(const User &obj)
// {
// 	// Deprecated.
// }

// User &User::operator=(const User &obj)
// {
// 	// Deprecated.
// 	return (*this);
// }

void User::userOn(CanClient *client)
{
	try
	{
		std::cout << "inside USER" << std::endl;
		isValidFormat();
		checkClientLevel(client);
		validCheck();
		setClientUser(client);
		if((client->getMemberLevel() & CERTIFICATION_FIN) == CERTIFICATION_FIN)
				welcome2CanServ(client);
	}
	catch (const std::exception &e)
	{
		std::string msgBuf = e.what() ;
		client->addSendBuff(msgBuf);
	}
}

int User::validCheck(void)
{
	// flag USER <username> 0 * <realname>
	//  0   1     2         3 4  5

	if (cmd[2].length() < 1 || cmd[5].length() < 1)
	{
		throw minUserLenException();
	}

	if (cmd[5].find(" ") != std::string::npos && getFlag() == 0)
	{
		throw spaceWithoutColonException();
	}
	return (TRUE);
}

void User::setClientUser(CanClient *client)
{
	// flag USER <username> 0 * <realname>
	//  0   1     2         3 4  5

	client->setUsername(cmd[2]);
	client->setRealname(cmd[5]);
	if((client->getMemberLevel() & (PASS_FIN | NICK_FIN)) ==  (PASS_FIN | NICK_FIN))
      	client->setMemberLevel(CERTIFICATION_FIN);
	else
		client->setMemberLevel(USER_FIN);
}

void User::welcome2CanServ(CanClient *client)
{
    // 001 :<client> :<msg>
	std::string userName = cmd[2];
	std::string serverName = static_cast<std::string>(SERVERNAME);
	std::string msgBuf = "001 :" + userName + " :Welcome, " + userName + "! Your host is " + serverName + "\n"; 
	client->addSendBuff(msgBuf);	
}

int User::isValidFormat(void)
{
	// flag USER <username> 0 * <realname>
	if (getSize() != 5)
		throw invalidFormatException();
	return (TRUE);
}

int User::checkClientLevel(CanClient *client)
{
	if ((client->getMemberLevel() & PASS_FIN) == 0)
	{
		throw noAuthorityException();
	}
	else if ((client->getMemberLevel() & USER_FIN) != 0)
	{
		throw alreadyRegisteredException();
	}
	return (TRUE);
}

int User::determineFlag(void)
{
	return (1);
}

const char *User::alreadyRegisteredException::what() const throw()
{
	return ("USER : You already registered \n");
}

const char *User::minUserLenException::what() const throw()
{
	return ("USER : Minimum name Length = 1 \n");
}

const char *User::spaceWithoutColonException::what() const throw()
{
	return ("USER : Space without colon \n");
}
