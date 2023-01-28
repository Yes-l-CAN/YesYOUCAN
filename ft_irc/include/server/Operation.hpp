#ifndef OPERATION_HPP
#define OPERATION_HPP

#include <csignal>

#include "CanChannel.hpp"
#include "CanClient.hpp"
#include "CanException.hpp"
#include "CanServer.hpp"
#include "Parsing.hpp"

#include "Bot.hpp"
#include "Join.hpp"
#include "Kick.hpp"
#include "Nick.hpp"
#include "Notice.hpp"
#include "Part.hpp"
#include "Pass.hpp"
#include "Ping.hpp"
#include "Prvmsg.hpp"
#include "Quit.hpp"
#include "User.hpp"

#define SUCCESS (1)
#define FAIL (0)
#define ERROR (-1)

#define CERTIFICATION_FIN (1 << 4) // 00000000 00000000 00000000 00010000
#define USER_FIN (1 << 3)          // 00000000 00000000 00000000 00001000
#define NICK_FIN (1 << 2)          // 00000000 00000000 00000000 00000100
#define PASS_FIN (1 << 1)          // 00000000 00000000 00000000 00000010
#define UNCERTIFICATION (1 << 0)   // 00000000 00000000 00000000 00000001

class Operation
{
  private:
    int        setFd;
    int        result;
    CanServer* server;
    Parsing    parser;

    // commands
    User*   cmdUser;
    Quit*   cmdQuit;
    Prvmsg* cmdPrvmsg;
    Ping*   cmdPing;
    Pass*   cmdPass;
    Part*   cmdPart;
    Notice* cmdNotice;
    Nick*   cmdNick;
    Kick*   cmdKick;
    Join*   cmdJoin;

    Operation(const Operation& obj);            // No use.
    Operation& operator=(const Operation& obj); // No use.

  public:
    Operation();
    Operation(char* s1, char* s2);
    ~Operation();

    // socket transmission
    void Transmission();

    // find sent Client
    CanClient* findClient(int fd);

    // check command after parsing
    void CommandChecker(std::vector<std::string> argv, CanClient* targetClient);

    void cRecv(int fd);

    int getCommandFromRecvBuffer(CanClient* client, std::string& sCmd);

    void serverClose(void);
};

#endif // OPERATION_HPP