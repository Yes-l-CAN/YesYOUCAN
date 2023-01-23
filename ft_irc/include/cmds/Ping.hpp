#ifndef COMMAND_PING_HPP
#define COMMAND_PING_HPP

#include "ACommand.hpp"


class Ping : public ACommand
{
	private:

	public:
		void	pong(CanClient *client);

		class noTokenException : public std::exception
		{
			virtual const char* what() const throw();
		};

		class maxLenException : public std::exception
		{
			virtual const char* what() const throw();
		};
};

#endif // COMMAND_PING_HPP