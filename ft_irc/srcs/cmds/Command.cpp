#include "Command.hpp"

ICommand::ICommand() : flag(-1), size(-1)
{
};

ICommand::ICommand(CanServer *serv) : flag(-1), size(-1)
{
	this->server = serv;
};


ICommand::~ICommand()
{};

void	ICommand::setFlag(void)
{
	if(*(cmd.begin()) == "0")
		this->flag = 0;
	else if(*(cmd.begin()) == "1")
		this->flag = 1;
}

void	ICommand::setSize(void)
{
	this->size = cmd.size() - 1;
}

const int ICommand::getFlag(void) const
{
	return (this->flag);
}

const int ICommand::getSize(void) const 
{
	return (this->size);
}