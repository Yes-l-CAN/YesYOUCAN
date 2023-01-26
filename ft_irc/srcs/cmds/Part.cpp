#include "Part.hpp"

#include "Operation.hpp"

Part::Part() {}

Part::Part(CanServer *serv) : ACommand(serv){}

Part::~Part() {}


void Part::partOn(CanClient *client)
{
  try
  {
    isValidFormat();
    checkClientLevel(client);
    operatorChanged(client);
    eraseChannel(client);
  }
  catch(const std::exception& e)
  {
      client->addSendBuff(e.what());
  }
}

// std::map<CanChannel *, int> Part::getChannel(CanClient *client) {}

int Part::isLastMember(void)
{
  return (channel->getClientList().size() == 0);
}

void Part::eraseChannel(CanClient *client)
{
  std::string channelName = cmd[2];
  client->deleteChannelElement(channelName);
  channel->deleteClientElement(client->getSockFd());

  if (isLastMember() == TRUE)
  {
    channelClose();
  }
}

void Part::channelClose(void)
{
    std::string channelName = cmd[2];
    server->deleteChannelElement(channelName);
}

void Part::operatorChanged(CanClient *client)
{
  this->channel = client->getChannelList().find(cmd[2])->second;
  std::string msgBuf = ":" + client->getUsername() + " PART " + channel->getChannelName();
  if (getFlag() == 1)
  {
    msgBuf += " :" + cmd[3];
  }
  msgBuf += "\r\n";
  channel->broadcast(msgBuf, client);
}

int Part::isValidFormat(void)
{
  // flag PART <channel> [reason]
  if (getSize() < 2 || getSize() > 3)
  {
    throw invalidFormatException();
  }

  if (server->getChannelList().find(cmd[2]) == server->getChannelList().end())
  {
    throw noSuchChannelException();
  }
  return (TRUE);
}

int Part::checkClientLevel(CanClient *client) {
  if ((client->getMemberLevel() & CERTIFICATION_FIN) == 0) {
    throw noAuthorityException();
  }
  return (TRUE);
}

int Part::determineFlag(void) { return (1); }

const char *Part::noSuchChannelException::what() const throw() 
{
  return ("Part : No such channel! \r\n");
}

const char *Part::notOnChannelException::what() const throw() {
  return ("Part : Not on channel !\r\n");
}
