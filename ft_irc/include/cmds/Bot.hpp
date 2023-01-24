#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>
#include <string>
#include "CanChannel.hpp"

class Bot
{
private:
	std::string word;
	std::string botMessage;
	Bot(const Bot &obj); // Deprecated.
	Bot& operator=(const Bot &obj); // Deprecated.
public:
	Bot();
	~Bot();
	int	 findWord(std::string message);
	void sendMessage(CanChannel *channel);
	void executeBot(std::string message, CanClient *client);
	void executeBot(std::string message, CanChannel *channel);
};

#endif