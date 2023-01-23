#ifndef COMMAND_QUIT_HPP
#define COMMAND_QUIT_HPP

#include "ACommand.hpp"

class Quit : public ACommand
{
private:
public:
	Quit();
	~Quit();
	void quitOn(CanClient *client);
	int isValidFormat(void);
	int checkClientLevel(CanClient *client);
	int determineFlag(void);
};

#endif // COMMAND_QUIT_HPP
