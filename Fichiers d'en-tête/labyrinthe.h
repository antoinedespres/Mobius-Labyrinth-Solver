/**
 * @file labyrinthe.h
 * Projet DesprésGr109NougaretGr109
 * @author Antoine Després, Anicet Nougaret
 * @version 1 06/01/20
 * @brief Composant labyrinthe
 * Structures de données et algorithmes
 */

#include <fstream>
#include "pile.h"

enum { NBDEPL = 8, DIM = 3 };

const int DEPL[NBDEPL][DIM] = {
	{-1,0,0},{-1,1,0},{0,1,0},{1,1,0},{1,0,0},{1,-1,0},{0,-1,0},{-1,-1,0}
}; // Déplacements possibles pour le dragon

struct Laby {
	enum {NBFACE = 2}; // Nombre de faces du labyrinthe
	Tab2 faces[NBFACE]; // Tableaux 2D des faces du labyrinthe
	Vec3 crd_dragon; // Coordonnées de la case DRAGON dans le labyrinthe
};

/**
 *	@brief Lit un fichier .txt pour initialiser le labyrinthe
 *	@param [in] path Chemin du fichier .txt qui décrit le labyrinthe
 *	@param [out] laby Labyrinthe à initialiser
 */
void initialiser(char* path, Laby& laby);

/**
 *	@brief Affiche un labyrinthe
 *	@param [in] laby Labyrinthe à afficher
 *	@param [in] mecontent Affiche le mécontentement du dragon si true (false par défaut)
 */
void afficher(const Laby& laby, bool mecontent = false);

/**
 *	@brief Désalloue les tableaux représentant les faces d'un labyrinthe
 *	@param [out] laby Labyrinthe à détruire
 */
void detruire(Laby& laby);

/**
 *	@brief Trouver une case
 *	@param [in] crd Coordonnées d'une case
 *	@param [in] laby Le labyrinthe
 *	@return Pointeur sur la case
 */
Case* get_case(const Vec3& crd, Laby& laby);

/**
 *	@brief Lire une case
 *	@param [in] crd Coordonnées d'une case
 *	@param [in] laby Le labyrinthe
 *	@return ca La case
 */
Case read_case(const Vec3& crd, const Laby& laby);

/**
 *	@brief Test d'existence d'une case
 *	@param [in] crd Coordonnées d'une case
 *	@param [in] laby Le labyrinthe
 *	@return True si la case existe, false sinon
 */
bool est_case(const Vec3& crd, const Laby& laby);

/**
 *	@brief Translation vectorielle selon les contraintes d'un ruban de Moebius (inversions en Y aux bordures etc...)
 *	@param [in] depart Loordonnées de départ
 *	@param [in] translation Translation à réaliser
 *	@param [in] laby Le labyrinthe
 *	@return nouv Le nouveau vecteur issu de la translation
 *	@pre Le nombre de lignes d'une face est supérieur à nouv.y
 */
Vec3 translation_moebius(const Vec3& v1, const Vec3& v2, const Laby& laby);

/**
 *	@brief Vérifie si une case est à visiter ou non
 *	@param [in] depart Première case
 *	@param [in] arrivee Deuxième case
 *	@param [in] laby Le labyrinthe
 *	@return true ou false selon que la case soit à visiter ou non
 */
bool est_a_visiter(const Vec3& c1, const Vec3& c2, const Laby& laby);

/**
 *	@brief Vérifie si une case est connexe à une autre (si on peut passer de l'une à l'autre)
 *	@param [in] depart Première case
 *	@param [in] arrivee Deuxième case
 *	@param [in] laby Le labyrinthe
 *	@return true ou false selon que les deux cases soient connexes ou non
 */
bool est_connexe(const Vec3& c1, const Vec3& c2, const Laby& laby);
