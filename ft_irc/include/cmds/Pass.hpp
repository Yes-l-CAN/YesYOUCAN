#ifndef COMMAND_PASS_HPP
#define COMMAND_PASS_HPP

#include "ACommand.hpp"

class Pass : public ACommand
{
private:
public:
	Pass();
	~Pass();
	void passOn(void);
	void passCmp(void);

	int isValidFormat(void);
	int checkClientLevel(CanClient *client);
	int determineFlag(void);

	class incorrectPassException : public std::exception
	{
		virtual const char *what() const throw();
	};
};

#endif // COMMAND_PASS_HPP