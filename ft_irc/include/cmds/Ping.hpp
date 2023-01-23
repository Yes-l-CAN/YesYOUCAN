#ifndef COMMAND_PING_HPP
#define COMMAND_PING_HPP

#include "ACommand.hpp"

class Ping : public ACommand
{
private:
public:
	Ping();
	~Ping();
	void pingOn(CanClient *client);
	void pong(CanClient *client);

	int isValidFormat(void);
	int checkClientLevel(CanClient *client);
	int determineFlag(void);

	class noTokenException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class maxLenException : public std::exception
	{
		virtual const char *what() const throw();
	};
};

#endif // COMMAND_PING_HPP
