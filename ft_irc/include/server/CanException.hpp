#ifndef CAN_EXCEPTION_HPP
#define CAN_EXCEPTION_HPP

#include <exception>

class CanException
{
public:
	// server Exception
	class socketCreateException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class bindException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class listenException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class selectException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class acceptException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class tooManyClientFDException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class invalidPortException : public std::exception
	{
		virtual const char *what() const throw();
	};

	// operation Exception

	class recvSocketErrorException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class recvSocketClosedException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class pwIncorrectException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class existNickException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class existUserException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class NotCertificatedException : public std::exception
	{
		virtual const char *what() const throw();
	};

	class PasswordNotSameException : public std::exception
	{
		virtual const char *what() const throw();
	};
};

#endif // CAN_EXCEPTION_HPP