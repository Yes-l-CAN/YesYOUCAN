#include "Kick.hpp"

#include "Operation.hpp"

Kick::Kick() {}

Kick::Kick(CanServer *serv) : ACommand(serv){}

Kick::~Kick() {}

void Kick::kickOn(CanClient *client)
{
  try
  {

  	if (getSize() != 3)
  	{
      // ERR_NEEDMOREPARAMS (461) :Not enough parameters
   		throw invalidFormatException();
  	}
  	if ((client->getMemberLevel() & CERTIFICATION_FIN) == 0) 
	  {
      // ERR_NOTREGISTERED (451)   "<client> :You have not registered"
   		throw noAuthorityException();
  	}

    isMemberInChannel(client);
    if (isOperator(client) == FALSE)
    {
      // ERR_NOTREGISTERED (451)   "<client> :You have not registered"
      // ERR_NEEDMOREPARAMS (461) :Not enough parameters
      throw notOperatorException();
    }
    sendMSG(client);
    changeChannelStatus(this->user);
  }
  catch(const std::exception& e)
  {
    std::string msgBuf = e.what();
    client->addSendBuff(msgBuf);  
  }
}

void Kick::isMemberInChannel(CanClient *client)
{
	if(client->getChannelList().find(cmd[2]) == client->getChannelList().end())
		throw(noSuchChannelException());
	this->channel = client->getChannelList().find(cmd[2])->second;
	std::map<int, CanClient *>::iterator it;
	for(it = channel->getClientList().begin(); it != channel->getClientList().end(); it++)
	{
		if(it->second->getNickname() == cmd[3])
		{
			this->user = it->second;
			return ;
		}
	}
	throw(noSuchUserException());
}


int Kick::isOperator(CanClient *client)
{
	(void) client;
//   if (channel->getClientList().begin()->first == client->getSockFd())
//   {
//     return (TRUE);
//   }
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
  channel->broadcast(msgBuf, client);
}

int Kick::isValidFormat(void)
{
//   if (getSize() != 3)
//   {
//     throw invalidFormatException();
//   }
  return (TRUE);
}

int Kick::checkClientLevel(CanClient *client) {
  if ((client->getMemberLevel() & CERTIFICATION_FIN) == 0) {
        // ERR_NOTREGISTERED (451)   "<client> :You have not registered"
    throw noAuthorityException();
  }
  return (TRUE);
}

int Kick::determineFlag(void) { return (1); }

// ERR_NOPRIVILEGES (481)  "<client> :Permission Denied- You're not an IRC operator"
const char *Kick::notOperatorException::what() const throw() {
  return "Kick : not Operator ! No authority !\r\n";
}

// ERR_NOSUCHNICK (401)   "<client> <nickname> :No such nick/channel"
const char *Kick::noSuchUserException::what() const throw() {
  return "Kick : No such user !\r\n";
}

// ERR_NOSUCHCHANNEL (403)   "<client> <channel> :No such channel"
const char *Kick::noSuchChannelException::what() const throw() {
  return "Kick : No such channel !\r\n";
}
