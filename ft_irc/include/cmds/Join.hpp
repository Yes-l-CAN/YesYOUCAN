#ifndef COMMAND_JOIN_HPP
#define COMMAND_JOIN_HPP

#include "ACommand.hpp"

#define ADD_LIMIT 1
#define MAX_MEMBER 10

class Join : public ACommand
{
  private:
    Join(const Join& obj);            // No use.
    Join& operator=(const Join& obj); // No use.
  public:
    Join();
    Join(CanServer* serv);
    ~Join();
    void joinOn(CanClient* client);

    int  isKicked(CanClient* client);
    int  isExistChannel(std::string channelName);
    void leaveAll(CanClient* client);
    void addClient(CanClient* client);
    void addChannel(std::string channelName);
    void sendMSG(CanClient* client);
    int  isAlreadyJoined(CanClient* client);

    int isValidFormat(void);
    int checkClientLevel(CanClient* client);
    int determineFlag(void);

    CanChannel* getChannel(std::string& channelName);
};

#endif // COMMAND_JOIN_HPP
