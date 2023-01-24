#ifndef COMMAND_PRVMSG_HPP
#define COMMAND_PRVMSG_HPP

#include "ACommand.hpp"
#include "Notice.hpp"
#include "Bot.hpp"

class Prvmsg : public Notice
{
private:
	Bot *bot;
	Prvmsg(const Prvmsg &obj); // Deprecated.
	Prvmsg& operator=(const Prvmsg &obj); // Deprecated.
public:

	Prvmsg();
	~Prvmsg();
	void prvMSGOn(CanClient *client);
	int isValidFormat(void);
	int checkClientLevel(CanClient *client);
	int determineFlag(void);
};

#endif // COMMAND_PRVMSG_HPP
