#ifndef COMMAND_HPP
#define	COMMAND_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <exception>

class Command{
	private:
		int	flag;
		int	size;

	public:
		virtual int isValidFormat(std::vector<std::string> cmd) = 0;
		virtual int	getClientLevel(Client *client) = 0;

		

		int	setFlag(int flag);
		int	setSize(int size);

		const int	getFlag(void) const;
		const int	getSize(void) const;
};

#endif