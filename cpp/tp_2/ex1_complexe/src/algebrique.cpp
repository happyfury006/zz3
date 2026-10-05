#include "algebrique.hpp"
#include "polaire.hpp"

#include <cmath>

Algebrique::Algebrique(double r, double i) : re(r), im(i) {}

Algebrique::Algebrique(const Polaire &p)
    : re(p.getMod() * std::cos(p.getArg())),
      im(p.getMod() * std::sin(p.getArg())) {}

double Algebrique::getRe() const { return re; }
double Algebrique::getIm() const { return im; }
void Algebrique::setRe(double r) { re = r; }
void Algebrique::setIm(double i) { im = i; }

void Algebrique::afficher(std::ostream &os) const {
  os << "(re=" << re << ";im=" << im << ")";
}

Algebrique Algebrique::versAlgebrique() const { return *this; }

Algebrique *Algebrique::clone() const { return new Algebrique(*this); }
