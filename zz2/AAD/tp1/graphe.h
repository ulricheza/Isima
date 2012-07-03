/**
 * \file graphe.h
 * \brief Programme de gestion de graphes
 * \author Maxime Escourbiac Jean Christophe Septier
 * \version 0.1
 * \date Vendredi 1er Octobre
 *
 * Programme de creation/gestion de graphes avec les listes d'adjacence
 *
 */

#ifndef __GRAPHE_JCM__
#define __GRAPHE_JCM__

#include <stdio.h>
#include <stdlib.h>

/*declaration des structures*/

 /**
  *\struct sommet_t
  *\brief structure decrivant un sommet 
  *
  */
typedef struct sommet
{
   int label;
   int first_arc;
   int nb_arcs;
   int x;
   int y;
}sommet_t;

/**
  *\struct arc_t
  *\brief structure decrivant un arc 
  *
  */
typedef struct arc
{
   int destination;
   float distance;
}arc_t;

 /**
  *\struct graphe_t
  *\brief structure gerant l'ensemble du graphe
  *
  */
typedef struct graphe
{
   int nb_sommets;
   int nb_arcs;
   struct sommet * sommets;
   struct arc * arcs;
}graphe_t;

/*declaration des fonctions*/

/**
 * \fn graphe_t * creation_arbre(char * nom_fic)
 * \brief fonction de lecture du probleme a partir d'un fichier
 * \param nom_fic nom du fichier ou est stocke le probleme
 * \return gr pointeur sur la structure du graphe cree
 *
 */

graphe_t * creation_arbre(char * );

#endif