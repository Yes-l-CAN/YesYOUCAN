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
    const std::string& getChannelName(void);

    const std::map<int, CanClient*>& getClientList(void) const;
    void                             addClientElement(const int fd, CanClient* pNewClient);
    void                             deleteClientElement(const int fd);

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