#include "Bot.hpp"
#include "Operation.hpp"

Bot::Bot(): word("42Seoul"), botMessage("weLove42Seoul") {}

Bot::~Bot() {}

// Bot::Bot(const Bot &obj)
// {
// 	// Deprecated.
// }

// Bot &Bot::operator=(const Bot &obj)
// {
// 	// Deprecated.
// 	return (*this);
// }

int Bot::findWord(std::string message)
{
	if(message.find(this->word) != std::string::npos)
		return (TRUE);	
	return (FALSE);
}


void Bot::executeBot(std::string message, CanClient *client)
{
	if(findWord(message) == TRUE)
		client->addSendBuff(botMessage);
}

void Bot::executeBot(std::string message, CanChannel *channel)
{
	if(findWord(message) == TRUE)
	{
		std::map<int, CanClient *>::iterator it;
		for(it = channel->getClientList().begin(); it != channel->getClientList().end(); it++)
		{
			it->second->addSendBuff(botMessage);
		}
	}
}