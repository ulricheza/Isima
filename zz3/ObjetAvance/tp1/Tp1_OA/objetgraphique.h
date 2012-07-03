/* 
 * File:   objetgraphique.h
 * Author: Maxime
 *
 * Created on 31 janvier 2012, 16:47
 */

#ifndef OBJETGRAPHIQUE_H
#define	OBJETGRAPHIQUE_H


typedef struct ObjetGraphique_t ObjetGraphique;

typedef struct metaOG_t {
    int _nbObjetGraphique;
    void (*setX)(ObjetGraphique *, int);
    void (*setY)(ObjetGraphique *, int);
    int (*getX)(ObjetGraphique *);
    int (*getY)(ObjetGraphique *);
    int (*getNBObjetGraphique) (void);
    ObjetGraphique * (*new)(int, int);
    void (*delete)(ObjetGraphique *);
    void (*init) (ObjetGraphique *, int, int);
} metaOG;

metaOG OGmeta;

struct ObjetGraphique_t {
    metaOG * _classe;
    int _x;
    int _y;
};

void initMetaOG(void);

#endif	/* OBJETGRAPHIQUE_H */

