#include "polaire.hpp"
#include "algebrique.hpp"

#include <cmath>

Polaire::Polaire(double m, double a) : mod(m), arg(a) {}

Polaire::Polaire(const Algebrique &a)
    : mod(std::hypot(a.getRe(), a.getIm())),
      arg(std::atan2(a.getIm(), a.getRe())) {}

double Polaire::getMod() const { return mod; }
double Polaire::getArg() const { return arg; }
void Polaire::setMod(double m) { mod = m; }
void Polaire::setArg(double a) { arg = a; }

void Polaire::afficher(std::ostream &os) const {
  os << "(mod=" << mod << ";arg=" << arg << ")";
}

Algebrique Polaire::versAlgebrique() const { return Algebrique(*this); }

Polaire *Polaire::clone() const { return new Polaire(*this); }
