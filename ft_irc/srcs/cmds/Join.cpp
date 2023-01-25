#include "Join.hpp"
#include "Operation.hpp"

Join::Join() {}
 
Join::Join(CanServer *serv) : ACommand(serv){}

Join::~Join() {}

// Join::Join(const Join &obj)
// {
// 	// Deprecated.
// }

// Join &Join::operator=(const Join &obj)
// {
// 	// Deprecated.
// 	return (*this);
// }

void Join::joinOn(CanClient *client)
{
  // flag JOIN <channel>
  try
  {
    isValidFormat();
    checkClientLevel(client);

      if (cmd[2] == "0")
      {
      
        leaveAll(client);
      }

      if (isExistChannel(cmd[2]) == FALSE)
           addChannel(cmd[2]);
      else
      {
        this->channel = getChannel(cmd[2]);
        isAlreadyJoined(client);
        isKicked(client);
      }

      if (channel->getClientList().size() < MAX_MEMBER)
      {
        addClient(client);
        sendMSG(client);
      }
      else
      {
        throw channelOverflowException();
      }
      
  }
  catch(const std::exception& e)
  {
    std::string msgBuf = e.what();
    client->addSendBuff(msgBuf);
  }
}

CanChannel *Join::getChannel(std::string &channelName)
{
  return (server->getChannelList().find(channelName)->second);
}

int Join::isKicked(CanClient *client)
{
  if(channel->getKickedList().empty())
    return (FALSE);
  if (channel->getKickedList().find(client->getSockFd()) != channel->getKickedList().end()) 
  {
    throw kickedException();
  }
  return (FALSE);
}

int Join::isExistChannel(std::string channelName)
{
  if (server->getChannelList().find(channelName) != server->getChannelList().end())
  {
    channel = server->getChannelList().find(channelName)->second;
    return (TRUE);
  }
  return (FALSE);
}

void Join::leaveAll(CanClient *client) 
{
  if (client != NULL)
  {
    std::map<std::string, CanChannel *>::iterator it = client->getChannelList().begin();
    std::string msgBuf;
    // for(it = client->getChannelList().begin(); it != client->getChannelList().end(); it++)
    while (client->getChannelList().size() != 0)
    {
      it = client->getChannelList().begin();
      msgBuf = ":" + client->getUsername() + " PART " + it->second->getChannelName() + "\n";
      it->second->broadcast(msgBuf);
      it->second->deleteClientElement(client->getSockFd());
      if (it->second->getClientList().size() == 0)
      {
        server->deleteChannelElement(it->second->getChannelName());
      }
      client->deleteChannelElement(it->second->getChannelName());
    }
  }
}

void Join::addClient(CanClient *client)
{
    channel->addClientElement(client->getSockFd(), client);
    client->addChannelElement(channel->getChannelName(), channel);
}

void Join::addChannel(std::string channelName)
{
  CanChannel *newCan = new CanChannel();

  newCan->setChannelName(channelName);
  server->addChannelElement(channelName, newCan);
  this->channel = newCan;
}

void Join::sendMSG(CanClient *client) 
{
  std::string msgBuff;
  // :<source> JOIN <channel>

  msgBuff = ":" + client->getNickname() + " JOIN " + channel->getChannelName() + "\r\n";
  channel->broadcast(msgBuff);
}

int Join::isAlreadyJoined(CanClient *client)
{
  if (client != NULL)
  {
    std::map<std::string, CanChannel *>::iterator find_it;
    std::map<std::string, CanChannel *>::iterator end_it;
    find_it = client->getChannelList().find(channel->getChannelName());
    end_it = client->getChannelList().end();
    if (find_it != end_it)
    {
      throw alreadyJoinedException();
    }
  }
  return (FALSE);
}

int Join::isValidFormat(void) 
{
  // flag JOIN <channel>

  if (getSize() < 2 || (getSize() > ADD_LIMIT + 1))
  {
    throw invalidFormatException();
  }

  if (getFlag() != determineFlag())
  {
    throw invalidFormatException();
  }
  return (TRUE);
}

int Join::checkClientLevel(CanClient *client) {
  if ((client->getMemberLevel() & CERTIFICATION_FIN) == 0) {
    throw noAuthorityException();
  }
  return (TRUE);
}

int Join::determineFlag(void) { return (0); }

const char *Join::invalidChannelException::what() const throw() {
  return "Join : Invalid Channel !\n";
}

const char *Join::alreadyJoinedException::what() const throw() {
  return "Join : Already joined !\n";
}

const char *Join::channelOverflowException::what() const throw() {
  return "Join : channel Overflow\n";
}

const char *Join::kickedException::what() const throw() {
  return "Join : cannot join channels that have been kicked. \n";
}
