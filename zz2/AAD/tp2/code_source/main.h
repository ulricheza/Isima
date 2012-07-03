/**
 * \file main.h
 * \brief fichier d'en-tete du main du tp2
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \version 1.0
 * \date Dimanche 7 novembre 2010
 */

#include <stdlib.h>
#include <stdio.h>
#include "instance.h"

/*
 * \struct chromosome
 * \brief structure utlisee pour gerer la population
 */
struct chromosome
{
  int * vect;
  float makespan;
};

/**
 * \fn chromosome * algo_memetique(instance * inst);
 * \brief fonction qui effectue l'ago memetique
 * \param inst instance sur laquelle on va effectuer les calculs
 */
chromosome * algo_memetique(instance * inst);

/**
 * \fn chromosome * algo_genetique(instance * inst);
 * \brief fonction qui effectue l'ago genetique
 * \param inst instance sur laquelle on va effectuer les calculs
 */
chromosome * algo_genetique(instance * inst);

/**
 * \fn bool compare_distance(chromosome * first, chromosome * second);
 * \brief predicat pour le tri de la population
 * \param first chromosome a comparer
 * \param second chromosome a comparer
 */
bool compare_distance(chromosome * first, chromosome * second);

/**
 * \fn bool compare_makespan(chromosome * first, chromosome * second);
 * \brief predicat pour le unique de la population
 * \param first chromosome a comparer
 * \param second chromosome a comparer
 */
bool compare_makespan(chromosome * first, chromosome * second);