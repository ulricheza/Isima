/**
 * \file popt_f1.cpp
 * \brief fichier de declaration des methodes de la classe F1
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mercredi 13 octobre 2010
 */

#include "popt_f1.h"

F1 :: F1(string marque,string couleur, int reg_max,float capacite,int * vitesse_regime):
        _marque(marque),_couleur(couleur),_regime_max(reg_max),_capacite_reservoir(capacite),
        _reservoir(capacite),_vitesse_regime(vitesse_regime)
{
}

/**
 * \fn int F1 :: getVITESSE_REGIME(int regime)
 * \brief donne la vitesse de la voiture a un regime donne
 * \param regime regime courant de la voiture
 * \return result la vitesse du vehicule  
 */

int F1 :: getVITESSE_REGIME(int regime)
{
   int result;
   if(regime<_regime_max)
      result =  _vitesse_regime[regime/100];
   else
      result =  _vitesse_regime[_regime_max/100];
   return result;
}