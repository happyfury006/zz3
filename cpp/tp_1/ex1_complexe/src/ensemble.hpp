#ifndef ENSEMBLE_HPP
#define ENSEMBLE_HPP

#include <cstddef>
#include <vector>

#include "algebrique.hpp"
#include "complexe.hpp"
#include "polaire.hpp"

class Ensemble {
  std::vector<Complexe *> elems;  // l'Ensemble POSSÈDE ses éléments (clones)

public:
  using iterator = std::vector<Complexe *>::const_iterator;
  using const_iterator = std::vector<Complexe *>::const_iterator;

  Ensemble() = default;
  Ensemble(const Ensemble &autre);
  Ensemble &operator=(const Ensemble &autre);
  ~Ensemble();

  void ajouter(const Complexe &c);
  std::size_t size() const;

  const_iterator begin() const;
  const_iterator end() const;

private:
  void vider();
};

// Q6 : fonction moyenne (renvoie (0,0) si l'ensemble est vide)
Algebrique moyenne(const Ensemble &ens);

// Q6 : versions foncteurs
struct MoyenneAlgebrique {
  Algebrique operator()(const Ensemble &ens) const;
};

struct MoyennePolaire {
  Polaire operator()(const Ensemble &ens) const;
};

#endif
