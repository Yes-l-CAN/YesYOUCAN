#include "Operation.hpp"
#include "CanServer.hpp"
#include "CanClient.hpp"
#include "CanChannel.hpp"

int loopFlag = TRUE;

void sigintHandler(int signum) 
{
    if (signum != SIGINT)
    {
        return ;
    }
    loopFlag = FALSE;
}

int main(int argc, char *argv[])
{
	static_cast<void>(argv);
	if (argc != 3)
	{
		std::cout << "./ircserv [PORT] [PASSWORD]" << std::endl;
		return (1);
	}

	signal(SIGINT, sigintHandler);
	Operation operation(argv[1], argv[2]);
	while (loopFlag)
	{
		try
		{
			operation.Transmission();
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	if (loopFlag == FALSE)
    {
        operation.serverClose();
	}

	return (0);
}