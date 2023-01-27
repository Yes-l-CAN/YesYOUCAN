#ifndef CAN_PARSING_HPP
#define CAN_PARSING_HPP

#include <cstddef>
#include <string>
#include <vector>

class Parsing
{
public:
    static std::vector<std::string> parseOn(std::string bufferStr);

  private:
    std::vector<std::string> v;
    std::string              buff;
    std::string              word;
    bool                     flag;

  public:
    Parsing();
    ~Parsing();

    void parseClear(void);

    void giveFlag();
    int  checkSpaceAndComma(size_t idx);
    void makeBuffString(char* buffStr);
    void checkColon(size_t idx);
};

#endif // CAN_PARSING_HPP