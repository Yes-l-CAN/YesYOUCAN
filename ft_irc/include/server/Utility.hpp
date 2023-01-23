#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <exception>
#include <string>
#include <vector>

class Utility
{
  private:
  public:
    std::vector<std::string> splitArr(char* str);
	std::vector<std::string> splitArrWithColon(char* s);
	
    class commandArgvException : public std::exception
    {
        virtual const char* what() const throw();
    };
};

#endif // UTILITY_HPP