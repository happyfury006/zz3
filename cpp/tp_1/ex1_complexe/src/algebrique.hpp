#ifndef ALGEBRIQUE_HPP
#define ALGEBRIQUE_HPP

#include "complexe.hpp"
class Polaire;

class Algebrique : public Complexe {
    private:
        double re;
        double im;
    public:
        Algebrique();
        Algebrique(const double nvre, const double nvim);
        Algebrique(const Polaire& );
        double getRe() const;
        double getIm() const;
        void setRe(const double nvRe);
        void setIm(const double nvIm);
        virtual void afficher(std::stringstream &str) const override;
        virtual Algebrique versAlgebrique() const override;
        ~Algebrique();

};
#endif
