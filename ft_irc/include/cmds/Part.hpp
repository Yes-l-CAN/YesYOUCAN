#ifndef COMMAND_PART_HPP
#define COMMAND_PART_HPP

#include "ACommand.hpp"

class Part : public ACommand
{
  private:
    Part(const Part& obj);            // No use.
    Part& operator=(const Part& obj); // No use.

  public:
    Part();
    Part(CanServer* serv);
    ~Part();
    void partOn(CanClient* client);

    int  isLastMember(void);
    void eraseChannel(CanClient* client);
    void channelClose(void);
    void operatorChanged(CanClient* client);

    int isValidFormat(void);
    int checkClientLevel(CanClient* client);
    int determineFlag(void);
};

#endif // COMMAND_PART_HPP
