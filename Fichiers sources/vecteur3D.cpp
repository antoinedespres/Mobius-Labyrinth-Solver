/**
 * @file vecteur3D.cpp
 * Projet DesprésGr109NougaretGr109
 * @author Antoine Després, Anicet Nougaret
 * @version 1 06/01/20
 * @brief Composant vecteur 3D
 * Structures de données et algorithmes
 */
 #include "vecteur3D.h"


/**
 *	@brief Création d'un vecteur à trois coordonnées
 *	@param [in] x Coordonnée d'abscisse
 *	@param [in] y Coordonnée d'ordonnée
 *	@param [in] z Numéro de face
 *	@return Le vecteur v
 */
Vec3 tuple(int x, int y, int z) {
	Vec3 v; v.x = x; v.y = y; v.z = z;
	return v;
}

/**
 *	@brief Passage d'un tableau de 3 entiers à un Vecteur 3
 *	@param [in] crd Tableau de 3 entiers
 *	@return Vecteur 3 issu de la conversion
 */
Vec3 from_list(const int crd[3]) {
	Vec3 nouv;
	nouv.x = crd[0];
	nouv.y = crd[1];
	nouv.z = crd[2];
	return nouv;
}

/**
 *	@brief Affichage (x,y,z) d'un Vecteur 3
 *	@param [in] Coordonnées d'une case
 */
void afficher(const Vec3& v) {
	std::cout << "(" << v.x << "," << v.y << "," << v.z+1 << ")";
}

/**
 *	@brief Test d'égalité entre deux Vecteurs 3 (ssi toutes coordonnées égales)
 *	@param [in] v1 Premier vecteur
 *	@param [in] v2 Second vecteur
 *	@return true si toutes les coordonnées sont égales, false sinon
 */
bool egal(const Vec3& v1, const Vec3& v2) {
	bool x_egal = v1.x == v2.x;
	bool y_egal = v1.y == v2.y;
	bool z_egal = v1.z == v2.z;
	return x_egal && y_egal && z_egal;
}
