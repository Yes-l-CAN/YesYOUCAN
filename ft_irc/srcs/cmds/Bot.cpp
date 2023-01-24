#include "Bot.hpp"
#include "Operation.hpp"

Bot::Bot(): word("42Seoul") {}

Bot::~Bot() {}

Bot::Bot(const Bot &obj)
{
	// Deprecated.
}

Bot &Bot::operator=(const Bot &obj)
{
	// Deprecated.
	return (*this);
}

void Bot::findWord()
{

}

void Bot::sendMessage(CanChannel *channel)
{

}