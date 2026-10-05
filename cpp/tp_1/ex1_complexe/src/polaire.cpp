#include "polaire.hpp"
#include "algebrique.hpp"

Polaire::Polaire():mod(0),arg(0){

}

Polaire::Polaire(const double nvMod, const double nvArg):mod(nvMod),arg(nvArg){

}
Polaire::Polaire(const Algebrique& a):mod(std::hypot(a.getRe(),a.getIm())),arg(std::atan2(a.getIm(),a.getRe())){

}

double Polaire::getMod() const {
    return mod;
}

double Polaire::getArg() const {
    return arg;
}
void Polaire::setMod(const double nvMod) {
    mod=nvMod;
}

void Polaire::setArg(const double nvArg) {
    arg=nvArg;
}


void Polaire::afficher(std::stringstream &str) const {
    str << "(mod=" << mod << ";arg=" << arg << ")";
}
Algebrique Polaire::versAlgebrique() const {
    return Algebrique(*this);
}

Polaire::~Polaire(){

}

