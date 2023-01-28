#ifndef COMMAND_PING_HPP
#define COMMAND_PING_HPP

#include "ACommand.hpp"

class Ping : public ACommand
{
  private:
    Ping(const Ping& obj);            // No use.
    Ping& operator=(const Ping& obj); // No use.

  public:
    Ping();
    Ping(CanServer* serv);
    ~Ping();
    void pingOn(CanClient* client);
    void pong(CanClient* client);

    int isValidFormat(void);
    int checkClientLevel(CanClient* client);
    int determineFlag(void);
};

#endif // COMMAND_PING_HPP
