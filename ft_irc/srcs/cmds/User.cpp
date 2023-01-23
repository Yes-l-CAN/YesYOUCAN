#include "User.hpp"
#include "Operation.hpp"

User::User()
{

}

User::~User()
{

}

void User::userOn(CanClient *client)
{
	try
	{
		isValidFormat();
		checkClientLevel(client);
		validCheck();
		setClientUser(client);
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
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

/* => username과 realname은 중복이 가능하다고 함
  // check used name 
  std::map<int, CanClient *>::iterator cit;
  std::vector<std::string>::iterator sit_username;
  std::vector<std::string>::iterator sit_realname;

  for (cit = server->getClientList()->begin(); cit != server->getClientList()->end(); cit++)
  {
	if (cit->second->getUsername() == *sit_username)
	{

	}
		  if (cit->second->getRealname() == *sit_Realname)
	{

	}
  }
*/
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
	client->setMemberLevel(USER_FIN);
	if (client->getMemberLevel() & (PASS_FIN | NICK_FIN | USER_FIN) == (PASS_FIN | NICK_FIN | USER_FIN))
	{
		client->setMemberLevel(CERTIFICATION_FIN);
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
	if (getSize() != 5)
		throw invalidFormatException();
	return (TRUE);
}

int User::checkClientLevel(CanClient *client)
{
	if (client->getMemberLevel() & PASS_FIN == 0)
	{
		throw noAuthorityException();
	}
	else if (client->getMemberLevel() & USER_FIN == 1)
	{
		throw alreadyRegisteredException();
	}
	return (TRUE);
}

int User::determineFlag(void)
{
	return (1);
}

const char *User::noAuthorityException::what() const throw()
{
	return ("USER: Password authentication required");
}

const char *User::alreadyRegisteredException::what() const throw()
{
	return ("USER : You already registered");
}

const char *User::minUserLenException::what() const throw()
{
	return ("USER : Minimum name Length = 1 ");
}

const char *User::spaceWithoutColonException::what() const throw()
{
	return ("USER : Space withcout colon");
}
