/**
 * \file dijkstra.h
 * \brief Programme de plus court chemin selon l'algo de dijkstra
 * \author Maxime Escourbiac Jean Christophe Septier
 * \version 0.1
 * \date Mercredi 12 Octobre 2010
 *
 * Programme de plus court chemin selon l'algo de dijkstra en C++
 *
 */

#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#define GR_MAX 10000.0

#include <list>
#include "graphe.h"

using std::list;

/**
 *\struct dij
 *\brief structure utilise pour l'algo de dijkstra
 *
 */

struct dij
{
  sommet * som;
  float distance;
};

/**
 *\struct retour
 *\brief structure utilise pour retourner le resultat de l'algo de dijkstra
 *
 */
struct retour
{
  int label;
  int prec;
  float distance;
};

/**
 * \fn bool compare_distance(dij first, dij second);
 * \brief predicat de tri de liste
 * \param first 
 * \param second 
 * \return true si distance de first < distance de second
 *
 */

bool compare_distance(const dij & , const dij & );

/**
 * \fn retour * dijkstra(graphe_t * gr, int debut, int fin);
 * \brief algorithme de Dijkstra
 * \param gr graphe a etudier
 * \param debut sommet de depart
 * \param fin sommet d'arrive
 * \return liste de structure result pour effectuer les calculs necessaires
 *
 */

retour * dijkstra(graphe_t * , const int & , const int & );

#endif