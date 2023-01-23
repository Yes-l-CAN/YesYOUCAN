#ifndef COMMAND_NICK_HPP
#define COMMAND_NICK_HPP

#include "ACommand.hpp"

class Nick : public ACommand
{
private:
	static char invalid[8];

public:
	Nick();
	~Nick();
	bool validCheck(void);
	bool checkUsedNick(void);
	int isValidFormat(void);
	void setClientNick(CanClient *client);

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