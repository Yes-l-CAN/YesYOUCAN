#include "User.hpp"

#include "User.hpp"

int	User::validCheck(void)
{
	
}

void User::setClientUser(CanClient *client)
{

}

void User::noticeNameReplaced(void)
{

}

void User::welcome2CanServ(void)
{
	
}

const char *User::noNickExistException::what() const throw()
{
    return ("USER: Nick command needed");
}

const char *User::alreadyRegisteredException::what() const throw()
{
    return ("USER : You already registered");
}

const char *User::minUserLenException::what() const throw()
{
    return ("USER : ");
}

const char *User::spaceWithoutColonException::what() const throw()
{
    return ("USER : incorrect password");
}