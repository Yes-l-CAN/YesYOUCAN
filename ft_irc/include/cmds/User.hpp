#ifndef COMMAND_USER_HPP
#define COMMAND_USER_HPP

#include "ACommand.hpp"

class User : public ACommand
{
private:
public:
	User();
	~User();
	void userOn();
	int validCheck(void);
	void setClientUser(CanClient *client);
	void noticeNameReplaced(void);
	void welcome2CanServ(void);

	int isValidFormat(void);
	int checkClientLevel(CanClient *client);
	int determineFlag(void);

	class noNickExistException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class alreadyRegisteredException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class minUserLenException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class spaceWithoutColonException : public std::exception
	{
		virtual const char *what() const throw();
	};
};

#endif // COMMAND_USER_HPP