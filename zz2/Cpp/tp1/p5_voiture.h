/**
 * \file p5_voiture.h
 * \brief fichier d'en tete de la classe voiture de la partie 5
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mercredi 6 octobre 2010
 */

#ifndef __VOITURE_H_MAX__
#define __VOITURE_H_MAX__

#include <iostream>
#include <string>


using std::string ;
class Voiture
{
   protected:
      string _marque; //on supposera que la marque contient - de 20 caracteres
      string _couleur;
      string _typemot; 
      int  _puissance; // cv
      int  _regime_max; // tr.min-1
      float  _conso_urbaine; // L.Km-1
      float  _conso_extraurbaine; // L.Km-1
      float  _reservoir; //en L
      float  _capacite_reservoir;//en L
      float  _emissionCO2; // g/km
      float  _kilometrage;
      static int _nombre_voiture;
      static float _pollution;
   public:
      Voiture(string marque,string couleur,string typemot, int puissance,int regime_max,
              float conso_urb, float conso_extraurb,float cap_reservoir, float emission);
      ~Voiture()  {_nombre_voiture--;}
      //getter
      string getMARQUE()             {return _marque;}
      string getCOULEUR()            {return _couleur;}
      string getTYPEMOT()            {return _typemot;}
      int    getPUISSANCE()          {return _puissance;}
      int    getREGIME_MAX()         {return _regime_max;}
      float  getCONSO_URBAINE()      {return _conso_urbaine;}
      float  getCONSO_EXTRAURBAINE() {return _conso_extraurbaine;}
      float  getRESERVOIR()          {return _reservoir;}
      float  getCAPACITE_RESERVOIR() {return _capacite_reservoir;}
      float  getEMISSIONCO2()        {return _emissionCO2;}
      float  getKILOMETRAGE()        {return _kilometrage;}
      static int getNOMBRE_VOITURE() {return _nombre_voiture;}
      static float getPOLLUTION()    {return _pollution;}
      //methodes
      void faire_plein();
      void rouler(float distance,string type_parcours);

};

#endif
