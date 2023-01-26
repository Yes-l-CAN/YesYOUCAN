#include "Notice.hpp"

#include "Operation.hpp"

Notice::Notice() {}

Notice::Notice(CanServer *serv) : ACommand(serv){}

Notice::~Notice() {}

void Notice::noticeOn(CanClient *client) 
{
  // flag NOTICE <target> <text to be sent>
  try
  {
    isValidFormat();
    checkClientLevel(client);
	executeNotice(client);
  }
  catch(const std::exception& e)
  {
    std::string msgBuf = e.what();
    client->addSendBuff(msgBuf);
  }
  
}

void Notice::executeNotice(CanClient *client)
{
  	std::string targetName = this->cmd[2];
	std::string message = "Notice " + targetName + " : " + this->cmd[3] + "\n";
	if (targetName[0] == '#')
	{
		channel = isExistChannelName(targetName);
		if (isKicked(client, channel) == TRUE)
			throw(kickedUserException());
		channel->broadcast(message, client);
	} else {
				// send to Client ? 보다는 buffer에 저장이 더 맞을 듯...?=
		CanClient *pClient = isExistNickname(targetName);
		pClient->addSendBuff(message);
	}
}

// std::map<CanChannel *, int> Notice::getChannel(CanClient *client) {}

void Notice::noticeToChannel(void) {}

CanChannel *Notice::isExistChannelName(std::string name)
{
  std::map<std::string, CanChannel *>::iterator it;
  it = server->getChannelList().find(name);
  if (it == server->getChannelList().end())
  {
    throw noSuchChannelException();
  }
  return (it->second);
}

CanClient *Notice::isExistNickname(std::string name)
{
  std::map<int, CanClient *>::iterator it;
  for (it = server->getClientList().begin(); it != server->getClientList().end(); it++)
  {
    if (it->second->getNickname() == name)
    {
      return (it->second);
    }
  }
  throw noSuchNickException();
}

int Notice::isKicked(CanClient *client, CanChannel *channel)
{
  int clientFd = client->getSockFd();
  if (channel->getKickedList().find(clientFd) != channel->getKickedList().end())
  {
      return (TRUE);
  }
  return (FALSE);
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
  if ((client->getMemberLevel() & CERTIFICATION_FIN) == 0) {
    throw noAuthorityException();
  }
  return (TRUE);
}

int Notice::determineFlag(void) { return (1); }

// ERR_NOSUCHNICK (401)   "<client> <nickname> :No such nick/channel"
const char *Notice::noSuchNickException::what() const throw() {
  return (":No such nick/channel\r\n");
}

// ERR_NOSUCHCHANNEL (403)   "<client> <channel> :No such channel"
const char *Notice::noSuchChannelException::what() const throw() {
  return (":No such channel\r\n");
}

// const char *Notice::replyAnywayException::what() const throw() {
//   return ("Notice Error! : replied anyway! \r\n");
// }

// ERR_NOTREGISTERED (451)  "<client> :You have not registered"
const char *Notice::kickedUserException::what() const throw() {
  return ("Notice Error! : Already kicked user! \r\n");
}
