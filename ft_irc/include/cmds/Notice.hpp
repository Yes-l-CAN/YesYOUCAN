
#ifndef COMMAND_NOTICE_HPP
#define COMMAND_NOTICE_HPP

#include "ACommand.hpp"

class Notice : public ACommand
{
  protected:
    Notice(const Notice& obj);            // No use.
    Notice& operator=(const Notice& obj); // No use.

  public:
    Notice();
    Notice(CanServer* serv);
    ~Notice();
    void noticeOn(CanClient* client);

    void        noticeToChannel(void);
    CanChannel* isExistChannelName(std::string name);
    CanClient*  isExistNickname(std::string name);
    int         isKicked(CanClient* clinet, CanChannel* channel);

    void executeNotice(CanClient* client);

    int isValidFormat(void);
    int checkClientLevel(CanClient* client);
    int determineFlag(void);
};

#endif // COMMAND_NOTICE_HPP
