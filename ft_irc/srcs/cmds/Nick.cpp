#include "Nick.hpp"
#include "Operation.hpp"

char Nick::invalid[8] = {' ', ',', '*', '?', '!', '@', '.', '#'};

Nick::Nick() {}

Nick::~Nick() {}

// Nick::Nick(const Nick &obj)
// {
// 	// Deprecated.
// }

// Nick &Nick::operator=(const Nick &obj)
// {
// 	// Deprecated.
// 	return (*this);
// }

void Nick::nickOn(CanClient *client)
{
  try
  {
	std::cout << "inside NICK" << std::endl;
    isValidFormat();
    checkClientLevel(client);
    validCheck();
    checkUsedNick();
    setClientNick(client);
  }
  catch(const std::exception& e)
  {
    std::string msgBuf = e.what();
    client->addSendBuff(msgBuf);
  }
  
}

int Nick::validCheck(void) 
{
  // flag NICK <nickname>
  std::string nickName = cmd[2];
  for (int i = 0; i < 8; i++) {
    if (nickName.find(invalid[i]) != std::string::npos) 
    {
      throw invalidNickException();
    }
  }
  if (nickName[0] == '$' || nickName[0] == ':') 
  {
    throw invalidNickException();
  }
  return (TRUE);
}

int Nick::checkUsedNick(void) 
{
  // flag NICK <nickname>
  std::map<int, CanClient *>::iterator cit;
  std::string nickName = cmd[2];
  
  for (cit = server->getClientList()->begin();
       cit != server->getClientList()->end(); cit++) 
  {
    if (cit->second->getNickname() == nickName) 
    {
      throw usedNickException();
    }
  }
  return (TRUE);
}

int Nick::isValidFormat(void) 
{
  // flag NICK <nickname>
  if (getSize() != 2)
  {
    throw invalidFormatException();
  }
  return (TRUE);
}

void Nick::setClientNick(CanClient *client) 
{
  // flag NICK <nickname>

  std::string nickName = cmd[2];
  client->setNickname(nickName);
  client->setMemberLevel(NICK_FIN);
	if ((client->getMemberLevel() & (PASS_FIN | NICK_FIN | USER_FIN)) == (PASS_FIN | NICK_FIN | USER_FIN))
	{
		client->setMemberLevel(CERTIFICATION_FIN);
	}
}

int Nick::checkClientLevel(CanClient *client) {
  if ((client->getMemberLevel() & PASS_FIN) == 0) 
  {
    throw noAuthorityException();
  }
  return (TRUE);
}

int Nick::determineFlag(void) { return (0); }

const char *Nick::invalidNickException::what() const throw() {
  return ("Nick Error : invalid nick! \n");
}

const char *Nick::usedNickException::what() const throw() {
  return ("Nick Error : already used nick! \n");
}
