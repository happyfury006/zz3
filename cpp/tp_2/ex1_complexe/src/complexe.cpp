#include "complexe.hpp"

std::ostream &operator<<(std::ostream &os, const Complexe &c) {
  c.afficher(os);
  return os;
}
