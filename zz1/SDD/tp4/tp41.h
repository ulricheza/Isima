/**
 * \file tp41.h
 * \brief Programme de tri par tas
 * \author Maxime ESCOURBIAC Sebastien SAINT_MARTIN
 * \version 0.1
 * \date Vendredi 04 juin 2010
 *
 *  Programme qui effectue un tri par tas sur des arbres binaires parfait
 *
 */

#ifndef __TP41_H__
#define __TP41_H__

#include <stdio.h>
#include <stdlib.h>

/**
 * \fn void tripartas(int * tas,int N)
 * \brief fonction de tri par tas
 * \param tas pointeur sur la liste contenant le tas
 * \param N nombre d'element dans la liste
 *
 * Algo de principe
 *
 * creation du tas initial
 * Pour i de N-1 a 1 de pas -1 faire
 *    on inverse la premiere et la derniere valeur
 *    descendre_tas(tas,i,1);
 * fait
 */

void tripartas(int * ,int );

/**
 * \fn void construire_tas(int * tas, int N);
 * \brief fonction de construction d'un tas
 * \param tas pointeur sur la liste contenant le tas
 * \param N nombre d'element dans la liste
 *
 * Algo de principe
 *
 * Pour chaque noeud faire
 *    descendre_tas
 * fait
 */

void construire_tas(int * ,int );

/**
 * \fn void descendre_tas(int * tas, int N,int rang)
 * \brief fonction de descente d'une valeur du tas
 * \param tas pointeur sur la liste contenant le tas
 * \param N nombre d'element dans la liste
 * \param rang rang de l'element a descendre
 *
 * Algo de principe
 *
 * k = rang;
 * ech = vrai
 * pere = tas[rang -1];
 * tant que k =< N/2 et ech == vrai faire
 *    calcul de la place du 1er fils
 *    ech = faux
 *    si le noeud a deux fils alors
 *       si le fils droit > au fils gauche alors
 *          fils++
 *       fsi
 *    fsi
 *    si fils>pere alors
 *       on echange fils et pere
 *       ech = vrai
 *    fsi
 * fait
 * Methodologie:
 *   l'algo traite en cours travaille sur les rangs or en C les tableau commencent a 0
 *   donc sur le principe on travaille sur les rang et lorsque on veut acceder au valeur dans le tableau
 *   on utilise un indice - 1 pour acceder a la bonne valeur
 *   
 */

void descendre_tas(int * , int ,int );

/**
 * \fn void affic_tab(int * tab,int N )
 * \brief fonction d'affichage de tableau
 * \param tab tableau a afficher
 * \param N nombre d'element dans le tableau
 */

void affic_tab(int *,int );

#endif
