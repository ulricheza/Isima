/**
 * \file jeu.h
 * \brief version 1.0 de navy battle en texte
 * \author Maxime Escourbiac 
 * \version 1.01
 * \date Jeudi 9 septembre 2010
 *
 * 
 */

#ifndef __JEU_H__
#define __JEU_H__


#include "network.h"
#include "graphisme.h"

#define PORT 2012

 /**
 *\fn int mode_solo(SDL_Surface * fenetre)
 *\brief fonction mode solo
 *\param fenetre pointeur sur l'ecran principal 
 *\return EXIT_SUCCESS 
 *
*/

int mode_solo(SDL_Surface *);

 /**
 *\fn int mode_local_serveur(SDL_Surface * fenetre)
 *\brief fonction mode solo
 *\param fenetre pointeur sur l'ecran principal 
 *\return EXIT_SUCCESS 
 *
*/
 
int mode_local_serveur(SDL_Surface *);

 /**
 *\fn int mode_local_client(SDL_Surface * fenetre)
 *\brief fonction mode solo
 *\param fenetre pointeur sur l'ecran principal 
 *\return EXIT_SUCCESS 
 *
*/
 
int mode_local_client(SDL_Surface *);

#endif
