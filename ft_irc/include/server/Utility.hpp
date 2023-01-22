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

    class commandArgvException : public std::exception
    {
        virtual const char* what() const throw();
    };
};

#endif // UTILITY_HPP