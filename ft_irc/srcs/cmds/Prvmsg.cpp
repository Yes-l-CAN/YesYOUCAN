#include "Prvmsg.hpp"

#include "Operation.hpp"

Prvmsg::Prvmsg() {}

Prvmsg::~Prvmsg() {}

Prvmsg::Prvmsg(const Prvmsg &obj)
{
	// Deprecated.
}

Prvmsg &Prvmsg::operator=(const Prvmsg &obj)
{
	// Deprecated.
	return (*this);
}

Prvmsg::Prvmsg() { this->bot = new Bot(); }

Prvmsg::~Prvmsg() { delete this->bot; }

int Prvmsg::isValidFormat(void) {}

int Prvmsg::checkClientLevel(CanClient *client) {
  if (client->getMemberLevel() & CERTIFICATION_FIN == 0) {
    return (FALSE);
  }
  return (TRUE);
}

int Prvmsg::determineFlag(void) { return (1); }
