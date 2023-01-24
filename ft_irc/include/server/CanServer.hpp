#ifndef CAN_SERVER_HPP
#define CAN_SERVER_HPP

#include <arpa/inet.h>
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <string>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include <map>
#include <utility>

#include "CanClient.hpp"
#include "CanServer.hpp"
#include "CanException.hpp"

#define MAX_FD 1000
#define MAXBUF 10
#define SERVERNAME "CanServer"

class CanServer
{
private:
	int inputPortNum;
	std::string inputPassword;
	int port;
	std::string password;

	int socketFd;
	struct sockaddr_in addr;

	fd_set reads;
	fd_set copyReads;
	fd_set writes;
	fd_set copyWrites;

	int maxFd;

	std::map<int, CanClient *> *clientList;			 // current exist all clients list
	std::map<std::string, CanChannel *> channelList; // current exist all channel list

	CanException except;

public:
	CanServer();
	CanServer(const CanServer &obj);
	CanServer &operator=(const CanServer &obj);
	~CanServer();

	void s_On();

	// socket transmission
	int Transmission();

	void s_Socket();
	void s_Bind();
	void s_Listen();
	void s_Select();
	void s_Accept();

	// utils
	void findFd();
	void addChannelElement(const std::string channelName, CanChannel *pNewChannel); // add channel List
	void deleteChannelElement(const std::string channelName);						// delete channel List

	// setter
	void setServer(char *port, char *pw);
	void setServAddr();
	void setFdSet();
	void setInputPortNum(char *str);
	void setInputPassword(char *str);

	// getter
	int getInputPortNum() const;
	std::string getInputPasswordNum() const;
	int getPort() const;
	std::string getPassWord() const;
	int getSocketFd() const;
	struct sockaddr_in getAddr() const;
	fd_set *getReads();
	fd_set *getWrites();
	fd_set *getCopyReads();
	fd_set *getCopyWrites();
	std::map<int, CanClient *> *getClientList() const;
	std::map<std::string, CanChannel *> getChannelList() const;
};

#endif // CAN_SERVER_HPP