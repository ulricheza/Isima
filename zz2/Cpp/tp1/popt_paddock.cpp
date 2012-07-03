/**
 * \file popt_paddock.cpp
 * \brief fichier de declaration des methodes de la classe paddock
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mercredi 13 octobre 2010
 */

#include "popt_paddock.h"

Paddock :: Paddock(int nbre_voit) : _nombre_F1(nbre_voit)
{
   _parc = new F1 * [nbre_voit];
   for(int i = 0;i<nbre_voit;i++)
      _parc[i] = NULL;
}

/**
 * \fn int Paddock :: placer_f1( F1 * voit)
 * \brief place une voiture dans un paddock
 * \param voit pointeur sur la voiture a placer
 * \return i si voiture non placer i = -1 sinon i la place de la f1 dans le tableau 
 */
int Paddock :: placer_f1( F1 * voit)
{
   int i=-1;
   while(++i < _nombre_F1 && !_parc[i]);
   if(i < _nombre_F1)
      _parc[i] = voit;
   else
      i = -1;
   return i;
}

/**
 * \fn F1 * Paddock :: voir_f1(int id)
 * \brief recupere les infos d'une voiture dans le paddock
 * \param id place de la f1 dans le paddock
 * \return result pointeur sur la f1 observe NULL si existe pas
 */

F1 * Paddock :: voir_f1(int id)
{
   F1 * result = NULL;
   if(id < _nombre_F1)
      result = _parc[id];
   return result;
}
