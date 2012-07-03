/**
 * \file tp42.h
 * \brief Programme de tri par interclassement
 * \author Maxime ESCOURBIAC Sebastien SAINT_MARTIN
 * \version 1.0
 * \date Mardi 08 juin 2010
 *
 *  Programme qui effectue un tri par interclassement
 *
*/
 
#ifndef __TP42_H__
#define __TP42_H__

#include <stdio.h>
#include <stdlib.h>

/*macro qui determine le min d'une valeur */
#define min(a,b) (a<=b?a:b)

/**
 * \fn void affic_tab(int * tab,int N )
 * \brief fonction d'affichage de tableau
 * \param tab tableau a afficher
 * \param N nombre d'element dans le tableau
 */

void affic_tab(int * ,int );

/**
 * \fn interclass(int * t1, int * t2,int debl1,int finl1,int debl2, int finl2)
 * \brief fonction d'interclassement dans un tableau
 * \param t1 tableau de lecture
 * \param t2 tableau d'ecriture
 * \param debl1 rang du debut de la 1er sous liste
 * \param finl1 rang de fin de la 1er sous liste
 * \param debl2 rang du debut de la 2nd sous liste
 * \param finl2 rang de fin de la 2nd sous liste
 *
 * Algo de principe:
 *   j = debl2;
 *   pour chaque valeur de la 1er sous liste faire
 *      tant que non fin de la 2nd liste et valeur 1er liste > val 2nd liste faire
 *         ecriture element 2nd liste
 *         on passe a l'element suivant dans la seconde liste
 *      fait
 *   fait
 *      tant que non fin de 2nd liste faire
 *         ecrire element seconde liste
 *         on passe a l'element suivant dans la seconde liste
 *      fait
 */

void interclass(int *, int *,int ,int ,int , int );

/**
 * \fn int * tri(int * liste,int N)
 * \brief fonction de tri von neumann
 * \param liste liste a trier
 * \param N nombre d'element dans le tableau
 *
 * algo de principe:
 *   allocation listeT
 *   si listeT != NULL alors
 *      pour l de 1 a N-1 de pas l<<=1 faire
 *         pour m de 0 a N-1 de pas 2l faire
 *            interclasser les 2 sous-listes
 *         fait
 *         echanger les pointeurs
 *      fait
 *   fsi
 */

int * tri(int * ,int );

#endif
