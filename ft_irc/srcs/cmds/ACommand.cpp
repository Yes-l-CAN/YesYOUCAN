#include "ACommand.hpp"

ACommand::ACommand() : flag(-1), size(-1){};

ACommand::ACommand(CanServer *serv) : flag(-1), size(-1)
{
	this->server = serv;
};


ACommand::~ACommand(){};

void ACommand::setFlag(void)
{
	if (*(cmd.begin()) == "0")
		this->flag = 0;
	else if (*(cmd.begin()) == "1")
		this->flag = 1;
}

void ACommand::setSize(void)
{
	this->size = cmd.size() - 1;
}

void ACommand::setCmd(std::vector<std::string> cmd)
{
	std::vector<std::string>::iterator it;
	for(it = cmd.begin(); it != cmd.end(); it++)
		std::cout << "it : " << *it << std::endl;
	this->cmd = cmd;
	setFlag();
    setSize();
}

int ACommand::getFlag(void) const
{
	return (this->flag);
}

int ACommand::getSize(void) const
{
	return (this->size);
}

//   		 예시:	  400 dan!~d@n PACK BOX :Could not find box to pack
// ERR_UNKNOWNERROR (400)    "<client> <command>{ <subcommand>} :<info>"
// const char *ACommand::invalidFormatException::what() const throw()
// {
// 	return "Invalid Format error ! \r\n";
// }

// ERR_NOTREGISTERED (451)   "<client> :You have not registered"
// const char *ACommand::noAuthorityException::what() const throw()
// {
// 	return ("No Authority : Register PASS, USER, NICK \r\n");
// }