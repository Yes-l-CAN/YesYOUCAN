#include "CanException.hpp"

// exception
const char *CanException::socketCreateException::what() const throw()
{
    return ("Error! Can't create the socket. \r\n");
}

const char *CanException::bindException::what() const throw()
{
    return ("Bind error \r\n");
}

const char *CanException::listenException::what() const throw()
{
    return ("Listen error \r\n");
}

const char *CanException::selectException::what() const throw()
{
    return ("Select error \r\n");
}

const char *CanException::acceptException::what() const throw()
{
    return ("Accept error \r\n");
}

const char *CanException::tooManyClientFDException::what() const throw()
{
    return ("There are too many client exception \r\n");
}

const char *CanException::invalidPortException::what() const throw()
{
    return ("Error! Port Num invalid. \r\n");
}

// operation

const char *CanException::recvSocketErrorException::what() const throw()
{
    return ("Error! Could not recv() client socket. \r\n");
}

const char *CanException::recvSocketClosedException::what() const throw()
{
    return ("Error! client socket is closed during recv(). \r\n");
}

const char *CanException::pwIncorrectException::what() const throw()
{
    return ("Error! Password incorrect. \r\n");
}

const char *CanException::PasswordNotSameException::what() const throw()
{
    return ("Error! Password is different. Try another one! \r\n");
}

const char *CanException::existNickException::what() const throw()
{
    return ("Error! There is the same Nickname in this server. Try another one! \r\n");
}

const char* CanException::existUserException::what() const throw()
{
    return ("Error! Teere is the same Username in this server. Try another one! \r\n");
}
const char* CanException::NotCertificatedException::what() const throw()
{
    return ("Error! There is no certification! Please finish making a password, username and nickname. \r\n");
}
