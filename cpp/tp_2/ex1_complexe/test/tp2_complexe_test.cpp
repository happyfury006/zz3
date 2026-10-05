#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>

#include <limits>
#include <vector>

#include <algebrique.hpp>
#include <ensemble.hpp>
#include <polaire.hpp>

// #0 --------------------------------------------------------------------------
/* TEST_CASE("TP2_Polaire::setArg") {
  Polaire p;

	p.setArg(std::numbers::pi);
  REQUIRE(p.getArg() == Catch::Approx(std::numbers::pi));

	p.setArg(-std::numbers::pi);
  REQUIRE(p.getArg() == Catch::Approx(-std::numbers::pi));

	p.setArg(2 * std::numbers::pi);
  REQUIRE(p.getArg() == Catch::Approx(0));

	p.setArg(1000);
  REQUIRE(p.getArg() == Catch::Approx(0.973536));
} */

// #1 --------------------------------------------------------------------------
/* TEST_CASE("TP2_Ensemble::Ajout") {
  Ensemble<Algebrique> ens;

  REQUIRE(ens.size() == 0u);

  ens.ajouter(Algebrique(12.0, 34.0));
  ens.ajouter(Algebrique(56.0, 78.0));
  ens.ajouter(Algebrique(90.0, 12.0));
  ens.ajouter(Algebrique(34.0, 56.0));

  REQUIRE(ens.size() == 4u);
} */

// #2 --------------------------------------------------------------------------
/* TEST_CASE("TP2_Ensemble::Iterateurs") {
  Polaire p1(12.0, 34.0);
  Polaire p2(56.0, 78.0);
  Polaire p3(90.0, 12.0);
  Polaire p4(34.0, 56.0);

  Ensemble<Polaire> ens;

  ens.ajouter(p1);
  ens.ajouter(p2);
  ens.ajouter(p3);
  ens.ajouter(p4);

  Polaire t[4];
  unsigned i = 0;
  Ensemble<Polaire>::const_iterator it = ens.begin();

  while (it != ens.end())
    t[i++] = *(it++);

  REQUIRE(t[0].getMod() == Catch::Approx(p1.getMod()));
  REQUIRE(t[0].getArg() == Catch::Approx(p1.getArg()));
  REQUIRE(t[1].getMod() == Catch::Approx(p2.getMod()));
  REQUIRE(t[1].getArg() == Catch::Approx(p2.getArg()));
  REQUIRE(t[2].getMod() == Catch::Approx(p3.getMod()));
  REQUIRE(t[2].getArg() == Catch::Approx(p3.getArg()));
  REQUIRE(t[3].getMod() == Catch::Approx(p4.getMod()));
  REQUIRE(t[3].getArg() == Catch::Approx(p4.getArg()));
} */

// #3 --------------------------------------------------------------------------
/* TEST_CASE("TP2_Algebrique::operator+") {
  Algebrique a(3.0, 4.0);
  Algebrique b(7.0, 8.0);

  Algebrique r = a + b;

  REQUIRE(r.getRe() == Catch::Approx(3.0 + 7.0));
  REQUIRE(r.getIm() == Catch::Approx(4.0 + 8.0));
} */

// #4 --------------------------------------------------------------------------
/* TEST_CASE("TP2_Algebrique::operator-") {
  Algebrique a(3.0, 4.0);
  Algebrique b(7.0, 8.0);

  Algebrique r = a - b;

  REQUIRE(r.getRe() == Catch::Approx(3.0 - 7.0));
  REQUIRE(r.getIm() == Catch::Approx(4.0 - 8.0));
} */

// #5 --------------------------------------------------------------------------
/* TEST_CASE("TP2_Algebrique::operator*") {
  Algebrique a(3.0, 4.0);
  Algebrique b(7.0, 8.0);

  Algebrique r = a * b;

  REQUIRE(r.getRe() == Catch::Approx(3.0 * 7.0 - 4.0 * 8.0));
  REQUIRE(r.getIm() == Catch::Approx(3.0 * 8.0 + 7.0 * 4.0));
} */

// #6 --------------------------------------------------------------------------
/* TEST_CASE("TP2_Algebrique::operator/") {
  Algebrique a(3.0, 4.0);

  Algebrique r = a / 2.5;

  REQUIRE(r.getRe() == Catch::Approx(3.0 / 2.5));
  REQUIRE(r.getIm() == Catch::Approx(4.0 / 2.5));
} */

// #7 --------------------------------------------------------------------------
/* TEST_CASE("TP2_Ensemble::Moyenne_Algebrique") {
  Ensemble<Algebrique> ens;

  Algebrique b0 = moyenne(ens);
  REQUIRE(b0.getRe() == Catch::Approx(0.0));
  REQUIRE(b0.getIm() == Catch::Approx(0.0));

  Algebrique z1(3.0, 4.0);
  Algebrique z2(7.0, 8.0);
  Algebrique z3(13.0, 16.0);
  Algebrique z4(27.0, 32.0);

  ens.ajouter(z1);
  ens.ajouter(z2);
  ens.ajouter(z3);
  ens.ajouter(z4);

  Algebrique b = moyenne(ens);
  REQUIRE(b.getRe() == Catch::Approx((3.0 + 7.0 + 13.0 + 27.0) / 4.0));
  REQUIRE(b.getIm() == Catch::Approx((4.0 + 8.0 + 16.0 + 32.0) / 4.0));
} */

// #8 --------------------------------------------------------------------------
/* TEST_CASE("TP2_Ensemble::Moyenne_Polaire") {
  Polaire p1(12.0, 34.0);
  Polaire p2(56.0, 78.0);
  Polaire p3(90.0, 12.0);
  Polaire p4(34.0, 56.0);

  Ensemble<Polaire> ens;

  Polaire b0 = moyenne(ens);
  REQUIRE(b0.getMod() == Catch::Approx(0.0));
  REQUIRE(b0.getArg() == Catch::Approx(0.0));

  ens.ajouter(p1);
  ens.ajouter(p2);
  ens.ajouter(p3);
  ens.ajouter(p4);

  Algebrique somme = p1.versAlgebrique() + p2.versAlgebrique() +
                     p3.versAlgebrique() + p4.versAlgebrique();
  Polaire attendu(Algebrique(somme.getRe() / 4.0, somme.getIm() / 4.0));

  Polaire b = moyenne(ens);
  REQUIRE(b.getMod() == Catch::Approx(attendu.getMod()));
  REQUIRE(b.getArg() == Catch::Approx(attendu.getArg()));
} */

// #9 --------------------------------------------------------------------------
/* TEST_CASE("TP2_Ensemble::MoyenneGenerique_Ensemble") {
  Ensemble<Algebrique> ens;

  ens.ajouter(Algebrique(3.0, 4.0));
  ens.ajouter(Algebrique(7.0, 8.0));
  ens.ajouter(Algebrique(13.0, 16.0));
  ens.ajouter(Algebrique(27.0, 32.0));

  Algebrique b = moyenne_generique(ens);
  REQUIRE(b.getRe() == Catch::Approx((3.0 + 7.0 + 13.0 + 27.0) / 4.0));
  REQUIRE(b.getIm() == Catch::Approx((4.0 + 8.0 + 16.0 + 32.0) / 4.0));
} */

// #10 -------------------------------------------------------------------------
/* TEST_CASE("TP2_Ensemble::MoyenneGenerique_VecteurAlgebrique") {
  std::vector<Algebrique> v;

  Algebrique b0 = moyenne_generique(v);
  REQUIRE(b0.getRe() == Catch::Approx(0.0));
  REQUIRE(b0.getIm() == Catch::Approx(0.0));

  v.push_back(Algebrique(3.0, 4.0));
  v.push_back(Algebrique(7.0, 8.0));
  v.push_back(Algebrique(13.0, 16.0));
  v.push_back(Algebrique(27.0, 32.0));

  Algebrique b = moyenne_generique(v);
  REQUIRE(b.getRe() == Catch::Approx((3.0 + 7.0 + 13.0 + 27.0) / 4.0));
  REQUIRE(b.getIm() == Catch::Approx((4.0 + 8.0 + 16.0 + 32.0) / 4.0));
} */

// #11 -------------------------------------------------------------------------
/* TEST_CASE("TP2_Ensemble::MoyenneGenerique_VecteurPolaire") {
  Polaire p1(12.0, 34.0);
  Polaire p2(56.0, 78.0);
  Polaire p3(90.0, 12.0);
  Polaire p4(34.0, 56.0);

  std::vector<Polaire> v;
  v.push_back(p1);
  v.push_back(p2);
  v.push_back(p3);
  v.push_back(p4);

  Algebrique somme = p1.versAlgebrique() + p2.versAlgebrique() +
                     p3.versAlgebrique() + p4.versAlgebrique();
  Polaire attendu(Algebrique(somme.getRe() / 4.0, somme.getIm() / 4.0));

  Polaire b = moyenne_generique(v);
  REQUIRE(b.getMod() == Catch::Approx(attendu.getMod()));
  REQUIRE(b.getArg() == Catch::Approx(attendu.getArg()));
} */

// #12 -------------------------------------------------------------------------
/* TEST_CASE("TP2_Ensemble::Rotate_Polaire") {
  Ensemble<Polaire> ens;

  ens.ajouter(Polaire(3.0, 4.0));
  ens.ajouter(Polaire(7.0, 8.0));

	rotate(ens, std::numbers::pi/2.);

	Ensemble<Polaire>::const_iterator it = std::begin(ens);

	REQUIRE((*it).getMod() == Catch::Approx(3.0));
	REQUIRE((*it).getArg() == Catch::Approx(-0.712388));

	++it;

	REQUIRE((*it).getMod() == Catch::Approx(7.0));
	REQUIRE((*it).getArg() == Catch::Approx(-2.995574));

	rotate(ens, -3.*std::numbers::pi/4.);

	it = std::begin(ens);

	REQUIRE((*it).getMod() == Catch::Approx(3.0));
	REQUIRE((*it).getArg() == Catch::Approx(-3.068583));

	++it;

	REQUIRE((*it).getMod() == Catch::Approx(7.0));
	REQUIRE((*it).getArg() == Catch::Approx(0.931416));
} */

// #13 -------------------------------------------------------------------------
/* TEST_CASE("TP2_Ensemble::Rotate_Algebrique") {
  Ensemble<Algebrique> ens;

  ens.ajouter(Algebrique(3.0, 4.0));
  ens.ajouter(Algebrique(7.0, 8.0));

	rotate(ens, std::numbers::pi/2.);

	Ensemble<Algebrique>::const_iterator it = std::begin(ens);

	REQUIRE((*it).getRe() == Catch::Approx(-4.0));
	REQUIRE((*it).getIm() == Catch::Approx(3.0));

	++it;

	REQUIRE((*it).getRe() == Catch::Approx(-8.0));
	REQUIRE((*it).getIm() == Catch::Approx(7.0));

	rotate(ens, -3.*std::numbers::pi/4.);

	it = std::begin(ens);

	REQUIRE((*it).getRe() == Catch::Approx(4.9497));
	REQUIRE((*it).getIm() == Catch::Approx(0.7071));

	++it;

	REQUIRE((*it).getRe() == Catch::Approx(10.6066));
	REQUIRE((*it).getIm() == Catch::Approx(0.7071));
} */

// #14 -------------------------------------------------------------------------
/* TEST_CASE("TP2_Ensemble::RotatePivot") {
  Ensemble<Polaire> ens;

  ens.ajouter(Polaire(3.0, 4.0));
  ens.ajouter(Polaire(7.0, 8.0));

	Algebrique pivotA(1, 1);
	RotatePivot<Polaire, Algebrique>::apply(ens, std::numbers::pi/2, pivotA);

	Ensemble<Polaire>::const_iterator it = std::begin(ens);

	REQUIRE((*it).getMod() == Catch::Approx(4.699109));
	REQUIRE((*it).getArg() == Catch::Approx(-0.430470));

	++it;

	REQUIRE((*it).getMod() == Catch::Approx(5.029708));
	REQUIRE((*it).getArg() == Catch::Approx(-2.937685));

	Polaire pivotP(3, 2);
	RotatePivot<Polaire, Polaire>::apply(ens, -3.*std::numbers::pi/4., pivotP);

	it = std::begin(ens);

	REQUIRE((*it).getMod() == Catch::Approx(8.732864));
	REQUIRE((*it).getArg() == Catch::Approx(2.893904));

	++it;

	REQUIRE((*it).getMod() == Catch::Approx(8.081897));
	REQUIRE((*it).getArg() == Catch::Approx(1.732033));
} */

// #15 -------------------------------------------------------------------------
/* TEST_CASE("TP2_Ensemble::RotatePivot_Algebrique") {
  Ensemble<Algebrique> ens;

  ens.ajouter(Algebrique(3.0, 4.0));
  ens.ajouter(Algebrique(7.0, 8.0));

	Algebrique pivotA(1, 1);
	RotatePivot<Algebrique, Algebrique>::apply(ens, std::numbers::pi/2, pivotA);

	Ensemble<Algebrique>::const_iterator it = std::begin(ens);

	REQUIRE((*it).getRe() == Catch::Approx(-2.0));
	REQUIRE((*it).getIm() == Catch::Approx(3.0));

	++it;

	REQUIRE((*it).getRe() == Catch::Approx(-6.0));
	REQUIRE((*it).getIm() == Catch::Approx(7.0));

	Polaire pivotP(3, 2);
	RotatePivot<Algebrique, Polaire>::apply(ens, std::numbers::pi/2, pivotP);

	it = std::begin(ens);

	REQUIRE((*it).getRe() == Catch::Approx(-1.520548));
	REQUIRE((*it).getIm() == Catch::Approx(1.976332));

	++it;

	REQUIRE((*it).getRe() == Catch::Approx(-5.520548));
	REQUIRE((*it).getIm() == Catch::Approx(-2.023667));
} */

// #16 -------------------------------------------------------------------------
/* TEST_CASE("TP2_Ensemble::RotatePivot_Algebrique_Spe") {
  Ensemble<Algebrique> ens;

	double inf = std::numeric_limits<double>::infinity();
  ens.ajouter(Algebrique(inf, inf));

	RotatePivot<Algebrique, Algebrique>::apply(ens, 0, Algebrique());

	Algebrique const& a = *std::begin(ens);

	// Ce test repose sur le fait que les nombres flottants (float, double)
	// produisent NaN (Not a Number) lorsqu'un calcul dont le résultat est
	// indéterminé est effectuée, par exemple inf - inf, ou 0 / 0.
	// L'implémentation utilisant la classe Polaire ne cause aucun calcul
	// de ce type, contrairement à une implémentation n'utilisant que la
	// classe Algebrique
	REQUIRE(std::isnan(a.getRe()));
} */
