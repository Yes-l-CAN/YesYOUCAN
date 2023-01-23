#ifndef COMMAND_NICK_HPP
#define COMMAND_NICK_HPP

#include "ACommand.hpp"

#define TRUE 1
#define FALSE 0

class Nick : public ACommand
{
private:
	int flag;
	static char invalid[8];

public:
Nick();
~Nick();
	void nickOn();
	int validCheck(void);
	int checkUsedNick(void);
	int isValidFormat(void);
	void setClientNick(CanClient *client);

	int checkClientLevel(CanClient *client);
	int determineFlag(void);

	//	int	isValidFormat(void);

	class invalidNickException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class usedNickException : public std::exception
	{
		virtual const char *what() const throw();
	};
};

#endif // COMMAND_NICK_HPP