#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <sstream>
#include <typeinfo>

#include <algebrique.hpp>
// #include <ensemble.hpp>
#include <polaire.hpp>

// #1 --------------------------------------------------------------------------
 TEST_CASE("TP1_Polaire::Constructeur") {
  const double mod = 24.0;
  const double arg = 12.0;

  Polaire p(mod, arg);

  REQUIRE(p.getMod() == Catch::Approx(mod));
  REQUIRE(p.getArg() == Catch::Approx(arg));
} 

// #2 --------------------------------------------------------------------------
 TEST_CASE("TP1_Polaire::ConstructeurDefaut") {
  Polaire p;

  REQUIRE(p.getMod() == Catch::Approx(0.0));
  REQUIRE(p.getArg() == Catch::Approx(0.0));
} 

// #3 --------------------------------------------------------------------------
 TEST_CASE("TP1_Polaire::Accesseurs") {
  const double mod = 24.0;
  const double arg = 12.0;

  Polaire p(13.0, 25.0);

  p.setMod(mod);
  p.setArg(arg);

  REQUIRE(p.getMod() == Catch::Approx(mod));
  REQUIRE(p.getArg() == Catch::Approx(arg));
} 

// #4 --------------------------------------------------------------------------
 TEST_CASE("TP1_Polaire::AccesseursConstants") {
  const Polaire p;

  REQUIRE(p.getMod() == Catch::Approx(0.0));
  REQUIRE(p.getArg() == Catch::Approx(0.0));
} 

// #5 --------------------------------------------------------------------------
 TEST_CASE("TP1_Polaire::Affichage") {
  Polaire p(12.0, 24.0);
  std::stringstream flux;

  p.afficher(flux);

  REQUIRE(flux.str() == "(mod=12;arg=24)");
}

// #6 --------------------------------------------------------------------------
 TEST_CASE("TP1_Algebrique::Constructeur") {
  const double re = 12.0;
  const double im = 24.0;

  Algebrique z(re, im);

  REQUIRE(z.getRe() == Catch::Approx(re));
  REQUIRE(z.getIm() == Catch::Approx(im));
} 

// #7 --------------------------------------------------------------------------
 TEST_CASE("TP1_Algebrique::ConstructeurDefaut") {
  Algebrique z;

  REQUIRE(z.getRe() == Catch::Approx(0.0));
  REQUIRE(z.getIm() == Catch::Approx(0.0));
} 

// #8 --------------------------------------------------------------------------
 TEST_CASE("TP1_Algebrique::Accesseurs") {
  const double re = 12.0;
  const double im = 24.0;

  Algebrique z(13.0, 25.0);

  z.setRe(re);
  z.setIm(im);

  REQUIRE(z.getRe() == Catch::Approx(re));
  REQUIRE(z.getIm() == Catch::Approx(im));
} 

// #9 --------------------------------------------------------------------------
 TEST_CASE("TP1_Algebrique::AccesseursConstants") {
  const Algebrique z;

  REQUIRE(z.getRe() == Catch::Approx(0.0));
  REQUIRE(z.getIm() == Catch::Approx(0.0));
} 

// #10 -------------------------------------------------------------------------
TEST_CASE("TP1_Algebrique::Affichage") {
  Algebrique z(12.0, 24.0);
  std::stringstream flux;

  z.afficher(flux);

  REQUIRE(flux.str() == "(re=12;im=24)");
} 

// #11 -------------------------------------------------------------------------
 TEST_CASE("TP1_Complexe::AffichageVirtuel") {
  Polaire p(12.0, 24.0);
  Algebrique z(13.0, 25.0);

  const Complexe &c1 = p;
  const Complexe &c2 = z;

  std::stringstream flux1;
  std::stringstream flux2;

  c1.afficher(flux1);
  c2.afficher(flux2);

  REQUIRE(flux1.str() == "(mod=12;arg=24)");
  REQUIRE(flux2.str() == "(re=13;im=25)");
} 

// #12 -------------------------------------------------------------------------
 TEST_CASE("TP1_Complexe::OperateurFlux") {
  Polaire p(12.0, 24.0);
  Algebrique z(13.0, 25.0);

  const Complexe &c1 = p;
  const Complexe &c2 = z;

  std::stringstream flux1;
  std::stringstream flux2;

  flux1 << c1;
  flux2 << c2;

  REQUIRE(flux1.str() == "(mod=12;arg=24)");
  REQUIRE(flux2.str() == "(re=13;im=25)");
} 

// #13 -------------------------------------------------------------------------
 TEST_CASE("TP1_Complexe::ConversionVersPolaire_V1") {
  const double re = 12.0;
  const double im = 24.0;
  const double mod = 26.832815;
  const double arg = 1.1071;

  Algebrique z(re, im);
  Polaire p(z);

  REQUIRE(p.getMod() == Catch::Approx(mod).epsilon(1e-3));
  REQUIRE(p.getArg() == Catch::Approx(arg).epsilon(1e-3));
} 

// #14 -------------------------------------------------------------------------
 TEST_CASE("TP1_Complexe::ConversionVersAlgebrique_V1") {
  const double mod = 24.0;
  const double arg = 12.0;
  const double re = 20.25249;
  const double im = -12.8777;

  Polaire p(mod, arg);
  Algebrique z(p);

  REQUIRE(z.getRe() == Catch::Approx(re).epsilon(1e-3));
  REQUIRE(z.getIm() == Catch::Approx(im).epsilon(1e-3));
} 

// #15 -------------------------------------------------------------------------
 TEST_CASE("TP1_Complexe::ConversionVersAlgebrique_V2") {
  const double mod = 24.0;
  const double arg = 12.0;
  const double re = 20.25249;
  const double im = -12.8777;

  const Polaire p(mod, arg);
  Algebrique z = p.versAlgebrique();

  REQUIRE(z.getRe() == Catch::Approx(re).epsilon(1e-3));
  REQUIRE(z.getIm() == Catch::Approx(im).epsilon(1e-3));
} 

// #16 -------------------------------------------------------------------------
TEST_CASE("TP1_Complexe::ConversionVersPolaire_V2") {
  const double re = 12.0;
  const double im = 24.0;

  const Algebrique z(re, im);
  Algebrique z2 = z.versAlgebrique();

  REQUIRE(z2.getRe() == Catch::Approx(re).epsilon(1e-3));
  REQUIRE(z2.getIm() == Catch::Approx(im).epsilon(1e-3));
} 

// #17 -------------------------------------------------------------------------
 TEST_CASE("TP1_Complexe::ConversionVirtuel") {
  const double re = 12.0;
  const double im = 24.0;
  const double mod = 26.832815;
  const double arg = 1.1071;

  Algebrique z(re, im);
  Polaire p(mod, arg);

  const Complexe *c1 = &z;
  const Complexe *c2 = &p;

  Algebrique z1 = c1->versAlgebrique();
  Algebrique z2 = c2->versAlgebrique();

  REQUIRE(z1.getRe() == Catch::Approx(re).epsilon(1e-3));
  REQUIRE(z1.getIm() == Catch::Approx(im).epsilon(1e-3));
  REQUIRE(z2.getRe() == Catch::Approx(re).epsilon(1e-3));
  REQUIRE(z2.getIm() == Catch::Approx(im).epsilon(1e-3));
} 

// #18 -------------------------------------------------------------------------
 TEST_CASE("TP1_Ensemble::Ajout") {
  Algebrique z1(12.0, 24.0);
  Polaire z2(25.0, 13.0);
  Polaire z3(z1);
  Algebrique z4(z2);

  Ensemble ens;

  REQUIRE(ens.size() == 0u);

  ens.ajouter(z1);
  ens.ajouter(z2);
  ens.ajouter(z3);
  ens.ajouter(z4);

  REQUIRE(ens.size() == 4u);
} 

// #19 -------------------------------------------------------------------------
 TEST_CASE("TP1_Ensemble::Iterateurs") {
  Algebrique z1(12.0, 24.0);
  Polaire z2(25.0, 13.0);
  Polaire z3(z1);
  Algebrique z4(z2);

  Ensemble ens;

  ens.ajouter(z1);
  ens.ajouter(z2);
  ens.ajouter(z3);
  ens.ajouter(z4);

  Complexe *t[4];
  unsigned i = 0;
  Ensemble::const_iterator it = ens.begin();

  while (it != ens.end())
    t[i++] = *(it++);

  REQUIRE(typeid(*(t[0])) == typeid(Algebrique));
  REQUIRE(typeid(*(t[1])) == typeid(Polaire));
  REQUIRE(typeid(*(t[2])) == typeid(Polaire));
  REQUIRE(typeid(*(t[3])) == typeid(Algebrique));

  Algebrique &z5 = *static_cast<Algebrique *>(t[0]);
  Polaire &z6 = *static_cast<Polaire *>(t[1]);
  Polaire &z7 = *static_cast<Polaire *>(t[2]);
  Algebrique &z8 = *static_cast<Algebrique *>(t[3]);

  REQUIRE(z5.getRe() == Catch::Approx(12.0));
  REQUIRE(z5.getIm() == Catch::Approx(24.0));
  REQUIRE(z6.getArg() == Catch::Approx(13.0));
  REQUIRE(z6.getMod() == Catch::Approx(25.0));

  REQUIRE(z7.getArg() == Catch::Approx(1.1071).epsilon(1e-3));
  REQUIRE(z7.getMod() == Catch::Approx(26.8328).epsilon(1e-3));
  REQUIRE(z8.getRe() == Catch::Approx(22.6861).epsilon(1e-3));
  REQUIRE(z8.getIm() == Catch::Approx(10.5041).epsilon(1e-3));
} 

// #20-23 ----------------------------------------------------------------------
/* double re[] = {3, 7, 13, 27};
double im[] = {4, 8, 16, 32};

Algebrique z1(re[0], im[0]);
Algebrique z2(re[1], im[1]);
Algebrique z3(re[2], im[2]);
Algebrique z4(re[3], im[3]);

Ensemble ens; */

// #20 -------------------------------------------------------------------------
/* TEST_CASE("TP1_Ensemble::MoyenneVide") {
  Algebrique b = moyenne(ens);

  REQUIRE(b.getRe() == 0);
  REQUIRE(b.getIm() == 0);
} */

// #21 -------------------------------------------------------------------------
/* TEST_CASE("TP1_Ensemble::Moyenne") {
  ens.ajouter(z1);
  ens.ajouter(z2);
  ens.ajouter(z3);
  ens.ajouter(z4);

  Algebrique b = moyenne(ens);

  REQUIRE(b.getRe() == Catch::Approx((re[0] + re[1] + re[2] + re[3]) / 4));
  REQUIRE(b.getIm() == Catch::Approx((im[0] + im[1] + im[2] + im[3]) / 4));
} */

// #22 -------------------------------------------------------------------------
/* TEST_CASE("TP1_Ensemble::MoyenneAlgebrique") {
  Algebrique b = MoyenneAlgebrique()(ens);

  REQUIRE(b.getRe() == Catch::Approx((re[0] + re[1] + re[2] + re[3]) / 4));
  REQUIRE(b.getIm() == Catch::Approx((im[0] + im[1] + im[2] + im[3]) / 4));
} */

// #23 -------------------------------------------------------------------------
/* TEST_CASE("TP1_Ensemble::MoyennePolaire") {
  Polaire p(Algebrique((re[0] + re[1] + re[2] + re[3]) / 4,
                       (im[0] + im[1] + im[2] + im[3]) / 4));
  Polaire b = MoyennePolaire()(ens);

  REQUIRE(b.getArg() == Catch::Approx(p.getArg()));
  REQUIRE(b.getMod() == Catch::Approx(p.getMod()));
} */
