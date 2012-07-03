/**
 * \file popt_paddock.h
 * \brief fichier d'en-tete de classe paddock
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mercredi 13 octobre 2010
 */


#ifndef __PADDOCK_MAX_H__
#define __PADDOCK_MAX_H__

#include "popt_f1.h"

class Paddock
{
   protected :
      F1 ** _parc;
      int _nombre_F1;

   public :
   Paddock(int nbre_voit);
   ~Paddock() {}
   int getNOMBRE_F1() {return _nombre_F1;}
   int placer_f1(F1 * voit);
   F1 * voir_f1(int id);
};


#endif