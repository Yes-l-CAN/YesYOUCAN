#include "CanException.hpp"

// exception
const char *CanException::socketCreateException::what() const throw()
{
    return ("Error! Can't create the socket.");
}

const char *CanException::bindException::what() const throw()
{
    return ("Bind error");
}

const char *CanException::listenException::what() const throw()
{
    return ("Listen error");
}

const char *CanException::selectException::what() const throw()
{
    return ("Select error");
}

const char *CanException::acceptException::what() const throw()
{
    return ("Accept error");
}

const char *CanException::invalidPortException::what() const throw()
{
    return ("Error! Port Num invalid.");
}

// operation

const char *CanException::recvSocketErrorException::what() const throw()
{
    return ("Error! Could not recv() client socket.");
}

const char *CanException::recvSocketClosedException::what() const throw()
{
    return ("Error! client socket is closed during recv().");
}

const char *CanException::pwIncorrectException::what() const throw()
{
    return ("Error! Password incorrect.");
}

const char *CanException::PasswordNotSameException::what() const throw()
{
    return ("Error! Password is different. Try another one!");
}

const char *CanException::existNickException::what() const throw()
{
    return ("Error! There is the same Nickname in this server. Try another one!");
}

const char* CanException::existUserException::what() const throw()
{
    return ("Error! Teere is the same Username in this server. Try another one!");
}
const char* CanException::NotCertificatedException::what() const throw()
{
    return ("Error! There is no certification! Please finish making a password, username and nickname.");
}
