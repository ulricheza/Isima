/**
 * \file pile.h 
 * \brief Programme de gestion de piles
 * \author Maxime ESCOURBIAC Sebastien SAINT_MARTIN
 * \version 1.0
 * \date Vendredi 19 mars 2010
 *
 * library de gestion de piles
 */

 #ifndef __PILE_H__
 #define __PILE_H__

 #include <stdio.h>
 #include <stdlib.h>

 #define type_t int

/**
*\struct pile_t
*\brief structure d'en-tete de pile
*
*/ 

typedef struct pile
{
   type_t * tableau;
   int rang;
   int taille_max;
}pile_t;

/**
 * \fn pile_t * init_pile(int taille)
 * \brief fonction d'initialisation d'une pile
 * \param taille entier indiquand la taille de la pile
 * \return new pointeur sur la pile cree
 *
 * algo de principe: 
 *    allocation de la structure
 *    si structure non null
 *       init rang = -1
 *       init taille_max = taille
 *       allocation du tableau d'entier
 *       si tableau null
 *          afficher erreur
 *       fsi
 *    sinon
 *       afficher erreur
 *
 */
 
 pile_t * init_pile(int );

/**
 * \fn int vide_pile(pile_t * lifo)
 * \brief teste si une pile est vide
 * \param lifo pile a tester
 * \return 1 si vide 0 sinon
 *
 * algo de principe:
 *    return(lifo->rang == -1)
*/

int vide_pile(pile_t * );

/**
 * \fn int empiler(pile_t * lifo,type_t valeur)
 * \brief empile une valeur dans une pile
 * \param lifo pile ou on va empiler la valeur
 * \param valeur valeur a empiler
 * \return realise booleen pour savoir si ca a empile
 *
 * algo de principe:
 *    si pile non pleine
 *       rajout de la valeur dans le tableau
 *       MAJ rang
 *       realise == VRAI
 *    fsi
*/     
 
int empiler(pile_t * ,type_t );

/**
 * \fn int depiler(pile_t * lifo,type_t * valeur)
 * \brief depile une valeur dans une pile
 * \param lifo pile ou on va depiler la valeur
 * \param valeur pointeur sur la valeur ou on va depiler
 * \return realise booleen pour savoir si ca a depile
 *
 * algo de principe:
 *    si pile non vide
 *       affection de la valeur a depiler dans valeur
 *       MAJ rang
 *       realise == VRAI
 *    fsi
*/    

int depiler(pile_t * ,type_t * );

/**
 * \fn int sommet_pile(pile_t * lifo,type_t * valeur)
 * \brief renvoie la valeur de sommet sans la supprimer
 * \param lifo pile ou on va chercher la valeur
 * \param valeur pointeur sur la valeur ou on va mettre la valeur du sommet    
 * \return realise booleen pour savoir si ca a rendu la valeur du sommet
 *
 * algo de principe:
 *    si pile non vide
 *       affection de la valeur a depiler dans valeur
 *       realise == VRAI
 *    fsi
*/   

int sommet_pile(pile_t * ,type_t * );

/**
 * \fn int pleine_pile(pile_t * lifo)
 * \brief teste si une pile est pleine
 * \param lifo pile a tester
 * \return 1 si pleine 0 sinon
 *
 * algo de principe:
 *    return(lifo->rang == (lifo->taille_max- 1))
*/

int pleine_pile(pile_t * );


/**
 * \fn void detruire_pile(pile_t * lifo)
 * \brief libere une pile ainsi que son contenu
 * \param lifo pile a detuire
 *
 * algo de principe:
 *    liberation du tableau d'entier
 *    liberation de la structure pile
 */
 
 void detruire_pile(pile_t *);


#endif
