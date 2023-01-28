#ifndef COMMAND_PRVMSG_HPP
#define COMMAND_PRVMSG_HPP

#include "ACommand.hpp"
#include "Bot.hpp"
#include "Notice.hpp"

class Prvmsg : public Notice
{
  private:
    void* target;
    Bot*  bot;
    Prvmsg(const Prvmsg& obj);            // No use.
    Prvmsg& operator=(const Prvmsg& obj); // No use.
  public:
    Prvmsg();
    Prvmsg(CanServer* serv);
    ~Prvmsg();
    void prvMSGOn(CanClient* client);
    int  isValidFormat(void);
    int  checkClientLevel(CanClient* client);
    int  determineFlag(void);
    void executePrvmsg(CanClient* client);

    void* getTarget(CanClient* client);
};

#endif // COMMAND_PRVMSG_HPP
