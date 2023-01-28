#ifndef CAN_EXCEPTION_HPP
#define CAN_EXCEPTION_HPP

#include <exception>

#define ERR_UNKNOWNERROR 400
#define ERR_NOSUCHNICK 401
#define ERR_NOSUCHCHANNEL 403
#define ERR_INPUTTOOLONG 417
#define ERR_ERRONEUSNICKNAME 432
#define ERR_NICKNAMEINUSE 433
#define ERR_NOTONCHANNEL 442
#define ERR_USERONCHANNEL 443
#define ERR_NOTREGISTERED 451
#define ERR_NEEDMOREPARAMS 461
#define ERR_ALREADYREGISTERED 462
#define ERR_PASSWDMISMATCH 464
#define ERR_CHANNELISFULL 471
#define ERR_BANNEDFROMCHAN 474
#define ERR_NOPRIVILEGES 481

class CanException
{
  public:
    // server Exception
    class socketCreateException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class bindException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class listenException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class selectException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class acceptException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class tooManyClientFDException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class invalidPortException : public std::exception
    {
        virtual const char* what() const throw();
    };

    // operation Exception
    class recvSocketErrorException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class recvSocketClosedException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class pwIncorrectException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class existNickException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class existUserException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class NotCertificatedException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class PasswordNotSameException : public std::exception
    {
        virtual const char* what() const throw();
    };
};

#endif // CAN_EXCEPTION_HPP