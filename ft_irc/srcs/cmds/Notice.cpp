#include "Notice.hpp"

#include "Operation.hpp"

Notice::Notice() {}

Notice::~Notice() {}

void Notice::noticeOn(CanClient *client) 
{
  try
  {
    '/* code */'
  }
  catch(const std::exception& e)
  {
    throw e;
  }
  
}

std::map<CanChannel *, int> Notice::getChannel(CanClient *client) {}

int Notice::noticeToChannel(void) {}

int Notice::isValidFormat(void) {}

int Notice::checkClientLevel(CanClient *client) {
  if (client->getMemberLevel() & CERTIFICATION_FIN == 0) {
    return (FALSE);
  }
  return (TRUE);
}

int Notice::determineFlag(void) { return (1); }

const char *Notice::noSuchNickException::what() const throw() {
  return ("Notice Error! : Threre's no such nick!");
}

const char *Notice::noSuchChannelException::what() const throw() {
  return ("Notice Error! : Threre's no such channel!");
}

const char *Notice::replyAnywayException::what() const throw() {
  return ("Notice Error! : replied anyway!");
}

const char *Notice::kickedUserException::what() const throw() {
  return ("Notice Error! : Already kicked user!");
}
