/**
 * \file garbage.h
 * \brief Programme de garbage collector utilise lors du partiel
 * \author Maxime Escourbiac
 * \version 0.1
 * \date Mardi 12 janvier 2010
 *
 * Programme qui gere dynamiquement la memoire
 *
 */

#ifndef __MAX_GARBAGE_H__
#define __MAX_GARBAGE_H__

#include <stdio.h>
#include <stdlib.h>

/*declaration de fonctions*/

void creerGC();

void gc();

void detruireGC();

void * allouer (unsigned int );

void * reallouer (void * ,unsigned int);

#endif 
