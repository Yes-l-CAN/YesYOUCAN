#ifndef CAN_CLIENT_HPP
#define CAN_CLIENT_HPP

#include <iostream>
#include <map>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string>
#include <sys/socket.h>

class CanChannel;

class CanClient
{
  private:
    int                socketFd;
    std::string        nickname;
    std::string        username;
    std::string        realname;
    struct sockaddr_in addr;
    int                isMember;

    std::string sendBuff;
    std::string recvBuff;

    static const int bufferSize = 512;
    char             buffer[bufferSize];

    std::map<std::string, CanChannel*> channelList;
	CanClient(const CanClient& ref);
	CanClient& operator=(const CanClient& ref);

  public:
    CanClient();
    CanClient(int fd);
    CanClient(const struct sockaddr_in addr);
    CanClient(const struct sockaddr_in addr, const int fd);
    ~CanClient();

    // setter
    void setNickname(const std::string name);
    void setUsername(const std::string name);
    void setRealname(const std::string name);
    void setMemberLevel(int lev);
    void setSendBuff(const std::string& msg);
    void setRecvBuff(const std::string& msg);

    // getter
    std::string                         getNickname(void) const;
    std::string                         getUsername(void) const;
    std::string                         getRealname(void) const;
    int                                 getSockFd(void) const;
    int                                 getMemberLevel(void) const;
    int                                 getisMember(void) const;
    std::map<std::string, CanChannel*>& getChannelList(void);
    std::string&                        getsendBuff(void);
    std::string&                        getRecvBuff(void);
    char*                               getBuffer(void);

    void addChannelElement(const std::string& key, CanChannel* pNewChannel);
    void deleteChannelElement(std::string key);

    void sendToClient();
    int  recvClient(void);

    void addSendBuff(std::string message);
    void addRecvBuff(std::string& message);

    class addChannelException : public std::exception
    {
        virtual const char* what() const throw();
    };

    class sendToClientException : public std::exception
    {
        virtual const char* what() const throw();
    };
};

#endif // CAN_CLIENT_HPP
