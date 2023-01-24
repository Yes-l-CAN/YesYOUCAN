#include "Ping.hpp"

#include "Operation.hpp"

Ping::Ping() {}

Ping::~Ping() {}

// Ping::Ping(const Ping &obj)
// {
// 	// Deprecated.
// }

// Ping &Ping::operator=(const Ping &obj)
// {
// 	// Deprecated.
// 	return (*this);
// }

void Ping::pingOn(CanClient *client)
{
  try
  {
    isValidFormat();
    pong(client);
  }
  catch(const std::exception& e)
  {
    std::string msgBuf = e.what() ;
    client->addSendBuff(msgBuf);
  }
  
}

void Ping::pong(CanClient *client) {
  // flag PING <token>

  // PONG <servername> <token>
  std::string msgBuf = "PONG " + static_cast<std::string>(SERVERNAME) + " " + cmd[2];
  client->addSendBuff(msgBuf);
}

int Ping::isValidFormat(void)
{
  if (getSize() < 2) 
  {
    throw noTokenException();
  }
  else if (getSize() > 2)
  {
    throw invalidFormatException();
  }
  return (TRUE);
}

int Ping::checkClientLevel(CanClient *client) {
  if ((client->getMemberLevel() & CERTIFICATION_FIN) == 0) {
    return (FALSE);
  }
  return (TRUE);
}

int Ping::determineFlag(void) { return (1); }

const char *Ping::noTokenException::what() const throw() {
  return ("Ping : No Token \n");
}

const char *Ping::maxLenException::what() const throw() {
  return ("Ping : Max Buffer Length => 512 \n");
}
