#ifndef COMMAND_NICK_HPP
#define COMMAND_NICK_HPP

#include "Command.hpp"


class Nick : public ICommand
{
	private:
		char	invalid[8] = {' ', ',', '*', '?', '!', '@', '.', '#'};

	public:
		int validCheck(void);
		int checkUsedNick(void);
		void setClientNick(CanClient *client);
		
	//	int	isValidFormat(void);

		class invalidNickException : public std::exception
		{
			virtual const char* what() const throw();
		};

		class usedNickException: public std::exception
		{
			virtual const char* what() const throw();
		};
};

#endif // COMMAND_NICK_HPP