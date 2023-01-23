
#ifndef COMMAND_NOTICE_HPP
#define COMMAND_NOTICE_HPP

#include "ACommand.hpp"

class Notice : public ACommand
{
private:
	CanChannel *channel;

public:
	Notice();
	~Notice();
	void noticeOn(CanClient *client);
	std::map<CanChannel *, int> getChannel(CanClient *client);

	int noticeToChannel(void);

	int isValidFormat(void);
	int checkClientLevel(CanClient *client);
	int determineFlag(void);

	class noSuchNickException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class noSuchChannelException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class replyAnywayException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class kickedUserException : public std::exception
	{
		virtual const char *what() const throw();
	};
};

#endif // COMMAND_NOTICE_HPP
