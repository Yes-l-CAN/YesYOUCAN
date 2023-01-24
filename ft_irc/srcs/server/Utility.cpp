#include "Utility.hpp"
#include <iostream>

// std::vector<std::string> Utility::splitArr(char* s)
// {
//     std::vector<std::string> v;
//     std::string              str = static_cast<std::string>(s);
//     std::string              temp = "";
//     size_t                   position = 0;
//     size_t                   start = 0;

//     if (str.find(" ") == std::string::npos)
//     {
//         throw(commandArgvException());
//     }

//     while ((position = str.find(" ", position)) != std::string::npos)
//     {
//         // std::cout << "start : " << start << std::endl;
//         // std::cout << "pos : " << position << std::endl;
//         std::string temp = "";
//         for (size_t i = start; i < position; i++)
//         {
//             temp += str[i];
//         }
//         v.push_back(temp);
//         position += 1;
//         start = position;
//     }
//     if (position == std::string::npos)
//         position = str.length();
//     std::string last = "";
//     for (size_t i = start; i < position - 1; i++)
//     {
//         last += str[i];
//     }
//     v.push_back(last);

//     return (v);
// }

std::vector<std::string> Utility::splitArrWithColon(char* s)
{
    std::vector<std::string> v;
    std::string              str = static_cast<std::string>(s);
    size_t                   s_position = 0;
    size_t                   c_position = 0;
    size_t                   start = 0;

    if (str.find(" ") == std::string::npos)
    {
        throw(commandArgvException());
    }

    std::string tmp = "";
    if ((c_position = str.find(":", c_position)) != std::string::npos)
    {
        for (size_t i = start; i < c_position; i++)
        {
            tmp += str[i];
        }
        v.push_back(tmp);
        c_position += 1;
        start = c_position;
        c_position = str.length();
        std::string last = "";
        for (size_t i = start; i < c_position - 1; i++)
        {
            last += str[i];
        }
        v.push_back(last);

        return (v);
    }
    else
    {
        while ((s_position = str.find(" ", s_position)) != std::string::npos)
        {
            // std::cout << "start : " << start << std::endl;
            // std::cout << "pos : " << position << std::endl;
            std::string temp = "";
            for (size_t i = start; i < s_position; i++)
            {
                temp += str[i];
            }
            v.push_back(temp);
            s_position += 1;
            start = s_position;
        }
        if (s_position == std::string::npos)
            s_position = str.length();
        std::string last = "";
        for (size_t i = start; i < s_position - 1; i++)
        {
            last += str[i];
        }
        v.push_back(last);

        return (v);
    }
}

const char* Utility::commandArgvException::what() const throw()
{
    return ("Command Acception error during spliting.");
}