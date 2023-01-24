#include "Quit.hpp"

#include "Operation.hpp"

Quit::Quit() {}

Quit::~Quit() {}

Quit::Quit(const Quit &obj)
{
	// Deprecated.
}

Quit &Quit::operator=(const Quit &obj)
{
	// Deprecated.
	return (*this);
}

int Quit::isValidFormat(void) {}

int Quit::checkClientLevel(CanClient *client) {
  if (client->getMemberLevel() & CERTIFICATION_FIN == 0) {
    return (FALSE);
  }
  return (TRUE);
}

int Quit::determineFlag(void) { return (1); }
