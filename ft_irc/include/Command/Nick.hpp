#ifndef COMMAND_NICK_HPP
#define COMMAND_NICK_HPP

#include "Command.hpp"

class NICK : public ICommand
{
	private:
		char	invalid[8];

	public:
		
		void validCheck(void);
		void setClientNick(void);

		class containIvalidChar : public std::exception
    	{
       		virtual const char* what() const throw();
		};

		class invalidNick : public std::exception
		{
			virtual const char* what() const throw();
		};

		class usedNick: public std::exception
		{
			virtual const char* what() const throw();
		};
};

#endif // COMMAND_NICK_HPP