#include "ensemble.hpp"

Ensemble::Ensemble(const Ensemble &autre) {
  elems.reserve(autre.elems.size());
  for (const Complexe *c : autre.elems) elems.push_back(c->clone());
}

Ensemble &Ensemble::operator=(const Ensemble &autre) {
  if (this != &autre) {
    Ensemble copie(autre);          // copy-and-swap : sûr en cas d'exception
    elems.swap(copie.elems);
  }
  return *this;
}

Ensemble::~Ensemble() { vider(); }

void Ensemble::vider() {
  for (Complexe *c : elems) delete c;
  elems.clear();
}

void Ensemble::ajouter(const Complexe &c) { elems.push_back(c.clone()); }

std::size_t Ensemble::size() const { return elems.size(); }

Ensemble::const_iterator Ensemble::begin() const { return elems.begin(); }
Ensemble::const_iterator Ensemble::end() const { return elems.end(); }

Algebrique moyenne(const Ensemble &ens) {
  if (ens.size() == 0) return Algebrique(0.0, 0.0);

  double sRe = 0.0, sIm = 0.0;
  for (const Complexe *c : ens) {
    Algebrique a = c->versAlgebrique();  // marche quel que soit le type réel
    sRe += a.getRe();
    sIm += a.getIm();
  }
  const double n = static_cast<double>(ens.size());
  return Algebrique(sRe / n, sIm / n);
}

Algebrique MoyenneAlgebrique::operator()(const Ensemble &ens) const {
  return moyenne(ens);
}

Polaire MoyennePolaire::operator()(const Ensemble &ens) const {
  return Polaire(moyenne(ens));
}
