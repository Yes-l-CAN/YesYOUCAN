#include "Quit.hpp"

#include "Operation.hpp"

int Quit::isValidFormat(void) {}

int Quit::checkClientLevel(CanClient *client) {
  if (client->getMemberLevel() & CERTIFICATION_FIN == 0) {
    return (FALSE);
  }
  return (TRUE);
}

int Quit::determineFlag(void) { return (1); }
