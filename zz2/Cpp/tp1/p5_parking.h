/**
 * \file p5_parking.h
 * \brief fichier d'en tete de la classe parking de la partie 5
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Dimanche 10 octobre 2010
 */

#ifndef __PARKING_H_MAX__
#define __PARKING_H_MAX__

#include <iostream>
#include <string>
#include <stdlib.h>
#include "p5_voiture.h"


class Parking
{
  private:
     Voiture ** park;
     int _voiture_garee;
     int _capacite;
  public:
     Parking(int capacite);
     ~Parking() {free (park);}
     //getter
     int get_VOITURE_GAREE() {return _voiture_garee;}
     int get_CAPACITE()      {return _capacite;}
     //methodes
     int garer(Voiture * car);
     int sortir(Voiture * car);
     Voiture * observer(int id);
};

#endif