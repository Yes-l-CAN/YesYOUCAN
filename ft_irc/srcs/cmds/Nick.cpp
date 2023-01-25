#include "Nick.hpp"
#include "Operation.hpp"

char Nick::invalid[8] = {' ', ',', '*', '?', '!', '@', '.', '#'};


Nick::Nick() {}

Nick::Nick(CanServer *serv) : ACommand(serv){
}

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
  std::cout << "hasdfasdfasdf" << std::endl;
    isValidFormat(); 
    checkClientLevel(client);
    validCheck();
    checkUsedNick();
    setClientNick(client);
	if((client->getMemberLevel() & CERTIFICATION_FIN) == CERTIFICATION_FIN)
		welcome2CanServ(client);
  }
  catch(const std::exception& e)
  {
    std::string msgBuf = e.what();
    client->addSendBuff(msgBuf);
  }
  
}

void Nick::welcome2CanServ(CanClient *client)
{
    // 001 :<client> :<msg>
	std::string userName = cmd[2];
	std::string serverName = static_cast<std::string>(SERVERNAME);
	std::string msgBuf = "001 :" + userName + " :Welcome, " + userName + "! Your host is " + serverName + "\n"; 
	client->addSendBuff(msgBuf);	
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
  std::cout << "getsize() [Nick] :: " << getSize() << std::endl;
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
	if((client->getMemberLevel() & (PASS_FIN | USER_FIN)) ==  (PASS_FIN | USER_FIN))
      	client->setMemberLevel(CERTIFICATION_FIN);
	else
		client->setMemberLevel(NICK_FIN);
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
