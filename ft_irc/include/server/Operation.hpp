#ifndef OPERATION_HPP
#define OPERATION_HPP

#include <csignal>

#include "CanChannel.hpp"
#include "CanClient.hpp"
#include "CanException.hpp"
#include "CanServer.hpp"

#include "User.hpp"
#include "Quit.hpp"
#include "Prvmsg.hpp"
#include "Ping.hpp"
#include "Pass.hpp"
#include "Part.hpp"
#include "Notice.hpp"
#include "Nick.hpp"
#include "Nick.hpp"
#include "Kick.hpp"
#include "Join.hpp"
#include "Bot.hpp"

#define SUCCESS (1)
#define FAIL (0)
#define ERROR (-1)

#define CERTIFICATION_FIN (1 << 4)		// 00000000 00000000 00000000 00010000
#define USER_FIN (1 << 3)				// 00000000 00000000 00000000 00001000
#define NICK_FIN (1 << 2)				// 00000000 00000000 00000000 00000100
#define PASS_FIN (1 << 1)				// 00000000 00000000 00000000 00000010
#define UNCERTIFICATION (1 << 0)		// 00000000 00000000 00000000 00000001

class Operation
{
private:
	int setFd;
	int result;
	CanServer *server;

	// commands
	User cmdUser;
	Quit cmdQuit;
	Prvmsg cmdPrvmsg;
	Ping cmdPing;
	Pass cmdPass;
	Part cmdPart;
	Notice cmdNotice;
	Nick cmdNick;
	Kick cmdKick;
	Join cmdJoin;

	Operation(const Operation &obj); // Deprecated.
	Operation &operator=(const Operation &obj); // Deprecated.

protected:
	static const int bufferSize = 512;
	char buffer[bufferSize];
	int offset;

public:
	// enum
	// {
	// 	PASS_FIN = 1,
	// 	NICK_FIN,
	// 	USER_FIN,
	// 	CERTIFICATION_FIN
	// };

	Operation();
	Operation(char *s1, char *s2);
	~Operation();

	// socket transmission
	void Transmission();

	// find sent Client
	CanClient *findClient(int fd);

	// check command after parsing
	void CommandChecker(std::vector<std::string> argv, CanClient *targetClient);

	void cRecv(int fd);
	void Client2ServSend(int fd);
	void Serv2ClientSend(int fd);

	int getCommandFromRecvBuffer(char *cOriginBuf, std::string &sCmd);

	void serverClose(void);
};

#endif // OPERATION_HPP