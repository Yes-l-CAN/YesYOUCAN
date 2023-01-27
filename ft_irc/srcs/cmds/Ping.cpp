#include "Ping.hpp"

#include "Operation.hpp"

Ping::Ping() {}
Ping::Ping(CanServer *serv) : ACommand(serv) {}
Ping::~Ping() {}

void Ping::onCommand(CanClient *client)
{
	try
	{
		isValidFormat();
		pong(client);
	}
	catch (int numeric)
	{
		std::stringstream sstm;
		sstm << numeric << " ";
		if (checkClientLevel(client) == TRUE)
		{
			sstm << client->getNickname();
		}
		else
		{
			sstm << client->getSockFd();
		}
		std::string msgBuf = sstm.str();

		switch (numeric)
		{
		case ERR_UNKNOWNERROR:
			msgBuf += " PING :Invalid Format error !";
			break;
		case ERR_NEEDMOREPARAMS:
			msgBuf += " PING :No Token";
			break;
		case ERR_INPUTTOOLONG:
			msgBuf += " :Input line was too long";
			break;

		default:
			break;
		}

		msgBuf += "\r\n";
		client->addSendBuff(msgBuf);
	}
}

void Ping::pong(CanClient *client)
{
	// flag PING <token>

	// PONG <servername> <token>
	std::string msgBuf = "PONG " + static_cast<std::string>(SERVERNAME) + " " + cmd[2] + "\r\n";
	client->addSendBuff(msgBuf);
}

int Ping::isValidFormat(void)
{
	if (getSize() < 2)
	{
		throw ERR_NEEDMOREPARAMS;
	}
	else if (getSize() > 2)
	{
		throw ERR_UNKNOWNERROR;
	}

	if (cmd[2].length() - 2 > 512) // -2 = \r\n
	{
		throw ERR_INPUTTOOLONG;
	}
	return (TRUE);
}

int Ping::checkClientLevel(CanClient *client)
{
	if ((client->getMemberLevel() & CERTIFICATION_FIN) == 0)
	{
		return (FALSE);
	}
	return (TRUE);
}

int Ping::determineFlag(void) { return (1); }

// // ERR_NEEDMOREPARAMS (461)    "<client> <command> :Not enough parameters"
// const char *Ping::noTokenException::what() const throw() {
//   return ("Ping : No Token \r\n");
// }
// // ERR_INPUTTOOLONG (417)   "<client> :Input line was too long"
// const char *Ping::maxLenException::what() const throw() {
//   return ("Ping : Max Buffer Length => 512 \r\n");
// }
