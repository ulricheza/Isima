/* 
 * File:   cercle.h
 * Author: Maxime
 *
 * Created on 31 janvier 2012, 17:09
 */

#ifndef CERCLE_H
#define	CERCLE_H

#include "objetgraphique.h"

typedef struct Cercle_t Cercle;

typedef struct metaCercle_t {
    metaOG * base;
    void (*setRayon)(Cercle *, int);
    int (*getRayon) (Cercle *);
    Cercle * (*new)(int, int,int);
    void (*delete)(Cercle *);
    void (*init) (Cercle *, int, int, int);
    
    void * tableMethodesVirtuelles[TAILLE];
    
} metaCercle;

metaCercle OGCercle;

struct Cercle_t {
    metaCercle * _classe;
    ObjetGraphique _super;
    int _rayon;
};

#endif	/* CERCLE_H */

