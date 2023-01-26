#include "Pass.hpp"
#include "Operation.hpp"


Pass::Pass() {}

Pass::Pass(CanServer *serv) : ACommand(serv){
  	this->server = serv;
}

Pass::~Pass() {}


void Pass::passOn(CanClient *client)
{
  try
  {
    isValidFormat();
    checkClientLevel(client);
    passCmp(client);
  }
  catch(int numeric)
  {
    std::string msgBuf;
    if (numeric == 464)
      msgBuf = std::to_string(numeric) + client->getNickname() + ":Password incorrect\r\n";
    else if (numeric == 461)
      msgBuf = std::to_string(numeric) + client->getNickname() + "::Not enough parameters\r\n";
    client->addSendBuff(msgBuf);
  }
}

void Pass::passCmp(CanClient *client) throw(int)
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
      throw (464);
    }
}

int Pass::isValidFormat(void)
{
  if (getSize() < 2)
    throw invalidFormatException();
  return (TRUE);
}

int Pass::checkClientLevel(CanClient *client) throw(int)
{
  if ((client->getMemberLevel() & PASS_FIN) != 0) {
    throw (461);
  }
  return (TRUE);
}

int Pass::determineFlag(void) { return (-1); }

// // ERR_PASSWDMISMATCH (464) :Password incorrect
// const char *Pass::incorrectPassException::what() const throw() {
//   return ("Pass : Incorrect Password ! \r\n");
// }
// // ERR_NEEDMOREPARAMS (461) :Not enough parameters
// const char *Pass::alreadyRegisteredException::what() const throw() {
//   return ("Pass : Password already registered ! \r\n");
// }

