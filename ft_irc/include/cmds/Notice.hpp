
#ifndef COMMAND_NOTICE_HPP
#define COMMAND_NOTICE_HPP

#include "ACommand.hpp"

class Notice : public ACommand
{
protected:
	Notice(const Notice &obj); // Deprecated.
	Notice& operator=(const Notice &obj); // Deprecated.

public:
	Notice();
	Notice(CanServer *serv);
	~Notice();
	void onCommand(CanClient *client);

	void noticeToChannel(void);
	CanChannel *isExistChannelName(std::string name);
	CanClient *isExistNickname(std::string name);
	int isKicked(CanClient *clinet, CanChannel *channel);

	void executeNotice(CanClient *client);

	int isValidFormat(void);
	int checkClientLevel(CanClient *client);
	int determineFlag(void);

	// class noSuchNickException : public std::exception
	// {
	// 	virtual const char *what() const throw();
	// };

	// class noSuchChannelException : public std::exception
	// {
	// 	virtual const char *what() const throw();
	// };

	// // class replyAnywayException : public std::exception
	// // {
	// // 	virtual const char *what() const throw();
	// // };

	// class kickedUserException : public std::exception
	// {
	// 	virtual const char *what() const throw();
	// };
};

#endif // COMMAND_NOTICE_HPP
