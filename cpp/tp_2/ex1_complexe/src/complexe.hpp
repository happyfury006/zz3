#ifndef COMPLEXE_HPP
#define COMPLEXE_HPP

#include <iostream>

class Algebrique;

class Complexe {
public:
  virtual ~Complexe() = default;  // OBLIGATOIRE : on fait delete via Complexe*
  virtual void afficher(std::ostream &os) const = 0;
  virtual Algebrique versAlgebrique() const = 0;
  virtual Complexe *clone() const = 0;  // copie polymorphe (pour Ensemble)
};

std::ostream &operator<<(std::ostream &os, const Complexe &c);

#endif
