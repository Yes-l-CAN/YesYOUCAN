#include "Ping.hpp"

#include "Operation.hpp"

Ping::Ping() {}

Ping::~Ping() {}

void Ping::pingOn(CanClient *client) {}

void Ping::pong(CanClient *client) {
  if (this->cmd.size() < 3) throw(noTokenException());
  std::vector<std::string>::iterator it;
  it = cmd.begin() + 3;
  std::string buf = "PONG: " + (*it);
  /*
          std::string에서 char * 로의 현변환이 자꾸 안 도ㅑ요...이제 그만
     받고싶은데....
  */

  send(client->getSockFd(), buf.c_str(), buf.length(), 0);
}

int Ping::isValidFormat(void) {}

int Ping::checkClientLevel(CanClient *client) {
  if (client->getMemberLevel() & CERTIFICATION_FIN == 0) {
    return (FALSE);
  }
  return (TRUE);
}

int Ping::determineFlag(void) { return (1); }

const char *Ping::noTokenException::what() const throw() {
  return ("Ping : No Token");
}

const char *Ping::maxLenException::what() const throw() {
  return ("Ping : Max Buffer Length => 512");
}
