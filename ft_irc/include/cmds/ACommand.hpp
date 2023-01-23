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

#define ERROR -1 
#define TRUE 1
#define FALSE 0

#define MAXBUFLEN 512 

// #deifine PASS_FIN (1 << 3) // 00000000 00000000 00000000 00000100
// #deifine NAME_FIN (1 << 2) // 00000000 00000000 00000000 00000010
#define NICK_FIN (1 << 1) // // 00000000 00000000 00000000 00000001

class ACommand
{
protected:
	CanServer	*server;

	int flag;
	int size;

	std::vector<std::string> cmd;

public:
	ACommand();
	ACommand(CanServer	*serv);
	virtual ~ACommand();
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