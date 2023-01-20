#ifndef COMMAND_USER_HPP
#define COMMAND_USER_HPP

#include "Command.hpp"

class User : public ICommand
{
	private:
		

	public:
		int		validCheck(void);
		void	setClientUser(void);
		void	noticeNameReplaced(void);
		void	welcom2CanServ(void);

		class noNickExistException : public std::exception
    	{
       		virtual const char* what() const throw();
		};

		class alreadyRegisteredException : public std::exception
		{
			virtual const char* what() const throw();
		};

		class minUserLenException: public std::exception
		{
			virtual const char* what() const throw();
		};

		class spaceWithoutColonException: public std::exception
		{
			virtual const char* what() const throw();
		};


};

#endif // COMMAND_USER_HPP