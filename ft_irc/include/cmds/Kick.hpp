
#ifndef COMMAND_KICK_HPP
#define COMMAND_KICK_HPP

#include "ACommand.hpp"

#define MAX_KICK_NUM 1

class Kick : public ACommand
{
private:
	CanClient *user;

	Kick(const Kick &obj); // Deprecated.
	Kick& operator=(const Kick &obj); // Deprecated.
public:
	Kick();
	Kick(CanServer *serv);
	~Kick();
	void onCommand(CanClient *client);
	// std::map<CanChannel *, int> getChannel(CanClient *client);

	void isMemberInChannel(CanClient *client);

	int isOperator(CanClient *client);
	void changeChannelStatus(CanClient *client);
	void sendMSG(CanClient *client);

	int isValidFormat(void);
	int checkClientLevel(CanClient *client);
	int determineFlag(void);

	// class notOperatorException : public std::exception
	// {
	// 	virtual const char *what() const throw();
	// };

	// class noSuchUserException : public std::exception
	// {
	// 	virtual const char *what() const throw();
	// };

	// class noSuchChannelException : public std::exception
	// {
	// 	virtual const char *what() const throw();
	// };
};

#endif // COMMAND_KICK_HPP
