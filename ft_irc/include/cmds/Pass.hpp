#ifndef COMMAND_PASS_HPP
#define COMMAND_PASS_HPP

#include "ACommand.hpp"
#define throw(...)

class Pass : public ACommand
{
private:
	Pass(const Pass &obj);			  // Deprecated.
	Pass &operator=(const Pass &obj); // Deprecated.

public:
	Pass();
	Pass(CanServer *serv);
	~Pass();
	void passOn(CanClient *client);
	void passCmp(CanClient *client) throw(int);

	int isValidFormat(void);
	int checkClientLevel(CanClient *client) throw(int);
	int determineFlag(void);

	// class incorrectPassException : public std::exception
	// {
	// 	virtual const char *what() const throw();
	// };

	// class alreadyRegisteredException : public std::exception
	// {
	// 	virtual const char *what() const throw();
	// };
};

#endif // COMMAND_PASS_HPP
