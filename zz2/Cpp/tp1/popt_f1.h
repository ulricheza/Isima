/**
 * \file popt_f1.h
 * \brief fichier d'en-tete de classe F1
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mercredi 13 octobre 2010
 */


#ifndef __F1_MAX_H__
#define __F1_MAX_H__

#include <string>
#include "popt_circuit.h"

using std::string;

class F1
{
   protected:
      string _marque;
      string _couleur;
      int  _regime_max; // tr.min-1
      float  _reservoir; //en L
      float  _capacite_reservoir;//en L
      float  _consommation; //litre/H
      float  _kilometrage;
      int * _vitesse_regime; //une case = 100tr.min-1

   public:
      F1(string marque,string couleur, int reg_max,float capacite,int * vitesse_regime);
      ~F1() {}
      //getter
      string getMARQUE()                    {return _marque;}
      string getCOULEUR()                   {return _couleur;}
      int    getREGIME_MAX()                {return _regime_max;}
      float  getRESERVOIR()                 {return _reservoir;}
      float  getCAPACITE_RESERVOIR()        {return _capacite_reservoir;}
      float  getCONSOMMATION()              {return _consommation;}
      float  getKILOMETRAGE()               {return _kilometrage;}
      int    getVITESSE_REGIME(int regime);
      
      //setter
      void  setRESERVOIR(float res) {_reservoir = res;}
      //methodes
      void faire_plein() {_reservoir = _capacite_reservoir;}
};

#endif