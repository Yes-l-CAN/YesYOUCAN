#include "Notice.hpp"

#include "Operation.hpp"

Notice::Notice() {}

Notice::~Notice() {}

void Notice::noticeOn(CanClient *client) 
{
  // flag NOTICE <target> <text to be sent>
  try
  {
    isValidFormat();
    checkClientLevel(client);

    std::string target = cmd[2];
    std::string msgBuf = "NOTICE " + target + " :" + cmd[3] + "\r\n";
    if (target.begin()[0] == '#') // channel
    {
      isExistChannelName(target);
      channel = server->getChannelList().find(target)->second;
      channel->broadcast(msgBuf);
    }
    else  // client's nickname
    {
      std::map<int, CanClient *>::iterator it = isExistNickname(target);
      it->second->setSendBuff(msgBuf);
      it->second->cSend
    }
  }
  catch(const std::exception& e)
  {
    throw e;
  }
  
}

// std::map<CanChannel *, int> Notice::getChannel(CanClient *client) {}

int Notice::noticeToChannel(void) {}

int Notice::isExistChannelName(std::string name)
{
  if (server->getChannelList().find(name) == server->getChannelList().end())
  {
    throw noSuchChannelException();
  }
  return (TRUE);
}

std::map<int, CanClient *>::iterator Notice::isExistNickname(std::string name)
{
  std::map<int, CanClient *>::iterator it;
  for (it = server->getClientList()->begin(); it != server->getClientList()->end(); it++)
  {
    if (it->second->getNickname() == name)
    {
      break ;
    }
  }
  if (it == server->getClientList()->end())
  {
    throw noSuchNickException();
  }
  return (it);
}

int Notice::isValidFormat(void)
{
  // flag NOTICE <target> <text to be sent>
  if (getSize() != 3)
  {
    throw invalidFormatException();
  }

  return (TRUE);
}

int Notice::checkClientLevel(CanClient *client) {
  if (client->getMemberLevel() & CERTIFICATION_FIN == 0) {
    throw noAuthorityException();
  }
  return (TRUE);
}

int Notice::determineFlag(void) { return (1); }

const char *Notice::noSuchNickException::what() const throw() {
  return ("Notice Error! : Threre's no such nick!");
}

const char *Notice::noSuchChannelException::what() const throw() {
  return ("Notice Error! : Threre's no such channel!");
}

const char *Notice::replyAnywayException::what() const throw() {
  return ("Notice Error! : replied anyway!");
}

const char *Notice::kickedUserException::what() const throw() {
  return ("Notice Error! : Already kicked user!");
}
