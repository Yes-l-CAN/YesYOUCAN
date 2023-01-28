
#ifndef COMMAND_KICK_HPP
#define COMMAND_KICK_HPP

#include "ACommand.hpp"

#define MAX_KICK_NUM 1

class Kick : public ACommand
{
  private:
    CanClient* user;

    Kick(const Kick& obj);            // No use.
    Kick& operator=(const Kick& obj); // No use.
  public:
    Kick();
    Kick(CanServer* serv);
    ~Kick();
    void kickOn(CanClient* client);

    void isMemberInChannel(CanClient* client);

    int  isOperator(CanClient* client);
    void changeChannelStatus(CanClient* client);
    void sendMSG(CanClient* client);

    int isValidFormat(void);
    int checkClientLevel(CanClient* client);
    int determineFlag(void);
};

#endif // COMMAND_KICK_HPP
