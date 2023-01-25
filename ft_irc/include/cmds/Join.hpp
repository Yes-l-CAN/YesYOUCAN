#ifndef COMMAND_JOIN_HPP
#define COMMAND_JOIN_HPP

#include "ACommand.hpp"

#define ADD_LIMIT 1
#define MAX_MEMBER 10

class Join : public ACommand
{
private:
	Join(const Join &obj); // Deprecated.
	Join& operator=(const Join &obj); // Deprecated.
public:
	Join();
	Join(CanServer *serv);
	~Join();
	void joinOn(CanClient *client);

	int isKicked(CanClient *client);
	int isExistChannel(std::string channelName);
	void leaveAll(CanClient *client);
	void addClient(CanClient *client);
	void addChannel(std::string channelName);
	void sendMSG(CanClient *client);
	int isAlreadyJoined(CanClient *client);

	int isValidFormat(void);
	int checkClientLevel(CanClient *client);
	int determineFlag(void);

	CanChannel *getChannel(std::string &channelName);

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

	class kickedException : public std::exception
	{
		virtual const char *what() const throw();
	};
};

#endif // COMMAND_JOIN_HPP
