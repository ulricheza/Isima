/**
 * \file jeu1p.h
 * \brief version 1 joueur de navy battle en texte
 * \author Maxime Escourbiac 
 * \version 1.0
 * \date Dimanche 7 mars 2010
 *
 * 
 */

#include "core.h"

#ifdef __WIN32__
   #define clear system("cls");
#else
   #define clear system("clear");
#endif


void affic_mat(int * ,int );
