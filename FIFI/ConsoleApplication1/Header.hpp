#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

// ---------------------------------------------------------------------------
// Dimensions (l'ancien code avait 30 sommets / 5 successeurs : trop petit
// pour le graphe du TP qui a 210 sommets et jusqu'a 8 successeurs)
// ---------------------------------------------------------------------------
const int nbmax_sommet = 1000;
const int nbmax_succ   = 20;
const int nb_crit      = 3;          // 3 informations par arc
const double c_infini  = 1e18;

typedef struct t_sommet
{
	int ns;                                  // nombre de successeurs
	int succ[nbmax_succ + 1];                 // indices 1..ns
	double distance[nbmax_succ + 1][nb_crit]; // cout de l'arc pour chaque critere
	bool manquant[nbmax_succ + 1];           // vrai si des valeurs etaient absentes du fichier
} t_sommet;

typedef struct t_graphe {
	int n;
	t_sommet liste[nbmax_sommet + 1];        // indices 1..n
} t_graphe;

typedef struct t_solution {
	int depart;
	int destination;
	int critere;
	double date[nbmax_sommet + 1];
	int pere[nbmax_sommet + 1];
} t_solution;

// ----------------------------- multi-objectif ------------------------------
typedef struct t_label {
	double c[nb_crit];   // couts cumules
	int sommet;
	int pere;            // indice du label pere (-1 pour la racine)
	bool actif;          // faux si le label a ete domine / supprime
} t_label;

// regle appliquee quand un sommet a deja son nombre max de labels
enum t_regle {
	REGLE_REFUSER = 0,        // on garde les premiers arrives
	REGLE_SOMME_PONDEREE = 1, // on remplace le pire label (somme normalisee)
	REGLE_DIVERSITE = 2       // on garde les extremes de chaque critere en priorite
};

enum t_ordre {
	ORDRE_FIFO = 0,       // file : label-correcting classique
	ORDRE_LIFO = 1,       // pile
	ORDRE_LEXICO = 2      // plus petit label d'abord (ordre lexicographique)
};

typedef struct t_param_mo {
	int max_labels;       // 0 = illimite
	t_regle regle;
	t_ordre ordre;
} t_param_mo;

typedef struct t_resultat_mo {
	vector<t_label> labels;      // tous les labels crees
	vector<int> front;           // indices des labels non domines a la destination
	long long nb_labels_crees;
	int max_labels_sommet;       // max observe de labels actifs sur un sommet
	double temps_ms;
} t_resultat_mo;

// ------------------------------- fonctions ---------------------------------
bool lire_fichier(t_graphe& g, const string& nom_fichier);
void afficher_graphe_resume(const t_graphe& g);

// mono-critere
t_solution plus_court_chemin(const t_graphe& g, int depart, int destination, int critere); // Dijkstra
t_solution bellmann(const t_graphe& g, int depart, int destination, int critere);
vector<int> chemin(const t_solution& s);
void couts_chemin(const t_graphe& g, const vector<int>& ch, double res[nb_crit]);
void afficher_chemin(const vector<int>& ch);

// multi-objectif
t_resultat_mo multi_objectif(const t_graphe& g, int depart, int destination, const t_param_mo& p);
vector<int> chemin_label(const t_resultat_mo& r, int id_label);
void afficher_front(const t_resultat_mo& r, bool avec_chemins);
bool domine(const double a[nb_crit], const double b[nb_crit]);

// variation +/- pct sur les arcs
void perturber(const t_graphe& origine, t_graphe& resultat, double pct, unsigned int graine);

#endif // HEADER_HPP
