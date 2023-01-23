#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>
#include <string>
#include "CanChannel.hpp"

class Bot
{
private:
	std::string word;

public:
	Bot();
	~Bot();
	void findWord();
	void sendMessage(CanChannel *channel);
};

#endif