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
  catch(int numeric)
  {
    std::stringstream sstm;
    sstm << numeric << " " << client->getNickname();
    std::string msgBuf =  sstm.str();
    switch (numeric)
    {
    case ERR_UNKNOWNERROR:
      msgBuf += " PART :Invalid Format error !";
      break;

    case ERR_NOTREGISTERED:
      msgBuf += " :You have not registered. Register PASS, USER, NICK !";
      break;

    case ERR_NOSUCHCHANNEL:
      msgBuf += " " + cmd[2] + " :No such channel";
      break;

    case ERR_NOTONCHANNEL:
      msgBuf += " " + cmd[2] + " :You're not on that channel";
      break;

    default:
      break;
    }
  
    msgBuf += "\r\n";
    client->addSendBuff(msgBuf);
  }
}

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
  if (client->getChannelList().find(cmd[2]) == client->getChannelList().end())
  {
    throw ERR_NOTONCHANNEL;
  }
  this->channel = client->getChannelList().find(cmd[2])->second; 
  std::string msgBuf = ":" + client->getNickname() + " PART " + channel->getChannelName() ;
  if (getFlag() == 1)
  {
    msgBuf += " :" + cmd[3];
  }
  msgBuf += "\r\n";
  client->addSendBuff(msgBuf); 
  channel->broadcast(msgBuf, client);
}

int Part::isValidFormat(void)
{
  // flag PART <channel> [reason]
  if (getSize() < 2 || getSize() > 3)
  {
    throw ERR_UNKNOWNERROR;
  }

  if (server->getChannelList().find(cmd[2]) == server->getChannelList().end())
  {
    throw ERR_NOSUCHCHANNEL;
  }
  return (TRUE);
}

int Part::checkClientLevel(CanClient *client) {
  if ((client->getMemberLevel() & CERTIFICATION_FIN) == 0) {
    throw ERR_NOTREGISTERED;
  }
  return (TRUE);
}

int Part::determineFlag(void) { return (1); }

// // ERR_NOSUCHCHANNEL (403)   "<client> <channel> :No such channel"
// const char *Part::noSuchChannelException::what() const throw() 
// {
//   return ("Part : No such channel! \r\n");
// }

// // ERR_NOTONCHANNEL (442)   "<client> <channel> :You're not on that channel"
// const char *Part::notOnChannelException::what() const throw() {
//   return ("Part : Not on channel !\r\n");
// }
