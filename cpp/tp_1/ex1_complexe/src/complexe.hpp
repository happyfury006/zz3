#ifndef COMPLEXE_HPP
#define COMPLEXE_HPP

#include <iostream>
#include <exception>
#include <sstream>
#include <cmath>
#include <vector>

class Algebrique;

class Complexe{
    public:
        Complexe();
        virtual void afficher(std::stringstream &str) const= 0;
        virtual Algebrique versAlgebrique() const = 0;
        ~Complexe();

};

std::ostream &operator<<(std::ostream &os, const Complexe &c);

#endif