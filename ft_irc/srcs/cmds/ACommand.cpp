#include "ACommand.hpp"

ACommand::ACommand() : flag(-1), size(-1)
{
};

ACommand::ACommand(CanServer *serv) : flag(-1), size(-1)
{
	this->server = serv;
};


ACommand::~ACommand()
{};

void	ACommand::setFlag(void)
{
	if(*(cmd.begin()) == "0")
		this->flag = 0;
	else if(*(cmd.begin()) == "1")
		this->flag = 1;
}

void	ACommand::setSize(void)
{
	this->size = cmd.size() - 1;
}

const int ACommand::getFlag(void) const
{
	return (this->flag);
}

const int ACommand::getSize(void) const 
{
	return (this->size);
}