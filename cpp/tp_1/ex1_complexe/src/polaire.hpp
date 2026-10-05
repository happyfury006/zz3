#ifndef POLAIRE_HPP
#define POLAIRE_HPP

#include "complexe.hpp"

class Algebrique;


class Polaire: public Complexe{
    private:
        double mod;
        double arg;
    public:
        Polaire();
        Polaire(const double nvmod, const double nvarg);
        Polaire(const Algebrique& );
        virtual void afficher(std::stringstream &str) const override;
        double getArg() const;
        double getMod() const;
        void setArg(const double nvArg);
        void setMod(const double nvMod);
        virtual Algebrique versAlgebrique() const override;
        ~Polaire();
};

#endif