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
std::vector<std::string> Parsing::parseOn(std::string bufferStr)
{
    // NOTE: 파싱 다시?
    if (bufferStr.empty())
        return (std::vector<std::string>()); // nothing inside
    
    Parsing parse;
    parse.buff = bufferStr;
  //  makeBuffString(bufferStr);
    parse.giveFlag();

    for (size_t i = 0; i <= parse.buff.size(); i++)
    {
        i = parse.checkSpaceAndComma(i);

        // check colon
        if (parse.buff[i] == ':')
        {
            parse.checkColon(i);
            break;
        }
    }
 
    return (parse.v);
}

void Parsing::giveFlag()
{
    //NOTE: prefix 부분에서 나오는 콜론은 어떻게?
    if (buff.find(":") != std::string::npos)
        this->v.push_back("1");
    else
        this->v.push_back("0");
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