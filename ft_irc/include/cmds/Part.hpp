#ifndef COMMAND_PART_HPP
#define COMMAND_PART_HPP

#include "ACommand.hpp"

class Part : public ACommand
{
private:
	Part(const Part &obj); // Deprecated.
	Part& operator=(const Part &obj); // Deprecated.

public:
	Part();
	Part(CanServer *serv);
	~Part();
	void partOn(CanClient *client);
	// std::map<CanChannel *, int> getChannel(CanClient *client);

	int isLastMember(void);
	void eraseChannel(CanClient *client);
	void channelClose(void);
	void operatorChanged(CanClient *client);

	int isValidFormat(void);
	int checkClientLevel(CanClient *client);
	int determineFlag(void);

	class noSuchChannelException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class notOnChannelException : public std::exception
	{
		virtual const char *what() const throw();
	};
};

#endif // COMMAND_PART_HPP
