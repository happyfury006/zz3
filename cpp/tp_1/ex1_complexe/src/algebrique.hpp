#ifndef ALGEBRIQUE_HPP
#define ALGEBRIQUE_HPP

#include "complexe.hpp"

class Polaire;  // déclaration anticipée

class Algebrique : public Complexe {
  double re;
  double im;

public:
  Algebrique(double re = 0.0, double im = 0.0);
  Algebrique(const Polaire &p);

  double getRe() const;
  double getIm() const;
  void setRe(double r);
  void setIm(double i);

  void afficher(std::ostream &os) const override;
  Algebrique versAlgebrique() const override;
  Algebrique *clone() const override;
};

#endif
