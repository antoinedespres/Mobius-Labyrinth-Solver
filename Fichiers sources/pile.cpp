/**
 * @file pile.cpp
 * Projet Despr�sGr109NougaretGr109
 * @author Antoine Despr�s, Anicet Nougaret
 * @version 1 06/01/20
 * @brief Composant Pile
 * Structures de donn�es et algorithmes
 */

#include "pile.h"

/** 
 * @brief Initialiser une pile vide
 * la pile est allou�e en m�moire dynamique
 * @see detruire pour une d�sallocation en fin d'utilisation
 * @param [in] n La capacit� de la pile
 * @param [in] p Le pas d'extension de la pile
 * @param [out] pile La pile � initialiser
 * @pre n>0
 */
void initialiser(unsigned int n, unsigned int p, Pile& pile) {
	pile.pas = p;
	pile.nbEl = 0;
	pile.cap = n;
	pile.tab = new Vec3[n];
}

/**
 * @brief Empiler un item sur une pile
 * @param [in] it L'item � empiler
 * @param [in,out] pile La pile
 */
void empiler(const Vec3& it, Pile& pile) {
	if (pile.nbEl >= pile.cap) {
		Vec3* nouv_tab = new Vec3[pile.cap+pile.pas];
		for (unsigned int i = 0; i < pile.nbEl; ++i) {
			nouv_tab[i] = pile.tab[i];
		}
		delete [] pile.tab;
		pile.tab = nouv_tab;
		pile.cap += pile.pas;
	}
	pile.nbEl++;
	pile.tab[pile.nbEl - 1] = it;
}

/**
 * @brief D�piler l'item au sommet de pile
 * @param [in,out] pile La pile
 * @pre la pile n'est pas vide
 */
void depiler(Pile& pile) {
	assert(pile.nbEl > 0);
	pile.nbEl--;
}

/**
 * @brief Lire l'item au sommet de la pile
 * @param [in] pile La pile
 * @return la valeur de l'item au sommet de la pile
 * @pre la pile n'est pas vide
 */
Vec3 sommet(const Pile& pile) {
	assert(pile.nbEl > 0);
	return pile.tab[pile.nbEl - 1];
}

/**
 * @brief D�sallouer une pile
 * @see initialiser, la pile a d�j� �t� initialis�e
 * @param [out] pile La pile � d�sallouer
 */
void detruire(Pile& pile) {
	delete[] pile.tab;
	pile.tab = NULL;
	pile.cap = 0;
	pile.nbEl = 0;
	pile.pas = 0;
}

/**
 * @brief Test de pile vide
 * @param [in] pile La pile
 * @return true si p est vide, false sinon
 */
bool est_vide(const Pile& pile) {
	return pile.nbEl == 0;
}

/**
 *	@brief Affichage des coordonn�es du chemin selon la mise en forme pr�vue
 *	@param [in] pile La pile contenant les coordonn�es
 */
void afficher(const Pile& pile) {
	for (unsigned int i = pile.nbEl; i > 0; i--) {
		std::cout << "C";
		afficher(pile.tab[i-1]);
		std::cout << "->";
	}
}