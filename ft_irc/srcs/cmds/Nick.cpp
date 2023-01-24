#include "Nick.hpp"

#include "Operation.hpp"

char Nick::invalid[8] = {' ', ',', '*', '?', '!', '@', '.', '#'};

Nick::Nick() {}

Nick::~Nick() {}

Nick::Nick(const Nick &obj)
{
	// Deprecated.
}

Nick &Nick::operator=(const Nick &obj)
{
	// Deprecated.
	return (*this);
}

int Nick::validCheck(void) {
  std::vector<std::string>::iterator it;

  it = this->cmd.begin() + 1;
  for (int i = 0; i < 8; i++) {
    if ((*it).find(invalid[i]) != std::string::npos) return (FALSE);
  }
  if ((*it)[0] == '$' || (*it)[0] == ':') return (FALSE);
  return (TRUE);
}

int Nick::checkUsedNick(void) {
  std::map<int, CanClient *>::iterator cit;
  std::vector<std::string>::iterator sit;

  sit = this->cmd.begin() + 1;
  for (cit = server->getClientList()->begin();
       cit != server->getClientList()->end(); cit++) {
    if (cit->second->getNickname() == *sit) return (FALSE);
  }
  return (TRUE);
}

int Nick::isValidFormat(void) {
  if (cmd.size() != 2) return (FALSE);
  return (TRUE);
}

void Nick::setClientNick(CanClient *client) {
  if (isValidFormat() != TRUE) throw(invalidFormatException());
  if (validCheck() != TRUE) throw(invalidNickException());
  if (checkUsedNick() != TRUE) throw(usedNickException());

  std::vector<std::string>::iterator it = this->cmd.begin() + 1;
  client->setNickname(*(it));
  client->setMemberLevel(NICK_FIN);
	if (client->getMemberLevel() & (PASS_FIN | NICK_FIN | USER_FIN) == (PASS_FIN | NICK_FIN | USER_FIN))
	{
		client->setMemberLevel(CERTIFICATION_FIN);
	}
}

int Nick::checkClientLevel(CanClient *client) {
  if (client->getMemberLevel() & PASS_FIN == 0) {
    return (FALSE);
  }
  return (TRUE);
}

int Nick::determineFlag(void) { return (0); }

const char *Nick::invalidNickException::what() const throw() {
  return ("Nick Error : invalid nick!");
}

const char *Nick::usedNickException::what() const throw() {
  return ("Nick Error : already used nick!");
}
