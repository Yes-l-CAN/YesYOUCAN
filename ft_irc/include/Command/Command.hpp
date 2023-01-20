#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <exception>
#include "CanClient.hpp"

class ICommand
{
private:
	int flag;
	int size;

	std::vector<std::string> cmd;

public:
	virtual int isValidFormat(void) = 0;
	virtual int getClientLevel(CanClient *client) = 0;
	virtual int determineFlag(void) = 0;

	int setFlag(int flag);
	int setSize(int size);

	const int getFlag(void) const;
	const int getSize(void) const;
};

#endif