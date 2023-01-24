#include "Join.hpp"
#include "Operation.hpp"

Join::Join() {}

Join::~Join() {}

Join::Join(const Join &obj)
{
	// Deprecated.
}

Join &Join::operator=(const Join &obj)
{
	// Deprecated.
	return (*this);
}

void Join::joinOn(CanClient *client)
{
  // flag JOIN <channel>
  try
  {
    isValidFormat();
    checkClientLevel(client);

    std::vector<std::string>::iterator it;
    for (it = cmd.begin() + 2;it != cmd.end();it++)
    {
      if (*it == "0")
      {// JOIN 0 => channel PART 시 메시지 첨부 기능까지 고려할 것인지 의논 필요
        leaveAll(client);
        continue;
      }

      if (isExistChannel(*it) == FALSE)
        addChannel(*it);
      else
      {
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
  }
  catch(const std::exception& e)
  {
    send(client->getSockFd(), e.what(), strlen(e.what()), 0);
  }
}

int Join::isKicked(CanClient *client)
{
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
    std::map<std::string, CanChannel *>::iterator it;
    std::string msgBuf;
    for(it = client->getChannelList().begin(); it != client->getChannelList().end(); it++)
    {
      msgBuf = ":" + client->getUsername() + " PART " + it->second->getChannelName() + "\r\n";
      it->second->broadcast(msgBuf);
      it->second->deleteClientElement(client->getSockFd());
      if (it->second->getClientList().size() == 0)
      {
        server->deleteChannelElement(it->second->getChannelName());
      }
    }
  }
}

void Join::addClient(CanClient *client)
{
  if (client != NULL)
  {
    channel->addClientElement(client->getSockFd(), client);
    client->addChannelElement(channel->getChannelName(), channel);
  }
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

  msgBuff = ":" + client->getUsername() + " JOIN #" + channel->getChannelName() + "\r\n";
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

  // JOIN 0 => channel PART 시 메시지 첨부 기능까지 고려할 것인지 의논 필요
  if (getFlag() != determineFlag())
  {
    throw invalidFormatException();
  }
  return (TRUE);
}

int Join::checkClientLevel(CanClient *client) {
  if (client->getMemberLevel() & CERTIFICATION_FIN == 0) {
    throw noAuthorityException();
  }
  return (TRUE);
}

int Join::determineFlag(void) { return (0); }
// JOIN 0 => channel PART 시 메시지 첨부 기능까지 고려할 것인지 의논 필요

const char *Join::invalidChannelException::what() const throw() {
  return "Join : Invalid Channel !";
}

const char *Join::alreadyJoinedException::what() const throw() {
  return "Join : Already joined !";
}

const char *Join::channelOverflowException::what() const throw() {
  return "Join : channel Overflow";
}

const char *Join::kickedException::what() const throw() {
  return "Join : cannot join channels that have been kicked. ";
}
