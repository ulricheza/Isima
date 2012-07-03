/**
 * \file agenda.h
 * \brief Programme de gestion d'agenda
 * \author Maxime Escourbiac
 * \version 0.1
 * \date Mardi 12 janvier 2010
 *
 * Programme qui gere un agenda
 *
 */
 
 #ifndef __MAX_AGENDA_H__
 #define __MAX_AGENDA_H__

 #include <stdio.h>
 #include <stdlib.h>
 #include "garbage.h"
 
 /**
  *\struct agenda_t
  *\brief nom et numero d'une personne
  *
  */
   
  typedef struct agenda
 {
    char nom[81];
    char num[13];
    struct agenda * suiv;
 }agenda_t;
 
 /*declaration des fonctions*/
 
 void adj(agenda_t **);
 
 void affic(agenda_t *);
  
 #endif
 
 
