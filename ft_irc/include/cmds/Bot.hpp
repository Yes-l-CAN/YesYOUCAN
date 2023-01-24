#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>
#include <string>
#include "CanChannel.hpp"

class Bot
{
private:
	std::string word;
	Bot(const Bot &obj); // Deprecated.
	Bot& operator=(const Bot &obj); // Deprecated.
public:
	Bot();
	~Bot();
	void findWord();
	void sendMessage(CanChannel *channel);
};

#endif