#include "Pass.hpp"
#include "Operation.hpp"

Pass::Pass() {}

Pass::Pass(CanServer *serv) : ACommand(serv){
  	this->server = serv;
}

Pass::~Pass() {}

// Pass::Pass(const Pass &obj)
// {
// 	// Deprecated.
// }

// Pass &Pass::operator=(const Pass &obj)
// {
// 	// Deprecated.
// 	return (*this);
// }

void Pass::passOn(CanClient *client)
{
  try
  {
	std::cout << "inside PASS" << std::endl;
    isValidFormat();
    checkClientLevel(client);
    passCmp(client);
  }
  catch(const std::exception& e)
  {
    std::string msgBuf = e.what();
    client->addSendBuff(msgBuf);
  }
}

void Pass::passCmp(CanClient *client) 
{
  // flag PASS <password> 
    std::cout << "server password"  << server->getPassWord() << std::endl;
    int serverPW = atoi(server->getPassWord().c_str());
    int clientPW = atoi(cmd[2].c_str());
    if (serverPW == clientPW)
    {
      std::cout << "hi" << std::endl;
      client->setMemberLevel(PASS_FIN);
    }
    else
    {
      throw incorrectPassException();
    }
}

int Pass::isValidFormat(void)
{
  // std::vector<std::string>::iterator it;
  // for(it = cmd.begin(); it != cmd.end(); ++it)
  // {
  //   std::cout << "cmd:: " << *it << std::endl;
  //   sleep(1);
  // }
  // sleep(1);
  // std::cout << "get Size :: " << getSize() << std::endl;
  // sleep(10);
  if (getSize() < 2)
    throw invalidFormatException();
  return (TRUE);
}

int Pass::checkClientLevel(CanClient *client) {
  if ((client->getMemberLevel() & PASS_FIN) != 0) {
    std::cout << "getMemLv :: " << client->getMemberLevel() << std::endl;
    std::cout << "PASS_FIM" << PASS_FIN << std::endl;
    throw alreadyRegisteredException();
  }
  return (TRUE);
}

int Pass::determineFlag(void) { return (-1); }

const char *Pass::incorrectPassException::what() const throw() {
  return ("Pass : Incorrect Password ! \n");
}

const char *Pass::alreadyRegisteredException::what() const throw() {
  return ("Pass : Password already registered ! \n");
}

