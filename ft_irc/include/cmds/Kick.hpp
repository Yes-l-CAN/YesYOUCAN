
#ifndef COMMAND_KICK_HPP
#define COMMAND_KICK_HPP

#include "ACommand.hpp"

#define MAX_KICK_NUM 1


class Kick : public ACommand
{
	private:
		CanChannel *channel;
		
	public:
		std::map<CanChannel *, int>	getChannel(CanClient *client); 

		int		isOperator(CanClient *client);
		void 	changeChannelStatus(CanClient *client);
		void	snedMSG(CanClient *client);

		class notOperatorException : public std::exception
		{
			virtual const char* what() const throw();
		};

		class noSuchUSerException: public std::exception
		{
			virtual const char* what() const throw();
		};
		
		class noSuchChannelException: public std::exception
		{
			virtual const char* what() const throw();
		};

		
};

#endif // COMMAND_KICK_HPP