/**
 * @file tableau2D.cpp
 * Projet Despr�sGr109NougaretGr109
 * @author Antoine Despr�s, Anicet Nougaret
 * @version 1 06/01/20
 * @brief Composant tableau � 2 dimensions
 * Structures de donn�es et algorithmes
 */

#include "tableau2D.h"

/**
 *	@brief Initialise un tableau 2D
 *	@param [in] nbL Nombre de lignes du tableau
 *	@param [in] nbC Nombre de colonnes du tableau
 *	@param [out] t Tableau 2D � initialiser
 */
void initialiser(int nbL, int nbC, Tab2& t) {
	assert(nbL >= 0 && nbC >= 0);
	t.nbC = nbC;
	t.nbL = nbL;

	t.mat = new Item * [nbL];
	t.used = new bool * [nbL];

	for (int l = 0; l < nbL; l++) {
		t.mat[l] = new Item [nbC];
		t.used[l] = new bool [nbC];

		for (int c = 0; c < nbC; c++) {
			t.used[l][c] = false;
		}
	}
}

/**
 *	@brief Remplir une case du tableau avec un Item
 *	@param [in] it Item � mettre dans la case
 *	@param [in] l N� de ligne de l'emplacement de la case � remplir
 *	@param [in] c N� de colonne de l'emplacement de la case � remplir
 *	@param [out] t Tableau 2D � �crire
 *	@pre N� de Ligne et de colonne positifs et compris dans le tableau
*/
void write(Item it, int l, int c, Tab2& t) {
	assert(l >= 0 && c >= 0);
	assert(l < t.nbL && c < t.nbC);
	t.mat[l][c] = it;
	t.used[l][c] = true;
}

/**
 *	@brief Obtenir l'Item stock� dans une case du tableau
 *	@param [in] t Tableau 2D � lire
 *	@param [in] l N� de ligne de l'emplacement de la case � lire
 *	@param [in] c N� de colonne de l'emplacement de la case � lire
 *	@return Item situ� dans la case sp�cifi�e
 *	@pre N� de Ligne et de colonne positifs et compris dans le tableau
 *	@pre Case sp�cifi�e non vide
 */
Item* get(Tab2& t, int l, int c) {
	assert(l >= 0 && c >= 0);
	assert(l < t.nbL && c < t.nbC);
	assert(t.used[l][c] == true);
	return &t.mat[l][c];
}

/**
 *	@brief Lit une case et retourne ses coordonn�es si elle a bien �t� lue
 *	@param [in] t Le tableau
 *	@param [in] l Num�ro de ligne de la case
 *	@param [in] c Num�ro de colonne de la case
 *	@return les coordonn�es de la case
 *	@pre N� de ligne et de colonne tous deux sup�rieurs � 0
 *	@pre la case a �t� marqu�e comme used
 */ 
const Item read(const Tab2& t, int l, int c) {
	assert(l >= 0 && c >= 0);
	assert(l < t.nbL && c < t.nbC);
	assert(t.used[l][c] == true);
	return t.mat[l][c];
}

/** 
 * @brief Affiche un tableau 2D et son contenu initialis�
 * @param [in] t Tableau 2D � afficher
 */
void afficher(const Tab2& t) {
	std::cout << "{\n";
	for (int l = 0; l < t.nbL; l++) {
		std::cout << "	{\n		";
		for (int c = 0; c < t.nbC; c++) {
			if (t.used[l][c]) std::cout << string(t.mat[l][c]);
			else std::cout << "?";

			if (c < t.nbC - 1) std::cout << ", ";
		}
		std::cout << "\n	}";
		if (l < t.nbL - 1) std::cout << ",\n\n";
	}
	std::cout << "\n}\n	";
}

/**
 *	@brief D�salloue et rend NULL un tableau 2D
 *	@param [in,out] t Tableau 2D � d�sallouer
 */
void detruire(Tab2& t) {
	for (int l = 0; l < t.nbL; l++) {
		delete [] t.mat[l];
		t.mat[l] = NULL; 
		delete [] t.used[l];
		t.used[l] = NULL;
	}

	delete[] t.mat;
	t.mat = NULL;
	delete[] t.used;
	t.used = NULL;
}
