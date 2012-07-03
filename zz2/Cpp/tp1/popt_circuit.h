/**
 * \file popt_circuit.h
 * \brief fichier d'en-tete de classe circuit
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mercredi 13 octobre 2010
 */


#ifndef __CIRCUIT_MAX_H__
#define __CIRCUIT_MAX_H__

#include<string>

using std::string;

class Circuit
{
   protected:
      string _name;
      int _taille;
      int * _stat_circuit; //une case pour 100m
   public:
      Circuit(string name, int taille, int * stat);
      ~Circuit() {}
      //getter
      string getNAME()    {return _name;}
      int    getTAILLE()  {return _taille;}
      int    regime_max_distance(int distance);
};

#endif