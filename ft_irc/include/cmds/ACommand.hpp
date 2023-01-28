#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "CanChannel.hpp"
#include "CanClient.hpp"
#include "CanServer.hpp"
#include <cstdlib>
#include <exception>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#define MAXBUFLEN 512

class ACommand
{
  protected:
    CanServer*  server;
    CanChannel* channel;

    int flag;
    int size;

    std::vector<std::string> cmd;
    ACommand(const ACommand& obj);            // No use.
    ACommand& operator=(const ACommand& obj); // No use.

  public:
    ACommand();
    ACommand(CanServer* serv);
    virtual ~ACommand();
    virtual int isValidFormat(void) = 0;
    virtual int checkClientLevel(CanClient* client) = 0;
    virtual int determineFlag(void) = 0;

    void setFlag(void);
    void setSize(void);
    void setCmd(std::vector<std::string> cmd);

    int getFlag(void) const;
    int getSize(void) const;
};

#endif