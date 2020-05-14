/**
 * @file labyGame.cpp
 * Projet DesprésGr109NougaretGr109
 * @author Antoine Després, Anicet Nougaret
 * @version 1 06/01/20
 * @brief Composant LabyGame
 * Structures de données et algorithmes
 */

#include "labyGame.h"
#define PILE_CAP 10
#define PILE_PAS 1

/**
 *	@brief Met à jour la pile contenant les coordonnées du chemin du dragon
 *	@param [in,out] chemin Chemin déjà parcouru
 *	@param [in] nouv_crd Nouvelle coordonnée à empiler
 *	@param [in] laby Le labyrinthe
*/
void maj_chemin(Pile& chemin, Vec3& nouv_crd, Laby& laby) {
	while (!est_vide(chemin) && !est_connexe(nouv_crd, sommet(chemin), laby)) {
		Case* ca = get_case(sommet(chemin), laby);
		ca->dans_chemin = false;
		depiler(chemin);
	}
	Case* ca = get_case(nouv_crd, laby);
	ca->dans_chemin = true;
	empiler(nouv_crd, chemin);
}

/**
 *	@brief Parcours du labyrinthe par le dragon
 */
void MissionDragon() {
	Laby laby;
	Pile suivantes;
	Pile chemin;
	// lecture d'un fichier in.txt à placer dans le dossier du projet
	char path[] = ""; // chemin vers le fichier d'entrée, à adapter selon vos besoins
	bool plan_found = false;
	unsigned int k = 0;
	Vec3 courant = tuple(0, 0, 0);

	initialiser(path, laby);
	initialiser(PILE_CAP, PILE_PAS, suivantes);
	initialiser(PILE_CAP, PILE_PAS, chemin);
	empiler(laby.crd_dragon, suivantes);

	while (!plan_found && !est_vide(suivantes)) {
		courant = sommet(suivantes);
		Case* ca = get_case(courant, laby);
		depiler(suivantes);

		if (!ca->visite) {
			maj_chemin(chemin, courant, laby);
		}

		if (read_case(courant, laby).type != PLAN) {

			for (int i = 0; i < NBDEPL; ++i) {

				Vec3 translation = from_list(DEPL[i]);

				if (courant.y == 0 && translation.y == -1) {
					continue;
				}
				if (laby.faces[courant.z].nbL <= courant.y + translation.y) {
					continue;
				}

				Vec3 translate = translation_moebius(courant, translation, laby);

				if (est_a_visiter(courant, translate, laby)) {
					empiler(translate, suivantes);
				}

			}
			
			ca->visite = true;
			ca->ordre = k;
			++k;
		}
		else {
			plan_found = true;
		}
	}

	if (read_case(courant, laby).type == PLAN) {
		afficher(laby);
		afficher(chemin);
		std::cout << "C";
		afficher(laby.crd_dragon);
		std::cout << "->";
		std::cout << "\n";
	}
	else {
		afficher(laby, true);
	}
}
