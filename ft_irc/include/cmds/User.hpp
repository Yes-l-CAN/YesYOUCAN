#ifndef COMMAND_USER_HPP
#define COMMAND_USER_HPP

#include "ACommand.hpp"

#define USERNAME_MAXLEN 30;

class User : public ACommand
{
private:
	
	User(const User &obj); // Deprecated.
	User& operator=(const User &obj); // Deprecated.
	
public:
	User();
	~User();
	void userOn(CanClient *client);
	int validCheck(void);
	void setClientUser(CanClient *client);
	void welcome2CanServ(CanClient *client);

	int isValidFormat(void);
	int checkClientLevel(CanClient *client);
	int determineFlag(void);

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
