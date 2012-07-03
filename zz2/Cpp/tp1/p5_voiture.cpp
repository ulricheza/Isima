/**
 * \file p5_voiture.cpp
 * \brief fichier de declaration des methodes de la classe Voiture
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mercredi 6 octobre 2010
 */

#include "p5_voiture.h"

int Voiture::_nombre_voiture = 0;
float Voiture::_pollution = 0.0;

/**
 * \brief constructeur de la classe voiture
 */

Voiture::Voiture(string marque,string couleur,string typemot, int puissance, int regime_max,
                 float conso_urb, float conso_extraurb, float cap_reservoir, float emission):
                 _marque(marque),_couleur(couleur),_typemot(typemot),_puissance(puissance),
                 _regime_max(regime_max),_conso_urbaine(conso_urb),_conso_extraurbaine(conso_extraurb),
                 _capacite_reservoir(cap_reservoir),_emissionCO2(emission),_reservoir(0.0),_kilometrage(0.0)
{
   _nombre_voiture ++;
}

/**
 * \fn void Voiture::faire_plein()
 * \brief cette fonction simule le passage a la pompe d'une voiture
 *
 */

void Voiture::faire_plein()
{
    _reservoir = _capacite_reservoir;
}

/**
 * \fn void Voiture::rouler(float distance,string type_parcours)
 * \brief simule le fonctionnement d'une voiture
 * \param distance reel indiquant la distance a parcourir
 * \param type_parcours indique le tye de parcours a effectuer (campagne,autoroute,ville)
 *
 */

void Voiture::rouler(float distance,string type_parcours)
{
   float conso = -1.0;
   float carburant_conso;
   
   if(type_parcours == "ville")
     conso = _conso_urbaine;
   else
      if(type_parcours == "autoroute" || type_parcours == "campagne")
         conso = _conso_extraurbaine;
   if(conso > 0.0)
   {
      carburant_conso = distance * conso / 100.0;
      if(carburant_conso > _reservoir)
      {
         distance = _reservoir/conso * 100.0;
         std::cout << "votre voiture est tombe en panne d'essence apres " << distance << " Km parcouru" << std::endl;
         _reservoir = 0.0;
      }
      else
      {
         std::cout << "votre voiture a ressi le parcours de distance: " << distance << "Km" << std::endl;
         _reservoir -= carburant_conso;
      }
      _kilometrage += distance;
      _pollution += (distance*_emissionCO2);
   }
   else
      std::cout << "mauvais type de route " << std::endl;
}
         
      
    
      