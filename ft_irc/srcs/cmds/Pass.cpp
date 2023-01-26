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
    std::stringstream sstm;
    sstm << numeric << " " << client->getSockFd();
    std::string msgBuf = sstm.str();
    switch(numeric)
    {
    case ERR_UNKNOWNERROR:
      msgBuf += " PASS :Invalid Format error !";
      break;

    case ERR_PASSWDMISMATCH:
      msgBuf += " :Password incorrect";
      break;

    case ERR_ALREADYREGISTERED:
      msgBuf += " :Not enough parameters";
      break;

    default:
      break;
    }

    msgBuf += "\r\n";
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
      throw(ERR_PASSWDMISMATCH);
    }
}

int Pass::isValidFormat(void)
{
  if (getSize() < 2)
    throw ERR_UNKNOWNERROR;
  return (TRUE);
}

int Pass::checkClientLevel(CanClient *client)
{
  if ((client->getMemberLevel() & PASS_FIN) != 0) {
    throw (ERR_ALREADYREGISTERED);
  }
  return (TRUE);
}

int Pass::determineFlag(void) { return (-1); }

// // ERR_PASSWDMISMATCH (464) :Password incorrect
const char *Pass::incorrectPassException::what() const throw() {
  return ("Pass : Incorrect Password ! \r\n");
}

// ERR_ALREADYREGISTERED (462) "<client> :You may not reregister"
const char *Pass::alreadyRegisteredException::what() const throw() {
  return ("Pass : Password already registered ! \r\n");
}
