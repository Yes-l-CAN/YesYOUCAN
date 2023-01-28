#ifndef COMMAND_PASS_HPP
#define COMMAND_PASS_HPP

#include "ACommand.hpp"

#define ERR_PASSWDMISMATCH 464
#define ERR_ALREADYREGISTERED 462

class Pass : public ACommand
{
  private:
    Pass(const Pass& obj);            // No use.
    Pass& operator=(const Pass& obj); // No use.

  public:
    Pass();
    Pass(CanServer* serv);
    ~Pass();
    void passOn(CanClient* client);
    void passCmp(CanClient* client);

    int isValidFormat(void);
    int checkClientLevel(CanClient* client);
    int determineFlag(void);
};

#endif // COMMAND_PASS_HPP
