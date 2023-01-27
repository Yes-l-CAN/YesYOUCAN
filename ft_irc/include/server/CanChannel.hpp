#ifndef CAN_CHANNEL_HPP
#define CAN_CHANNEL_HPP

#include "CanClient.hpp"
#include <exception>
#include <iostream>
#include <map>
#include <vector>

class CanChannel
{
  private:
    std::string               channelName;
    std::map<int, CanClient*> clientList;

    std::map<int, CanClient*> kickedList;

  public:
    CanChannel();
    ~CanChannel();
    CanChannel(const CanChannel& ref);
    CanChannel& operator=(const CanChannel& ref);

    CanChannel(const std::string channelName);
    const std::string& getChannelName(void) const;
    void setChannelName(const std::string name);

    std::map<int, CanClient*>& getClientList(void);
    void                             addClientElement(const int fd, CanClient* pNewClient);
    void                             deleteClientElement(const int fd);

    const std::map<int, CanClient*>& getKickedList(void) const;
    void addKickedListElement(CanClient* client);
    void delKickedListElement(CanClient* client);

    void broadcast(const std::string& msg, CanClient *client);
    void broadcastWithMe(const std::string& msg, CanClient *client);

    class addClientException : public std::exception
    {
        virtual const char* what() const throw();
    };

    // class deleteClientException: public std::exception
    // {
    //     virtual const char*	what() const throw();
    // }
};

#endif // CAN_CHANNEL_HPP
