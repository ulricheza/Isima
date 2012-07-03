/**
 * \file popt_circuit.cpp
 * \brief fichier de declaration des methodes de la classe circuit
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mercredi 13 octobre 2010
 */

#include "popt_circuit.h"

Circuit :: Circuit(string name, int taille, int * stat):
                  _name(name),_taille(taille),_stat_circuit(stat)
{
}

/**
 * \fn int Circuit :: regime_max_distance(int distance)
 * \brief donne le regime_max d'une voiture sur une portion du circuit
 * \param distance distance ou se situe le vehicule
 * \return le regime maximal que peut atteindre le vehicule
 */

int Circuit :: regime_max_distance(int distance)
{
   /*on simule le regime max sur des portions de circuit de 100m*/
   return (_stat_circuit[(distance/100)%_taille]);
}