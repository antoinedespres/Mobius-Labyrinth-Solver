/**
 * @file vecteur3D.h
 * Projet DesprésGr109NougaretGr109
 * @author Antoine Després, Anicet Nougaret
 * @version 1 06/01/20
 * @brief Composant vecteur 3D
 * Structures de données et algorithmes
 */

#include <iostream>
#include <cassert>

struct Vec3 {
	int x; // Coordonnée x du point (colonne)
	int y; // Coordonnée y du point (ligne)
	int z; // Coordonnée z du point (face)
};

/**
 *	@brief Création d'un vecteur à trois coordonnées
 *	@param [in] x Coordonnée d'abscisse
 *	@param [in] y Coordonnée d'ordonnée
 *	@param [in] z Numéro de face
 *	@return Le vecteur v
 */
Vec3 tuple(int x, int y, int z);

/**
 *	@brief Passage d'un tableau de 3 entiers à un Vecteur 3
 *	@param [in] crd Vableau de 3 entiers
 *	@return Vecteur 3 issu de la conversion
 */
Vec3 from_list(const int crd[3]);

/**
 *	@brief Affichage (x,y,z) d'un Vecteur 3
 *	@param [in] v Coordonnées d'une case
 */
void afficher(const Vec3& v);

/**
 *	@brief Test d'égalité entre deux Vecteurs 3 (ssi toutes coordonnées égales)
 *	@param [in] v1 Premier vecteur
 *	@param [in] v2 Second vecteur
 *	@return true si toutes les coordonnées sont égales, false sinon
 */
bool egal(const Vec3& v1, const Vec3& v2);
