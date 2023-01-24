#include "Pass.hpp"
#include "Operation.hpp"

Pass::Pass() {}

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
    if (server->getPassWord() == cmd[2])
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

