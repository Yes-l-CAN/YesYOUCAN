#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <exception>
#include "CanClient.hpp"
#include "CanServer.hpp"

#define ERROR -1 
#define TRUE 1
#define FALSE 0

class ICommand
{
protected:
	CanServer	*server;

	int flag;
	int size;

	std::vector<std::string> cmd;

public:
	ICommand();
	ICommand(CanServer	*serv);
	~ICommand();
	virtual int isValidFormat(void) = 0;
	virtual int getClientLevel(CanClient *client) = 0;
	virtual int determineFlag(void) = 0;

	void setFlag(void);
	void setSize(void);

	const int getFlag(void) const;
	const int getSize(void) const;

	class invalidFormatException : public std::exception
	{
		virtual const char *what() const throw();
	};
};

#endif