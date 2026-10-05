#include "algebrique.hpp"
#include "polaire.hpp"
Algebrique::Algebrique():re(0), im(0){}

Algebrique::Algebrique(const double nvRe,const double nvIm): re(nvRe),im(nvIm){

}
Algebrique::Algebrique(const Polaire& p)
    : re(std::cos(p.getArg()) * p.getMod()),
      im(std::sin(p.getArg()) * p.getMod()) {}

double Algebrique::getRe() const {
    return re;
}

double Algebrique::getIm() const {
    return im;
}
void Algebrique::setRe(const double nvRe) {
    re =nvRe;
}

void Algebrique::setIm(const double nvIm) {
    im=nvIm;
}

void Algebrique::afficher(std::stringstream &str) const {
    str << "(re=" << re << ";im=" << im << ")";
}
Algebrique Algebrique::versAlgebrique() const {
    return *this;
}

Algebrique::~Algebrique(){

}