/**
 * \file p5_parking.cpp
 * \brief fichier de declaration des methodes de la classe parking de la partie 5
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Dimanche 10 octobre 2010
 */

#include "p5_parking.h"


Parking :: Parking(int capacite):
         _capacite(capacite),_voiture_garee(0)
{
   park = (Voiture **)calloc(capacite,sizeof(Voiture *));
   if(!park)
   {
      std::cerr << "erreur alloc parking";
      exit(EXIT_FAILURE);
   }
}

/**
 * \fn int Parking::garer(Voiture * car)
 * \brief fonction qui effectue le parking d'une voiture
 * \param car pointeur sur la voiture a garer
 * \return result retourne l'emplacement de la voiture garee et -1 si on a pas pu la garer
 */

 int Parking::garer(Voiture * car)
{
   int result = -1,i=-1;
   if(_voiture_garee < _capacite)
   {
      while(park[++i]);
      park[i] = car;
      result = i; 
      _voiture_garee++;
   }
   return result;
}

/**
 * \fn Parking:sortir(Voiture * car)
 * \brief fonction qui effectue la sortie d'une voiture du parking
 * \param car pointeur sur la voiture a sortir
 * \return result retourne 1 si la voiture est sortie 0 sinon
 */

int Parking::sortir(Voiture * car)
{
   int i = 0,result = 0;
   while(i<_capacite && park[i] != car)
   {
     ++i;
   }
   if(i<_capacite)
   {
      result = 1;
      park[i] = NULL;
      _voiture_garee--;
   }
   return result;
}

/**
 * \fn Parking::observer(int id)
 * \brief fonction qui effectue l'observation d'une voiture dans le parking
 * \param id identifiant de parking de la voiture a observer
 * \return result le pointeur sur l'instance de voiture 
 */

Voiture * Parking::observer(int id)
{
   Voiture * result = NULL;
   if(id >= 0 && id < _capacite)
      result = park[id];
   return result;
}