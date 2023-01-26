#include "CanChannel.hpp"
#include "CanClient.hpp"
#include "CanServer.hpp"
#include "Operation.hpp"

int main(int argc, char *argv[])
{
	static_cast<void>(argv);
	if (argc != 3)
	{
		std::cout << "./ircserv [PORT] [PASSWORD]" << std::endl;
		return (1);
	}

	Operation operation(argv[1], argv[2]);
	while (1)
	{
		//signal(SIGINT,serverEnd());
		try
		{
			operation.Transmission();
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	return (0);
}