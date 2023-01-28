#ifndef BOT_HPP
#define BOT_HPP

#include "CanChannel.hpp"
#include <iostream>
#include <string>

class Bot
{
  private:
    std::string word;
    std::string botMessage;
    Bot(const Bot& obj);            // No use.
    Bot& operator=(const Bot& obj); // No use.
  public:
    Bot();
    ~Bot();
    int  findWord(std::string message);
    void sendMessage(CanChannel* channel);
    void executeBot(std::string message, CanClient* dstClient, CanClient* sndClient);
    void executeBot(std::string message, CanChannel* channel);
};

#endif