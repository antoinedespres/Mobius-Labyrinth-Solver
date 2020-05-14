/**
 * @file tableau2D.h
 * Projet DesprésGr109NougaretGr109
 * @author Antoine Després, Anicet Nougaret
 * @version 1 06/01/20
 * @brief Composant tableau à 2 dimensions
 * Structures de données et algorithmes
 */

#include "item.h"

struct Tab2 {
	Item** mat; // Matrice 2D contenant les éléments du tableau
	bool** used; // Matrice 2D indiquant quelles cases de la matrice d'éléments sont occuppées
	int nbC; // Nombre de colonnes de la matrice du tableau
	int nbL; // Nombre de ligne de la matrice du tableau
};

/**
 *	@brief Initialise un tableau 2D
 *	@param [in] nbL Nombre de lignes du tableau
 *	@param [in] nbC Nombre de colonnes du tableau
 *	@param [out] t Tableau 2D à initialiser
 */
void initialiser(int nbL, int nbC, Tab2& t);

/**
 *	@brief Remplir une case du tableau avec un Item
 *	@param [in] it Item à mettre dans la case
 *	@param [in] l N° de ligne de l'emplacement de la case à remplir
 *	@param [in] c N° de colonne de l'emplacement de la case à remplir
 *	@param [out] t Tableau 2D à écrire
 *	@pre N° de Ligne et de colonne positifs et compris dans le tableau
*/
void write(Item it, int l, int c, Tab2& t);

/**
 *	@brief Obtenir l'Item stocké dans une case du tableau
 *	@param [in] t Tableau 2D à lire
 *	@param [in] l N° de ligne de l'emplacement de la case à lire
 *	@param [in] c N° de colonne de l'emplacement de la case à lire
 *	@return Item situé dans la case spécifiée
 *	@pre N° de Ligne et de colonne positifs et compris dans le tableau
 *	@pre Case spécifiée non vide
 */
Item* get(Tab2& t, int l, int c);

/**
 *	@brief Lit une case et retourne ses coordonnées si elle a bien été lue
 *	@param [in] t Le tableau
 *	@param [in] l Numéro de ligne de la case
 *	@param [in] c Numéro de colonne de la case
 *	@return les coordonnées de la case
 *	@pre N° de ligne et de colonne tous deux supérieurs à 0
 *	@pre la case a été marquée comme used
 */ 
const Item read(const Tab2& t, int l, int c);

/** 
 * @brief Affiche un tableau 2D et son contenu initialisé
 * @param [in] t Tableau 2D à afficher
 */
void afficher(const Tab2& t);

/**
 *	@brief Désalloue et rend NULL un tableau 2D
 *	@param [in,out] t Tableau 2D à désallouer
 */
void detruire(Tab2& t);