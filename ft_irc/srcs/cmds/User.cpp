#include "User.hpp"
#include "Operation.hpp"

User::User()
{
}
User::User(CanServer* serv) : ACommand(serv)
{
}
User::~User()
{
}

void User::userOn(CanClient* client)
{
    try
    {
        isValidFormat();
        checkClientLevel(client);
        validCheck();
        setClientUser(client);
        if ((client->getMemberLevel() & CERTIFICATION_FIN) == CERTIFICATION_FIN)
            welcome2CanServ(client);
    }
    catch (int numeric)
    {
        std::stringstream sstm;
        sstm << numeric << " " << client->getSockFd();
        std::string msgBuf = sstm.str();
        switch (numeric)
        {
        case ERR_UNKNOWNERROR:
            msgBuf += " USER :Invalid Format error !";
            break;
        case ERR_NOTREGISTERED:
            msgBuf += " :You have not registered. Register PASS, USER, NICK !";
            break;

        case ERR_NEEDMOREPARAMS:
            msgBuf += " USER :Invalid Format error !";
            break;

        case ERR_ALREADYREGISTERED:
            msgBuf += " :You may not reregister";
            break;

        default:
            break;
        }

        msgBuf += "\r\n";
        client->addSendBuff(msgBuf);
    }
}

int User::validCheck(void)
{
    // flag USER <username> 0 * <realname>
    //  0   1     2         3 4  5

    if (cmd[2].length() < 1 || cmd[5].length() < 1)
    {
        throw(ERR_NEEDMOREPARAMS);
    }
    return (TRUE);
}

void User::setClientUser(CanClient* client)
{
    // flag USER <username> 0 * <realname>
    //  0   1     2         3 4  5

    client->setUsername(cmd[2]);
    client->setRealname(cmd[5]);
    client->setMemberLevel(USER_FIN);
    if ((client->getMemberLevel() & (PASS_FIN | NICK_FIN)) == (PASS_FIN | NICK_FIN))
        client->setMemberLevel(CERTIFICATION_FIN);
}

void User::welcome2CanServ(CanClient* client)
{
    // 001 <client> :<msg>
    std::string userName = cmd[2];
    std::string serverName = static_cast<std::string>(SERVERNAME);
    std::string msgBuf = "001 " + userName + " :Welcome, " + userName + "! Your host is " + serverName + "\r\n";
    client->addSendBuff(msgBuf);
}

int User::isValidFormat(void)
{
    // flag USER <username> 0 * <realname>
    if (getSize() != 5)
        throw ERR_UNKNOWNERROR;
    return (TRUE);
}

int User::checkClientLevel(CanClient* client)
{
    if ((client->getMemberLevel() & PASS_FIN) == 0)
    {
        throw ERR_NOTREGISTERED;
    }
    else if ((client->getMemberLevel() & USER_FIN) == USER_FIN)
    {
        throw(ERR_ALREADYREGISTERED);
    }
    return (TRUE);
}

int User::determineFlag(void)
{
    return (1);
}
