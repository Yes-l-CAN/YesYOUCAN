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
    int serverPW = atoi(server->getPassWord().c_str());
    int clientPW = atoi(cmd[2].c_str());
    if (serverPW == clientPW)
    {
      client->setMemberLevel(PASS_FIN);
    }
    else
    {
      throw incorrectPassException();
    }
}

int Pass::isValidFormat(void)
{
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
  return ("Pass : Incorrect Password ! \r\n");
}

const char *Pass::alreadyRegisteredException::what() const throw() {
  return ("Pass : Password already registered ! \r\n");
}

