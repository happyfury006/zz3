#include "Header.hpp"
#include <cstdlib>
#include <cmath>
#include <queue>
#include <deque>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>

// ===========================================================================
//  Lecture du fichier DLP_210_mod.dat
//  Format :
//    ligne 1           : n
//    n lignes          : id  ns  succ1 ... succns
//    1 ligne           : m (nombre d'arcs)
//    m lignes          : id_arc  origine  destination  crit1  crit2  crit3  [colonne en trop ignoree]
//    "END OF FILE"
//  ATTENTION : le fichier "_mod" contient des arcs ou crit2 / crit3 sont
//  remplaces par les mots "Duree" et "Cout". On les detecte et on les estime.
// ===========================================================================

static bool est_nombre(const string& s, double& v)
{
	if (s.empty()) return false;
	char* fin = nullptr;
	v = strtod(s.c_str(), &fin);
	return fin != s.c_str() && *fin == '\0';
}

static vector<string> decouper(const string& ligne)
{
	vector<string> res;
	istringstream iss(ligne);
	string t;
	while (iss >> t) res.push_back(t);
	return res;
}

bool lire_fichier(t_graphe& g, const string& nom_fichier)
{
	ifstream fichier(nom_fichier.c_str(), ios::in);
	if (!fichier) {
		cerr << "ERREUR : impossible d'ouvrir '" << nom_fichier << "'" << endl;
		cerr << "  -> placez le fichier dans le repertoire de travail du projet" << endl;
		cerr << "     (Visual Studio : dossier contenant le .vcxproj) ou passez son chemin en argument." << endl;
		return false;
	}

	// on lit toutes les lignes non vides
	vector<vector<string> > lignes;
	string ligne;
	while (getline(fichier, ligne)) {
		vector<string> t = decouper(ligne);
		if (t.empty()) continue;
		if (t[0] == "END") break;
		lignes.push_back(t);
	}

	size_t pos = 0;
	double v;
	if (lignes.empty() || !est_nombre(lignes[0][0], v)) { cerr << "ERREUR : n absent" << endl; return false; }
	g.n = (int)v;
	if (g.n < 1 || g.n > nbmax_sommet) { cerr << "ERREUR : n=" << g.n << " > nbmax_sommet" << endl; return false; }
	pos = 1;

	// --- listes d'adjacence
	for (int i = 1; i <= g.n; i++) g.liste[i].ns = 0;
	for (int i = 1; i <= g.n; i++, pos++) {
		if (pos >= lignes.size()) { cerr << "ERREUR : fichier tronque (sommets)" << endl; return false; }
		const vector<string>& t = lignes[pos];
		int id = atoi(t[0].c_str());
		int ns = atoi(t[1].c_str());
		if (id < 1 || id > g.n || ns > nbmax_succ || (int)t.size() < 2 + ns) {
			cerr << "ERREUR : ligne sommet invalide (id=" << id << ", ns=" << ns << ")" << endl;
			return false;
		}
		g.liste[id].ns = ns;
		for (int k = 1; k <= ns; k++) {
			g.liste[id].succ[k] = atoi(t[1 + k].c_str());
			for (int c = 0; c < nb_crit; c++) g.liste[id].distance[k][c] = -1; // pas encore lu
			g.liste[id].manquant[k] = false;
		}
	}

	// --- arcs
	if (pos >= lignes.size()) { cerr << "ERREUR : nombre d'arcs absent" << endl; return false; }
	int m = atoi(lignes[pos][0].c_str());
	pos++;
	int nb_trous = 0;
	for (int a = 0; a < m; a++, pos++) {
		if (pos >= lignes.size()) { cerr << "ERREUR : fichier tronque (arcs)" << endl; return false; }
		const vector<string>& t = lignes[pos];
		if (t.size() < 4) { cerr << "ERREUR : arc " << a + 1 << " incomplet" << endl; return false; }
		int i = atoi(t[1].c_str());
		int j = atoi(t[2].c_str());
		if (i < 1 || i > g.n || j < 1 || j > g.n) { cerr << "ERREUR : arc " << t[0] << " hors bornes" << endl; return false; }

		// retrouver j dans la liste des successeurs de i (sinon on l'ajoute)
		int k = 0;
		for (int x = 1; x <= g.liste[i].ns; x++) if (g.liste[i].succ[x] == j) { k = x; break; }
		if (k == 0) {
			if (g.liste[i].ns >= nbmax_succ) { cerr << "ERREUR : trop de successeurs pour " << i << endl; return false; }
			k = ++g.liste[i].ns;
			g.liste[i].succ[k] = j;
		}
		g.liste[i].manquant[k] = false;
		for (int c = 0; c < nb_crit; c++) {
			if (3 + c < (int)t.size() && est_nombre(t[3 + c], v)) g.liste[i].distance[k][c] = v;
			else { g.liste[i].distance[k][c] = -1; g.liste[i].manquant[k] = true; }
		}
		if (g.liste[i].manquant[k]) nb_trous++;
	}

	// --- estimation des valeurs manquantes :
	//     critere c  ~  critere1 * (moyenne de critere_c / critere1 sur les arcs complets)
	double ratio[nb_crit] = { 1, 0, 0 };
	int nb_ok[nb_crit] = { 0 };
	for (int i = 1; i <= g.n; i++)
		for (int k = 1; k <= g.liste[i].ns; k++)
			for (int c = 1; c < nb_crit; c++)
				if (g.liste[i].distance[k][c] >= 0 && g.liste[i].distance[k][0] > 0) {
					ratio[c] += g.liste[i].distance[k][c] / g.liste[i].distance[k][0];
					nb_ok[c]++;
				}
	for (int c = 1; c < nb_crit; c++) ratio[c] = nb_ok[c] ? ratio[c] / nb_ok[c] : 1.0;

	int nb_sans_cout = 0;
	for (int i = 1; i <= g.n; i++)
		for (int k = 1; k <= g.liste[i].ns; k++) {
			if (g.liste[i].distance[k][0] < 0) { nb_sans_cout++; g.liste[i].distance[k][0] = c_infini; }
			for (int c = 1; c < nb_crit; c++)
				if (g.liste[i].distance[k][c] < 0) {
					g.liste[i].distance[k][c] = g.liste[i].distance[k][0] * ratio[c];
					g.liste[i].manquant[k] = true;
				}
		}

	cout << "Fichier '" << nom_fichier << "' lu : " << g.n << " sommets, " << m << " arcs." << endl;
	if (nb_trous > 0)
		cout << "  ATTENTION : " << nb_trous << " arcs avaient des valeurs manquantes (\"Duree\"/\"Cout\")"
		     << " -> estimees (ratio moyen crit2/crit1=" << ratio[1] << ", crit3/crit1=" << ratio[2] << ")." << endl;
	if (nb_sans_cout > 0)
		cout << "  ATTENTION : " << nb_sans_cout << " arcs de la liste d'adjacence n'ont aucun cout (consideres infranchissables)." << endl;
	return true;
}

void afficher_graphe_resume(const t_graphe& g)
{
	int nb_arcs = 0, deg_max = 0;
	for (int i = 1; i <= g.n; i++) { nb_arcs += g.liste[i].ns; deg_max = max(deg_max, g.liste[i].ns); }
	cout << "Graphe : n=" << g.n << ", arcs=" << nb_arcs << ", degre sortant max=" << deg_max << endl;
}

// ===========================================================================
//  Mono-critere
// ===========================================================================

static void init_solution(t_solution& s, const t_graphe& g, int depart, int destination, int critere)
{
	s.depart = depart;
	s.destination = destination;
	s.critere = critere;
	for (int i = 0; i <= g.n; i++) { s.date[i] = c_infini; s.pere[i] = 0; }
	s.date[depart] = 0;
}

// Dijkstra (version O(n^2) comme dans le code d'origine, corrigee)
t_solution plus_court_chemin(const t_graphe& g, int depart, int destination, int critere)
{
	t_solution s;
	init_solution(s, g, depart, destination, critere);

	vector<int> dejavu(g.n + 1, 0);
	for (int iter = 1; iter <= g.n; iter++)
	{
		// 1. sommet non traite de plus petite marque
		int j = -1;
		double val_min = c_infini;
		for (int k = 1; k <= g.n; k++)
			if (dejavu[k] == 0 && s.date[k] < val_min) { val_min = s.date[k]; j = k; }
		if (j == -1) break;          // plus rien d'atteignable (bug d'origine : j non initialise)
		dejavu[j] = 1;

		// 2. propager les marques
		for (int k = 1; k <= g.liste[j].ns; k++) {
			int su = g.liste[j].succ[k];
			double d = s.date[j] + g.liste[j].distance[k][critere];
			if (d < s.date[su]) { s.date[su] = d; s.pere[su] = j; }
		}
	}
	return s;
}

// Bellman (Bellman-Ford) : sert a verifier Dijkstra
t_solution bellmann(const t_graphe& g, int depart, int destination, int critere)
{
	t_solution s;
	init_solution(s, g, depart, destination, critere);

	int stop = 0, tours = 0;
	while (stop == 0 && tours < g.n)      // bug d'origine : j < n oubliait le dernier sommet
	{
		stop = 1;
		tours++;
		for (int j = 1; j <= g.n; j++) {
			if (s.date[j] >= c_infini) continue;
			for (int k = 1; k <= g.liste[j].ns; k++) {
				int su = g.liste[j].succ[k];
				double d = s.date[j] + g.liste[j].distance[k][critere];
				if (d < s.date[su]) { s.date[su] = d; s.pere[su] = j; stop = 0; }
			}
		}
	}
	return s;
}

vector<int> chemin(const t_solution& s)
{
	vector<int> ch;
	if (s.date[s.destination] >= c_infini) return ch;
	int x = s.destination;
	while (x != 0) {
		ch.push_back(x);
		if (x == s.depart) break;
		x = s.pere[x];
	}
	reverse(ch.begin(), ch.end());
	return ch;
}

void couts_chemin(const t_graphe& g, const vector<int>& ch, double res[nb_crit])
{
	for (int c = 0; c < nb_crit; c++) res[c] = 0;
	for (size_t p = 0; p + 1 < ch.size(); p++) {
		int i = ch[p], j = ch[p + 1];
		for (int k = 1; k <= g.liste[i].ns; k++)
			if (g.liste[i].succ[k] == j) {
				for (int c = 0; c < nb_crit; c++) res[c] += g.liste[i].distance[k][c];
				break;
			}
	}
}

void afficher_chemin(const vector<int>& ch)
{
	if (ch.empty()) { cout << "(aucun chemin)"; return; }
	for (size_t p = 0; p < ch.size(); p++) cout << (p ? "-" : "") << ch[p];
}

// ===========================================================================
//  Multi-objectif : algorithme de labels (label-correcting) avec dominance
// ===========================================================================

bool domine(const double a[nb_crit], const double b[nb_crit])
{
	// a domine (faiblement) b : a <= b sur tous les criteres
	const double eps = 1e-9;
	for (int c = 0; c < nb_crit; c++) if (a[c] > b[c] + eps) return false;
	return true;
}

// score normalise : somme des c_k / (plus court chemin mono-critere k vers ce sommet)
static double score(const t_label& L, const vector<vector<double> >& ref)
{
	double s = 0;
	for (int c = 0; c < nb_crit; c++) {
		double r = ref[c][L.sommet];
		s += (r > 1e-12) ? L.c[c] / r : L.c[c];
	}
	return s;
}

struct t_cmp_lexico {
	const vector<t_label>* labels;
	bool operator()(int a, int b) const {
		const t_label& A = (*labels)[a];
		const t_label& B = (*labels)[b];
		for (int c = 0; c < nb_crit; c++) {
			if (A.c[c] != B.c[c]) return A.c[c] > B.c[c]; // min-heap
		}
		return a > b;
	}
};

t_resultat_mo multi_objectif(const t_graphe& g, int depart, int destination, const t_param_mo& p)
{
	auto t0 = chrono::steady_clock::now();
	t_resultat_mo r;
	r.nb_labels_crees = 0;
	r.max_labels_sommet = 0;

	// references pour normaliser (plus courts chemins mono-critere)
	vector<vector<double> > ref(nb_crit, vector<double>(g.n + 1));
	for (int c = 0; c < nb_crit; c++) {
		t_solution s = plus_court_chemin(g, depart, destination, c);
		for (int i = 1; i <= g.n; i++) ref[c][i] = s.date[i];
	}

	vector<vector<int> > actifs(g.n + 1);   // labels non domines sur chaque sommet

	// file de traitement selon l'ordre choisi
	deque<int> file;
	t_cmp_lexico cmp; cmp.labels = &r.labels;
	priority_queue<int, vector<int>, t_cmp_lexico> tas(cmp);

	auto pousser = [&](int id) {
		if (p.ordre == ORDRE_LEXICO) tas.push(id); else file.push_back(id);
	};
	auto vide = [&]() { return p.ordre == ORDRE_LEXICO ? tas.empty() : file.empty(); };
	auto extraire = [&]() {
		int id;
		if (p.ordre == ORDRE_LEXICO) { id = tas.top(); tas.pop(); }
		else if (p.ordre == ORDRE_LIFO) { id = file.back(); file.pop_back(); }
		else { id = file.front(); file.pop_front(); }
		return id;
	};

	// insertion d'un label candidat sur un sommet ; renvoie vrai s'il est conserve
	auto inserer = [&](t_label L) -> bool {
		int v = L.sommet;
		// borne : inutile de garder un label domine par une solution deja trouvee a la destination
		if (v != destination)
			for (int id : actifs[destination]) if (domine(r.labels[id].c, L.c)) return false;
		// dominance locale
		for (int id : actifs[v]) if (domine(r.labels[id].c, L.c)) return false;
		vector<int> garde;
		for (int id : actifs[v]) {
			if (domine(L.c, r.labels[id].c)) r.labels[id].actif = false;
			else garde.push_back(id);
		}
		actifs[v].swap(garde);

		// limitation du nombre de labels par sommet
		if (p.max_labels > 0 && (int)actifs[v].size() >= p.max_labels) {
			if (p.regle == REGLE_REFUSER) return false;

			// candidats : labels existants + nouveau (indice -1)
			vector<int> cand = actifs[v];
			cand.push_back(-1);
			auto lab = [&](int id) -> const t_label& { return id == -1 ? L : r.labels[id]; };

			vector<bool> protege(cand.size(), false);
			if (p.regle == REGLE_DIVERSITE && p.max_labels >= nb_crit) {
				for (int c = 0; c < nb_crit; c++) {
					size_t best = 0;
					for (size_t x = 1; x < cand.size(); x++) if (lab(cand[x]).c[c] < lab(cand[best]).c[c]) best = x;
					protege[best] = true;
				}
			}
			size_t pire = cand.size();
			double s_pire = -1;
			for (size_t x = 0; x < cand.size(); x++) {
				if (protege[x]) continue;
				double s = score(lab(cand[x]), ref);
				if (s > s_pire) { s_pire = s; pire = x; }
			}
			if (pire == cand.size()) return false;
			if (cand[pire] == -1) return false;          // le nouveau est le pire : refuse
			r.labels[cand[pire]].actif = false;          // on retire le pire existant
			actifs[v].erase(find(actifs[v].begin(), actifs[v].end(), cand[pire]));
		}

		L.actif = true;
		r.labels.push_back(L);
		int id = (int)r.labels.size() - 1;
		actifs[v].push_back(id);
		r.nb_labels_crees++;
		r.max_labels_sommet = max(r.max_labels_sommet, (int)actifs[v].size());
		if (v != destination) pousser(id);   // on ne prolonge pas depuis la destination
		return true;
	};

	t_label racine;
	for (int c = 0; c < nb_crit; c++) racine.c[c] = 0;
	racine.sommet = depart; racine.pere = -1; racine.actif = true;
	inserer(racine);

	while (!vide()) {
		int id = extraire();
		if (!r.labels[id].actif) continue;
		t_label cur = r.labels[id];            // copie : r.labels peut etre realloue
		int j = cur.sommet;
		for (int k = 1; k <= g.liste[j].ns; k++) {
			int su = g.liste[j].succ[k];
			if (g.liste[j].distance[k][0] >= c_infini) continue;
			t_label L;
			for (int c = 0; c < nb_crit; c++) L.c[c] = cur.c[c] + g.liste[j].distance[k][c];
			L.sommet = su; L.pere = id; L.actif = true;
			inserer(L);
		}
	}

	r.front = actifs[destination];
	sort(r.front.begin(), r.front.end(), [&](int a, int b) {
		for (int c = 0; c < nb_crit; c++) if (r.labels[a].c[c] != r.labels[b].c[c]) return r.labels[a].c[c] < r.labels[b].c[c];
		return a < b;
	});
	r.temps_ms = chrono::duration<double, milli>(chrono::steady_clock::now() - t0).count();
	return r;
}

vector<int> chemin_label(const t_resultat_mo& r, int id_label)
{
	vector<int> ch;
	for (int id = id_label; id != -1; id = r.labels[id].pere) ch.push_back(r.labels[id].sommet);
	reverse(ch.begin(), ch.end());
	return ch;
}

void afficher_front(const t_resultat_mo& r, bool avec_chemins)
{
	cout << "  Front de Pareto : " << r.front.size() << " solution(s)" << endl;
	cout << fixed << setprecision(2);
	int num = 1;
	for (int id : r.front) {
		cout << "   #" << setw(3) << num++ << "  (";
		for (int c = 0; c < nb_crit; c++) cout << (c ? " ; " : "") << setw(9) << r.labels[id].c[c];
		cout << ")";
		if (avec_chemins) { cout << "  "; afficher_chemin(chemin_label(r, id)); }
		cout << endl;
	}
	cout.unsetf(ios::floatfield);
	cout << setprecision(6);
}

// ===========================================================================
//  Variation aleatoire +/- pct sur toutes les valeurs des arcs
// ===========================================================================
void perturber(const t_graphe& origine, t_graphe& resultat, double pct, unsigned int graine)
{
	mt19937 gen(graine);
	uniform_real_distribution<double> U(1.0 - pct, 1.0 + pct);
	resultat = origine;
	for (int i = 1; i <= resultat.n; i++)
		for (int k = 1; k <= resultat.liste[i].ns; k++)
			for (int c = 0; c < nb_crit; c++)
				if (resultat.liste[i].distance[k][c] < c_infini)
					resultat.liste[i].distance[k][c] *= U(gen);
}
