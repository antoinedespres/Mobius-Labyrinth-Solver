/**
 * @file case.cpp
 * Projet Despr�sGr109NougaretGr109
 * @author Antoine Despr�s, Anicet Nougaret
 * @version 1 06/01/20
 * @brief Composant case
 * Structures de donn�es et algorithmes
 */

#include "case.h"

/**
 *	@brief Renvoie vrai ssi le type de case d'entr�e est valide.
 *	@param [in] tc Type de case � v�rifier
 *	@retun True si la case est valide, false sinon
 */
bool est_valide(const typeCase tc) {
	return tc == MUR || tc == CHEMIN || tc == DRAGON || tc == PLAN;
}

/**
 *	@brief Convertit une Case en cha�ne de caract�res
 *	@param [in] c Case � convertir
 *	@return Cha�ne de caract�res issue de la conversion
 */
char* string(const Case& c, bool mecontent) {
	char* str;
	str = new char[2];
	str[0] = (char) c.type;
	//if (c.visite) str[0] = 'V';
	if (c.dans_chemin || c.type == DRAGON) str[0] = 'C';
	if (mecontent && c.type != PLAN) str[0] = '#';
	if (mecontent && c.type == PLAN) str[0] = 'P';
	str[1] = '\0';
	return str;
}

/**
 *	@brief Convertit un char en Case
 *	@param [in] c Case � convertir
 *	@param [in] crd Coordonn�es 3D de la case
 *	@return Cha�ne de caract�res issue de la conversion
 *	@pre Le char d'entr�e correspond � un type de case valide
 */
Case initialiser(char c, Vec3 crd) {
	typeCase tc = (typeCase) c;
	assert(est_valide(tc));
	Case ca;
	ca.type = tc;
	ca.crd = crd;
	ca.ordre = 10;
	ca.visite = false;
	ca.dans_chemin = false;
	return ca;
}

/**
 *	@brief Affiche les coordonn�es d'une Case
 *	@param [in] c Case dont on souhaite afficher les coordonn�es
 */
void afficher_crd(const Case& c) {
	afficher(c.crd);
}