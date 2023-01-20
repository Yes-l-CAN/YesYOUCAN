#include "Pass.hpp"

void	Pass::PassCmp(void)
{
	if(*(cmd.begin() + 1) != server->getPassWord())
		throw(incorrectPassException());
}

const char *Pass::incorrectPassException::what() const throw()
{
    return ("PASS : incorrect password");
}

