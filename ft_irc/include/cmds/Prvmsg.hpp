#ifndef COMMAND_PRVMSG_HPP
#define COMMAND_PRVMSG_HPP

#include "ACommand.hpp"
#include "Notice.hpp"
#include "Bot.hpp"

class Prvmsg : public Notice
{
private:
	Bot *bot;

public:

	Prvmsg();
	~Prvmsg();
	void prvMSGOn();
	int isValidFormat(void);
	int checkClientLevel(CanClient *client);
	int determineFlag(void);
};

#endif // COMMAND_PRVMSG_HPP