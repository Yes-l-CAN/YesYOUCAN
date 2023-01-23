#include "Nick.hpp"

char Nick::invalid[8] = {' ', ',', '*', '?', '!', '@', '.', '#'};

Nick::Nick()
{
}

Nick::~Nick()
{
}

bool Nick::validCheck(void)
{
	std::vector<std::string>::iterator it;

	it = this->cmd.begin() + 1;
	for (int i = 0; i < 8; i++)
	{
		if ((*it).find(invalid[i]) != std::string::npos)
			return (FALSE);
	}
	if ((*it)[0] == '$' || (*it)[0] == ':')
		return (FALSE);
	return (TRUE);
}

bool Nick::checkUsedNick(void)
{
	std::map<int, CanClient *>::iterator cit;
	std::vector<std::string>::iterator sit;

	sit = this->cmd.begin() + 1;
	for (cit = server->getClientList()->begin(); cit != server->getClientList()->end(); cit++)
	{
		if (cit->second->getNickname() == *sit)
			return (FALSE);
	}
	return (TRUE);
}

int Nick::isValidFormat(void)
{
	if (cmd.size() != 2)
		return (0); // FALSE
	return (1);
}

void Nick::setClientNick(CanClient *client)
{
	if (isValidFormat() != TRUE)
		throw(invalidFormatException());
	if (validCheck() != TRUE)
		throw(invalidNickException());
	if (checkUsedNick() != TRUE)
		throw(usedNickException());

	std::vector<std::string>::iterator it = this->cmd.begin() + 1;
	client->setNickname(*(it));
	client->setMemberLevel(NICK_FIN);
}

const char* Nick::invalidNickException::what(void) const throw()
{
	return ("Nick Error! : invalid Nick exception.");
};

const char* Nick::usedNickException::what(void) const throw()
{
	return ("Nick Error! : used Nick exception.");
};