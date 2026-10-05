#include "Header.hpp"
#include <cstdlib>
#include <cmath>
#include <iomanip>

// Usage : ConsoleApplication1.exe [fichier] [depart] [arrivee]
//   par defaut : DLP_210_mod.dat  1  210

// Le graphe fait ~500 Ko : on le met en statique (sur la pile, Visual Studio
// plante avec un "stack overflow" car la pile par defaut ne fait que 1 Mo).
static t_graphe g;
static t_graphe g_bruite;

static const char* nom_crit[nb_crit] = { "critere 1", "critere 2", "critere 3" };

// vrai si une solution du front atteint la valeur optimale du critere c
static bool front_contient_optimum(const t_resultat_mo& r, int c, double opt)
{
	for (int id : r.front) if (fabs(r.labels[id].c[c] - opt) < 1e-6 * max(1.0, opt)) return true;
	return false;
}

// nombre de points du front "vrai" retrouves dans un front approche
static int nb_points_retrouves(const t_resultat_mo& vrai, const t_resultat_mo& approx)
{
	int n = 0;
	for (int a : vrai.front)
		for (int b : approx.front) {
			bool egal = true;
			for (int c = 0; c < nb_crit; c++)
				if (fabs(vrai.labels[a].c[c] - approx.labels[b].c[c]) > 1e-6) { egal = false; break; }
			if (egal) { n++; break; }
		}
	return n;
}

int main(int argc, char* argv[])
{
	string nom = (argc > 1) ? argv[1] : "DLP_210_mod.dat";
	if (!lire_fichier(g, nom)) {
		cout << "Appuyez sur Entree..." << endl;
		cin.get();
		return 1;
	}
	int depart  = (argc > 2) ? atoi(argv[2]) : 1;
	int arrivee = (argc > 3) ? atoi(argv[3]) : g.n;
	afficher_graphe_resume(g);
	cout << "Depart = " << depart << ", arrivee = " << arrivee << endl << endl;

	// -----------------------------------------------------------------------
	// 1. Plus courts chemins mono-critere (Dijkstra, verifie par Bellman)
	// -----------------------------------------------------------------------
	cout << "===== 1. Plus courts chemins mono-critere =====" << endl;
	double opt[nb_crit];
	for (int c = 0; c < nb_crit; c++) {
		t_solution sd = plus_court_chemin(g, depart, arrivee, c);
		t_solution sb = bellmann(g, depart, arrivee, c);
		opt[c] = sd.date[arrivee];
		vector<int> ch = chemin(sd);
		double cc[nb_crit];
		couts_chemin(g, ch, cc);

		cout << nom_crit[c] << " : optimum = " << sd.date[arrivee]
		     << "  (Bellman = " << sb.date[arrivee]
		     << (fabs(sd.date[arrivee] - sb.date[arrivee]) < 1e-6 ? ", OK" : ", DIFFERENT !") << ")" << endl;
		cout << "   chemin : "; afficher_chemin(ch); cout << endl;
		cout << "   couts du chemin sur les 3 criteres : (" << cc[0] << " ; " << cc[1] << " ; " << cc[2] << ")" << endl;
	}
	cout << endl;

	// -----------------------------------------------------------------------
	// 2. Multi-objectif exact (nombre de labels illimite)
	// -----------------------------------------------------------------------
	cout << "===== 2. Plus court chemin multi-objectif (labels illimites) =====" << endl;
	t_param_mo p_exact = { 0, REGLE_REFUSER, ORDRE_FIFO };
	t_resultat_mo exact = multi_objectif(g, depart, arrivee, p_exact);
	afficher_front(exact, true);
	cout << "  Labels crees : " << exact.nb_labels_crees
	     << " | max labels sur un sommet : " << exact.max_labels_sommet
	     << " | temps : " << exact.temps_ms << " ms" << endl;
	for (int c = 0; c < nb_crit; c++)
		cout << "  Le front contient l'optimum du " << nom_crit[c] << " : "
		     << (front_contient_optimum(exact, c, opt[c]) ? "OUI" : "NON (bug !)") << endl;
	cout << endl;

	// -----------------------------------------------------------------------
	// 3. Nombre limite de labels par sommet + regle de gestion
	// -----------------------------------------------------------------------
	cout << "===== 3. Limitation du nombre de labels par sommet =====" << endl;
	const char* nom_regle[3] = { "refuser", "somme ponderee", "diversite" };
	int limites[] = { 1, 2, 3, 5, 10, 20 };
	cout << left << setw(8) << "max" << setw(17) << "regle" << setw(12) << "taille"
	     << setw(18) << "pts exacts trouves" << "  temps(ms)" << right << endl;
	for (int L : limites)
		for (int rg = 0; rg < 3; rg++) {
			t_param_mo p = { L, (t_regle)rg, ORDRE_FIFO };
			t_resultat_mo r = multi_objectif(g, depart, arrivee, p);
			cout << left << setw(8) << L << setw(17) << nom_regle[rg] << setw(12) << r.front.size()
			     << setw(18) << (to_string(nb_points_retrouves(exact, r)) + "/" + to_string(exact.front.size()))
			     << "  " << r.temps_ms << right << endl;
		}
	cout << endl;

	// -----------------------------------------------------------------------
	// 4. Ordre de passage sur les sommets
	// -----------------------------------------------------------------------
	cout << "===== 4. Ordre de traitement des labels (labels illimites) =====" << endl;
	const char* nom_ordre[3] = { "FIFO (file)", "LIFO (pile)", "lexicographique" };
	for (int o = 0; o < 3; o++) {
		t_param_mo p = { 0, REGLE_REFUSER, (t_ordre)o };
		t_resultat_mo r = multi_objectif(g, depart, arrivee, p);
		cout << "  " << left << setw(18) << nom_ordre[o] << right
		     << " front=" << r.front.size() << "  labels crees=" << r.nb_labels_crees
		     << "  temps=" << r.temps_ms << " ms" << endl;
	}
	cout << endl;

	// -----------------------------------------------------------------------
	// 5. Variation de +/-20% sur les arcs, 20 executions
	// -----------------------------------------------------------------------
	cout << "===== 5. Variation +/-20% des valeurs des arcs (20 executions) =====" << endl;
	for (int run = 1; run <= 20; run++) {
		perturber(g, g_bruite, 0.20, (unsigned)run);
		t_resultat_mo r = multi_objectif(g_bruite, depart, arrivee, p_exact);
		cout << "  run " << setw(2) << run << " : front=" << setw(3) << r.front.size() << "  optima = (";
		for (int c = 0; c < nb_crit; c++) {
			t_solution s = plus_court_chemin(g_bruite, depart, arrivee, c);
			cout << (c ? " ; " : "") << fixed << setprecision(1) << s.date[arrivee];
		}
		cout.unsetf(ios::floatfield);
		cout << setprecision(6) << ")" << endl;
	}

	cout << endl << "Termine. Appuyez sur Entree..." << endl;
	cin.get();
	return 0;
}
