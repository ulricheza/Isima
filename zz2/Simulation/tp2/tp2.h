/**
 * \file tp2.h
 * \brief Generation de nombres pseudo aleatoires suivant differentes ditributions
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \version 0.1
 * \date Jeudi 7 octobre 2010
 *
 * Tp2 de simulation
 *
 */


#ifndef __TP2_H_EJC__
#define __TP2_H_EJC__

#include <stdio.h>
#include "fonction.h"
#include <SDL/SDL.h>

/**
 * \fn void tracer_graphe(SDL_Surface * ,int * , int , int );
 * \brief fonction de tracer de graphe
 * \param ecran Pointeur sur la surface fenetre
 * \param tab tableau contenant les valeur a afficher
 * \param nb_intervalle nombre de colonnes du graphe
 * \param nb_tirage hauteur max du graphique
 */
void tracer_graphe(SDL_Surface * ,int * , int , int );

/**
 * \fn void attendre();
 * \brief fonction de gestion d'evenement 
 */
void attendre();
 
#endif
