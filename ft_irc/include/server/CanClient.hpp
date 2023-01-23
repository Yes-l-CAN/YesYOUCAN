#ifndef CAN_CLIENT_HPP
#define CAN_CLIENT_HPP

#include <map>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string>
#include <sys/socket.h>
#include <iostream>

class CanChannel;

class CanClient
{
private:
	int socketFd;
	std::string nickname;
	std::string username;
	std::string realname;
	struct sockaddr_in addr;
	int isMember;

	std::map<std::string, CanChannel *> channelList; // channelList which the client belongs

public:
	CanClient();
	CanClient(int fd);
	CanClient(const CanClient &ref);
	CanClient(const struct sockaddr_in addr);
	CanClient(const struct sockaddr_in addr, const int fd);
	CanClient &operator=(const CanClient &ref);
	~CanClient();

	// setter
	void setNickname(const std::string name);
	void setUsername(const std::string name);
	void setRealname(const std::string name);
	void setMemberLevel(int lev);

	// getter
	std::string getNickname(void) const;
	std::string getUsername(void) const;
	std::string getRealname(void) const;
	int getSockFd(void) const;
	int getMemberLevel(void) const;

	void addChannelElement(std::string key, CanChannel *pNewChannel); // join channel
	void deleteChannelElement(std::string key);						  // come outside channel

	void cSend(int fd);

	class addChannelException : public std::exception
	{
		virtual const char *what() const throw();
	};
};

// std::ostream    &operator<<(std::ostream &os, CanClient& client)
// {
//     os << "test!!" << std::endl;
//     return (os);
// }

#endif // CAN_CLIENT_HPP