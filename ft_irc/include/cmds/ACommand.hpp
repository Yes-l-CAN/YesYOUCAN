#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <exception>
#include "CanClient.hpp"
#include "CanServer.hpp"
#include "CanChannel.hpp"

#define MAXBUFLEN 512

class ACommand
{
protected:
	CanServer *server;

	int flag;
	int size;

	std::vector<std::string> cmd;
	ACommand(const ACommand &obj);			  // Deprecated.
	ACommand &operator=(const ACommand &obj); // Deprecated.

public:
	ACommand();
	ACommand(CanServer *serv);
	virtual ~ACommand();
	virtual int isValidFormat(void) = 0;
	virtual int checkClientLevel(CanClient *client) = 0;
	virtual int determineFlag(void) = 0;

	void setFlag(void);
	void setSize(void);

	int getFlag(void) const;
	int getSize(void) const;

	class invalidFormatException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class noAuthorityException : public std::exception
	{
		virtual const char *what() const throw();
	};
};

#endif