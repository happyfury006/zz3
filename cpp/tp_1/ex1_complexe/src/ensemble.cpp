#include "ensemble.hpp"

Ensemble::~Ensemble() {
    for (Complexe *c : elems)
        delete c;
}

void Ensemble::ajouter(const Complexe &c) {
    elems.push_back(c.clone());
}

std::size_t Ensemble::size() const {
    return elems.size();
}

Ensemble::const_iterator Ensemble::begin() const {
    return elems.begin();
}

Ensemble::const_iterator Ensemble::end() const {
    return elems.end();
}