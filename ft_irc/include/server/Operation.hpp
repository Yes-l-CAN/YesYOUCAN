#ifndef OPERATION_HPP
#define OPERATION_HPP

#include "CanChannel.hpp"
#include "CanClient.hpp"
#include "CanException.hpp"
#include "CanServer.hpp"
#include "Operation.hpp"
#include "Utility.hpp"

#define SUCCESS (1)
#define FAIL (0)
#define ERROR (-1)

class Operation
{
  private:
    int          setFd;
    int          result;
    CanServer*   server;
    Utility      util;
    CanException except;

  protected:
    static const int bufferSize = 300;
    char             buffer[bufferSize];

  public:
    enum
    {
        PASS_FIN = 1,
        NICK_FIN,
        USER_FIN,
        CERTIFICATION_FIN
    };

    Operation();
    Operation(char* s1, char* s2);
    Operation(const Operation& obj);
    Operation& operator=(const Operation& obj);
    ~Operation();

    // socket transmission
    void Transmission();

    // find sent Client
    CanClient* findClient(int fd);

    // check command after parsing
    void CommandChecker(std::vector<std::string> argv, CanClient* targetClient);

    void cRecv(int fd);
    void Client2ServSend(int fd);
    void Serv2ClientSend(int fd);

    void Pass(std::vector<std::string> argv, CanClient* targetClient);
    int  Nick(std::vector<std::string> argv, CanClient* targetClient);
    int  User(std::vector<std::string> argv, CanClient* targetClient);
    void Ping(std::vector<std::string> argv, CanClient* targetClient);
    void Quit(std::vector<std::string> argv, CanClient* targetClient);
    // void    Pong(std::vector<std::string> argv, CanClient* targetClient);
    void Join(std::vector<std::string> argv, CanClient* targetClient);
    void Part(std::vector<std::string> argv, CanClient* targetClient);
    void Kick(std::vector<std::string> argv, CanClient* targetClient);
    void Notice(std::vector<std::string> argv, CanClient* targetClient);
    void PrivateMSG(std::vector<std::string> argv, CanClient* targetClient);
};

#endif // OPERATION_HPP