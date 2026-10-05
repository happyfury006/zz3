#ifndef POLAIRE_HPP
#define POLAIRE_HPP

#include "complexe.hpp"

class Algebrique;  // déclaration anticipée

class Polaire : public Complexe {
  double mod;
  double arg;  // en radians

public:
  Polaire(double mod = 0.0, double arg = 0.0);
  Polaire(const Algebrique &a);

  double getMod() const;
  double getArg() const;
  void setMod(double m);
  void setArg(double a);

  void afficher(std::ostream &os) const override;
  Algebrique versAlgebrique() const override;
  Polaire *clone() const override;
};

#endif
