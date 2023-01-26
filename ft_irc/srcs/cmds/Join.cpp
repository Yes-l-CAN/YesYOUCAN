#include "Join.hpp"
#include "Operation.hpp"

Join::Join() {}
 
Join::Join(CanServer *serv) : ACommand(serv){}

Join::~Join() {}


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
        return ;
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
    std::string excpMsg(const_cast<char *>(e.what()));
    // std::string msgBuf = "123 " + client->getNickname() + " : " + excpMsg;
    std::string msgBuf = excpMsg;
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
      msgBuf = ":" + client->getUsername() + " PART " + it->second->getChannelName() + "\r\n";
      it->second->broadcast(msgBuf, client);
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
  /*
    JOIN #welove42Seoul
    103.196.037.095.06667-010.019.227.116.51934: :poiupoiu!~katherine@121.135.181.61 JOIN #welove42Seoul
    103.196.037.095.06667-010.019.227.116.51934: :cadmium.libera.chat MODE #welove42Seoul +Cnst
    :cadmium.libera.chat 353 poiupoiu @ #welove42Seoul :@poiupoiu
    :cadmium.libera.chat 366 poiupoiu #welove42Seoul :End of /NAMES list.
  
   "<client> @ <channel> : @ <nick>{ [prefix]<nick>}"

   <client> <channel> :End of /NAMES list"

    :@hejangg
 :End of /NAMES list.
  */
  msgBuff =  " JOIN " + channel->getChannelName() + "\r\n";
  client->addSendBuff(msgBuff);
  msgBuff = "353 " + client->getNickname() + " @ " + channel->getChannelName() + " :@" + client->getNickname() + "\r\n";
  client->addSendBuff(msgBuff);
  msgBuff = "366 " + client->getNickname() + " " + channel->getChannelName() + " :End of /NAMES list." + "\r\n"; 
  client->addSendBuff(msgBuff);

  std::string memberBuff;
  memberBuff = ":" + client->getNickname() + " JOIN " + channel->getChannelName() + "\r\n";
  channel->broadcast(memberBuff, client);
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
    // ERR_NEEDMOREPARAMS (461) :Not enough parameters
    throw invalidFormatException();
  }

  if (getFlag() != determineFlag())
  {
        // ERR_NEEDMOREPARAMS (461) :Not enough parameters
    throw invalidFormatException();
  }
  return (TRUE);
}

int Join::checkClientLevel(CanClient *client) {
  if ((client->getMemberLevel() & CERTIFICATION_FIN) == 0) {
        // ERR_NOTREGISTERED (451)   "<client> :You have not registered"
    throw noAuthorityException();
  }
  return (TRUE);
}

int Join::determineFlag(void) { return (0); }

// ERR_USERONCHANNEL (443)   "<client> <nick> <channel> :is already on channel"
const char *Join::alreadyJoinedException::what() const throw() {
  return "Join : Already joined !\r\n";
}

// ERR_CHANNELISFULL (471)   "<client> <channel> :Cannot join channel (+l)"
const char *Join::channelOverflowException::what() const throw() {
  return " :Cannot join channel\r\n";
}

// ERR_BANNEDFROMCHAN (474) "<client> <channel> :Cannot join channel"
const char *Join::kickedException::what() const throw() {
  return "Join : cannot join channels that have been kicked. \r\n";
}
