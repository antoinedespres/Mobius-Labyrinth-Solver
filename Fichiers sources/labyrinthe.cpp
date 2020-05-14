/**
 * @file labyrinthe.cpp
 * Projet DesprésGr109NougaretGr109
 * @author Antoine Després, Anicet Nougaret
 * @version 1 06/01/20
 * @brief Composant labyrinthe
 * Structures de données et algorithmes
 */

#include "labyrinthe.h"


/**
 *	@brief Lit un fichier .txt pour initialiser le labyrinthe
 *	@param [in] path Chemin du fichier .txt qui décrit le labyrinthe
 *	@param [out] laby Labyrinthe à initialiser
 */
void initialiser(char* path, Laby& laby) {
	std::ifstream labyFic;
	labyFic.open(path);

	int nbC; // nombre de colonnes
	labyFic >> nbC;
	int nbL; // nombre de lignes
	labyFic >> nbL;

	for (int f = 0; f < laby.NBFACE; f++) {
		initialiser(nbL, nbC, laby.faces[f]);

		for (int l = 0; l < nbL; l++) {
			char* ligne;
			ligne = new char[nbC];
			labyFic >> ligne;

			for (int c = 0; c < nbC; c++) {
				Case ca = initialiser(ligne[c], tuple(c, l, f));
				
				if (ca.type == DRAGON) laby.crd_dragon = ca.crd;

				write(ca, l, c, laby.faces[f]);
			}
		}
	}

	labyFic.close();
}

/**
 *	@brief Affiche un labyrinthe
 *	@param [in] laby Labyrinthe à afficher
 *	@param [in] mecontent Affiche le mécontentement du dragon si true (false par défaut)
 */
void afficher(const Laby& laby, bool mecontent) {
	int nbC = laby.faces[0].nbC;
	int nbL = laby.faces[0].nbL;

	std::cout << nbC << " " << nbL << "\n";

	for (int f = 0; f < laby.NBFACE; f++) {
		for (int l = 0; l < nbL; l++) {
			for (int c = 0; c < nbC; c++) {
				Case ca = read(laby.faces[f], l, c);
				std::cout << string(ca, mecontent);
			}
			std::cout << "\n";
		}
		std::cout << "\n";
	}
}

/**
 *	@brief Désalloue les tableaux représentant les faces d'un labyrinthe
 *	@param [out] laby Labyrinthe à détruire
 */
void detruire(Laby& laby) {
	for (int f = 0; f < laby.NBFACE; f++) {
		detruire(laby.faces[f]);
	}
}

/**
 *	@brief Trouver une case
 *	@param [in] crd Coordonnées d'une case
 *	@param [in] laby Le labyrinthe
 *	@return Pointeur sur la case
 */
Case* get_case(const Vec3& crd, Laby& laby) {
	assert(est_case(crd, laby));
	return get(laby.faces[crd.z], crd.y, crd.x);
}

/**
 *	@brief Lire une case
 *	@param [in] crd Coordonnées d'une case
 *	@param [in] laby Le labyrinthe
 *	@return ca la case
 */
Case read_case(const Vec3& crd, const Laby& laby) {
	assert(est_case(crd, laby));
	Case ca = read(laby.faces[crd.z], crd.y, crd.x);
	return ca;
}

/**
 *	@brief Test d'existence d'une case
 *	@param [in] crd Coordonnées d'une case
 *	@param [in] laby Le labyrinthe
 *	@return True si la case existe, false sinon
 */
bool est_case(const Vec3& crd, const Laby& laby) {
	bool z_valide = crd.z < Laby::NBFACE;
	if (!z_valide) return false;
	const Tab2& face = laby.faces[crd.z];
	bool y_valide = face.nbL > crd.y;
	bool x_valide = face.nbC > crd.x;
	return y_valide && x_valide;
}

/**
 *	@brief Translation vectorielle selon les contraintes d'un ruban de Moebius (inversions en Y aux bordures etc...)
 *	@param [in] depart Coordonnées de départ
 *	@param [in] Translation à réaliser
 *	@param [in] laby Le labyrinthe
 *	@return nouv Le nouveau vecteur issu de la translation
 *	@pre Le nombre de lignes d'une face est supérieur à nouv.y
 */
Vec3 translation_moebius(const Vec3& depart, const Vec3& translation, const Laby& laby) {
	Vec3 nouv;
	nouv.z = (depart.z + translation.z) % Laby::NBFACE;
	Tab2 face = laby.faces[nouv.z];

	nouv.x = depart.x + translation.x;

	if (nouv.x < 0 || face.nbC <= nouv.x) {
		nouv.y = ((face.nbL-1) - depart.y) - translation.y;
	}
	else {
		nouv.y = depart.y + translation.y;
	}

	while (nouv.x < 0) {
		nouv.z = Laby::NBFACE - (nouv.z + 1);
		face = laby.faces[nouv.z];
		nouv.x += face.nbC;
	}

	while (face.nbC <= nouv.x) {
		nouv.x -= face.nbC;
		nouv.z = (nouv.z + 1) % Laby::NBFACE;
		face = laby.faces[nouv.z];	
	}

	assert(face.nbL >= nouv.y);

	return nouv;
}

/**
 *	@brief Vérifie si une case est à visiter ou non
 *	@param [in] depart Première case
 *	@param [in] arrivee Deuxième case
 *	@param [in] laby Le labyrinthe
 *	@return true ou false selon que la case soit à visiter ou non
 */
bool est_a_visiter(const Vec3& depart, const Vec3& arrivee, const Laby& laby) {
	assert(est_case(depart, laby) && est_case(arrivee, laby));
	
	bool est_visitee;

	// vérifions si elle est visitée
	Case c_arrivee = read_case(arrivee, laby);
	est_visitee = c_arrivee.visite;

	return est_connexe(depart, arrivee, laby) && !est_visitee;
}

/**
 *	@brief Vérifie si une case est connexe à une autre (si on peut passer de l'une à l'autre)
 *	@param [in] depart Première case
 *	@param [in] arrivee Deuxième case
 *	@param [in] laby Le labyrinthe
 *	@return true ou false selon que les deux cases soient connexes ou non
 */
bool est_connexe(const Vec3& depart, const Vec3& arrivee, const Laby& laby) {
	assert(est_case(depart, laby) && est_case(arrivee, laby));

	bool est_acote = false;
	bool est_chemin;
	
	// vérifions si c'est un chemin
	Case c_arrivee = read_case(arrivee, laby);
	est_chemin = c_arrivee.type == CHEMIN || c_arrivee.type == PLAN;

	// vérifions si c'est à côté du départ
	for (int i = 0; i < NBDEPL; ++i) {
		Vec3 translation = from_list(DEPL[i]);
		Vec3 translate = translation_moebius(depart, translation, laby);

		if (egal(translate, arrivee)) est_acote = true;
	}

	return est_chemin && est_acote;
}
