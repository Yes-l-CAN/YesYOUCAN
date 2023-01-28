#ifndef CAN_PARSING_HPP
#define CAN_PARSING_HPP

#include <cstddef>
#include <string>
#include <vector>

class Parsing
{
  private:
    std::vector<std::string>* v;
    std::string               buff;
    std::string               word;
    bool                      flag;

  public:
    Parsing();
    ~Parsing();

    std::vector<std::string> parseOn(std::string bufferStr);

    void parseClear(void);

    void giveFlag();
    int  checkSpaceAndComma(size_t idx);
    void makeBuffString(char* buffStr);
    void checkColon(size_t idx);
};

#endif // CAN_PARSING_HPP