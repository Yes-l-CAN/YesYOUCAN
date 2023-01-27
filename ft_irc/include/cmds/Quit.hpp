#ifndef COMMAND_QUIT_HPP
#define COMMAND_QUIT_HPP

#include "ACommand.hpp"

class Quit : public ACommand
{
private:
	Quit(const Quit &obj); // Deprecated.
	Quit& operator=(const Quit &obj); // Deprecated.
public:
	Quit();
	Quit(CanServer *serv);
	~Quit();
	void onCommand(CanClient *client);
	void eraseFromList(CanClient *client);
	void msgToAllJoinedChannel(CanClient *client);

	int isValidFormat(void);
	int checkClientLevel(CanClient *client);
	int determineFlag(void);
};

#endif // COMMAND_QUIT_HPP
