#ifndef COMMAND_JOIN_HPP
#define COMMAND_JOIN_HPP

#include "ACommand.hpp"

#define ADD_LIMIT 1
#define MAX_MEMBER 10

class Join : public ACommand
{
private:
	CanChannel *channel;

public:
	Join();
	~Join();
	void joinOn();

	int isKicked(CanClient *client);
	void leaveAll(CanClient *client);
	void addClient(CanClient *client);
	void addChannel(CanClient *client);
	void sendMSG(CanClient *client);

	int isValidFormat(void);
	int checkClientLevel(CanClient *client);
	int determineFlag(void);

	class invalidChannelException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class alreadyJoinedException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class channelOverflowException : public std::exception
	{
		virtual const char *what() const throw();
	};
};

#endif // COMMAND_JOIN_HPP