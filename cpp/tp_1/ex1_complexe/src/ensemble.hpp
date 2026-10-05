#ifndef ENSEMBLE_HPP
#define ENSEMBLE_HPP

#include "complexe.hpp"

class Ensemble {
    std::vector<Complexe *> elems;
public:
    typedef std::vector<Complexe *>::const_iterator const_iterator;
    Ensemble() = default;
    Ensemble(const Ensemble &) = delete;
    Ensemble &operator=(const Ensemble &) = delete;
    ~Ensemble();
    void ajouter(const Complexe &c);
    std::size_t size() const;
    const_iterator begin() const;
    const_iterator end() const;
};
#endif