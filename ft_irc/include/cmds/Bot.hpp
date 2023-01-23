#ifndef BOT_HPP
#define BOT_HPP

#include <iostream>
#include <string>
#include "CanChannel.hpp"

class Bot
{
	private:
		std::string	word;
	public:
		void findWord();
		void sendMessage(CanChannel *channel);
};

#endif