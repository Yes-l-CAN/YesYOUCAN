#include "Kick.hpp"

#include "Operation.hpp"

Kick::Kick() {}

Kick::~Kick() {}

// Kick::Kick(const Kick &obj)
// {
// 	// Deprecated.
// }

// Kick &Kick::operator=(const Kick &obj)
// {
// 	// Deprecated.
// 	return (*this);
// }

void Kick::kickOn(CanClient *client)
{
  try
  {
    isValidFormat();
    checkClientLevel(client);

    if (isOperator(client) == FALSE)
    {
      throw notOperatorException();
    }
    sendMSG(client);
    changeChannelStatus(client);
  }
  catch(const std::exception& e)
  {
    std::string msgBuf = e.what();
    client->addSendBuff(msgBuf);  
  }
}

// std::map<CanChannel *, int> Kick::getChannel(CanClient *client)
// {

// }

int Kick::isOperator(CanClient *client)
{
  if (channel->getClientList().begin()->first == client->getSockFd())
  {
    return (TRUE);
  }
  return (FALSE);
}

void Kick::changeChannelStatus(CanClient *client)
{
  channel->addKickedListElement(client);
  channel->deleteClientElement(client->getSockFd());
  client->deleteChannelElement(channel->getChannelName());
}

void Kick::sendMSG(CanClient *client)
{
  // flag KICK <channel> <user> [reason]
  std::string msgBuf = ":" + client->getUsername() + " KICK " + cmd[2] + " " + cmd[3];
  if (getFlag() == 1)
  {
    msgBuf += " :" + cmd[4];
  } 
  msgBuf += "\r\n";
  channel->broadcast(msgBuf);
}

int Kick::isValidFormat(void)
{
  // flag KICK <channel> <user> [<comment>]

  if (getSize() < 3 || getSize() > 4)
  {
    throw invalidFormatException();
  }

  if (server->getChannelList().find(cmd[2]) == server->getChannelList().end())
  {
    throw noSuchChannelException();
  }
  else
  {
    channel = server->getChannelList().find(cmd[2])->second;
  }

  std::map<int, CanClient *>::iterator it ; 
  for (it = channel->getClientList().begin();it != channel->getClientList().end();it++)
  {
    if (it->second->getNickname() == cmd[3])
    {
      return (TRUE);
    }
  }
  if (it == channel->getClientList().end())
  {
    throw noSuchUserException();
  }
  return (FALSE);
}

int Kick::checkClientLevel(CanClient *client) {
  if ((client->getMemberLevel() & CERTIFICATION_FIN) == 0) {
    throw noAuthorityException();
  }
  return (TRUE);
}

int Kick::determineFlag(void) { return (1); }

const char *Kick::notOperatorException::what() const throw() {
  return "Kick : not Operator ! No authority !\n";
}

const char *Kick::noSuchUserException::what() const throw() {
  return "Kick : No such user !\n";
}

const char *Kick::noSuchChannelException::what() const throw() {
  return "Kick : No such channel !\n";
}
