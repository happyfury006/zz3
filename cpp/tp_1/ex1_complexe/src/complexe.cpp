#include "complexe.hpp"

Complexe::Complexe() {}
Complexe::~Complexe() {}

std::ostream &operator<<(std::ostream &os, const Complexe &c) {
    std::stringstream ss;
    c.afficher(ss);
    return os << ss.str();
}