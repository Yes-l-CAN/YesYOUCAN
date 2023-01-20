#ifndef COMMAND_PASS_HPP
#define COMMAND_PASS_HPP

#include "Command.hpp"

class Pass : public ICommand
{
	private:

	public:
		
		void PassCmp(void);

		class incorrectPassException : public std::exception
    	{
       		virtual const char* what() const throw();
		};
};

#endif // COMMAND_PASS_HPP