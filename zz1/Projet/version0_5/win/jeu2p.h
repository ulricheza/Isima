/**
 * \file jeu2p.c
 * \brief version 0.5 de navy battle en texte
 * \author Maxime Escourbiac 
 * \version 1.0
 * \date Jeudi 1 avril 2010
 *
 * 
 */

#ifndef __JEU2P_H__
#define __JEU2P_H__

#ifdef __WIN32__
   #define clear system("cls");
#else
   #define clear system("clear");
#endif

#include "network.h"

#define PORT 2012

int mode_solo();
int mode_local_client();
int mode_local_serv();
void affic_mat(int *, int );

#endif