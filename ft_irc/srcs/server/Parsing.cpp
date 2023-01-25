#include "Parsing.hpp"
#include <iostream>

Parsing::Parsing() : v(), buff(), word(), flag(false)
{
}

Parsing::~Parsing()
{
}

void Parsing::parseClear(void)
{
    delete v;
    buff.clear();
    word.clear();
    flag = false;
}

// main function
std::vector<std::string> Parsing::parseOn(char* bufferStr)
{
    v = new std::vector<std::string>;
    if (!bufferStr)
        return (*v); // nothing inside

    makeBuffString(bufferStr);
    giveFlag();

    for (size_t i = 0; i <= buff.size(); i++)
    {
        i = checkSpaceAndComma(i);

        // check colon
        if (buff[i] == ':')
        {
            checkColon(i);
            break;
        }
    }
    //  && ((*(*(v->begin() + 1)).end() - 1) == '\n')
    if((v->size() == 2))
    {
        std::string::iterator it = (*(v->begin() + 1)).end() - 1;
        std::cout << "string iterator :: " << *it << std::endl;
       (v->begin() + 1)->erase(it); 
    }
    std::vector<std::string>::iterator it;
    for (it = v->begin(); it != v->end(); ++it)
    {
        std::cout << "parse :: " << *it << std::endl;
    }
    return (*v);
}

void Parsing::giveFlag()
{
    if (buff.find(":") != std::string::npos)
        (*v).push_back("1");
    else
        (*v).push_back("0");
}

int Parsing::checkSpaceAndComma(size_t i)
{
    while (buff[i] == ' ' || buff[i] == ',')
    {
        flag = true;
        i++;
    }
    if ((!word.empty() && flag) || i == buff.size())
    {
        (*v).push_back(word);
        word.clear();
        word += buff[i];
        flag = false;
    }
    else if (word.empty() || !flag)
    {
        word += buff[i];
        flag = false;
    }
    return (i);
}

void Parsing::checkColon(size_t i)
{

    if (!word.empty())
    {
        if (!word.empty() && (word.find(":") != std::string::npos))
        {
            word.erase(word.find(":"));
        }
        if (!word.empty())
        {
            (*v).push_back(word);
            word.clear();
        }
    }
    while (i < buff.size())
    {
        word += buff[++i];
    }
    (*v).push_back(word);
}

void Parsing::makeBuffString(char* buffStr)
{
    int i = 0;
    while (buffStr[i])
        buff += buffStr[i++];
}