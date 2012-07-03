/* 
 * File:   objetgraphique.h
 * Author: Maxime
 *
 * Created on 31 janvier 2012, 16:47
 */

#ifndef OBJETGRAPHIQUE_H
#define	OBJETGRAPHIQUE_H

#define OG_NBMETHODE 3

typedef struct ObjetGraphique_t ObjetGraphique;

enum OG_METHODE {
    AFFICHER,
    GET_CENTRE_X,
    GET_CENTRE_Y,
    TAILLE
};

typedef struct metaOG_t {
    int _nbObjetGraphique;

    //methodes classiques
    void (*setX)(ObjetGraphique *, int);
    void (*setY)(ObjetGraphique *, int);
    int (*getX)(ObjetGraphique *);
    int (*getY)(ObjetGraphique *);

    //Methode virtuelle
    void * tableMethodeVirtuelle[OG_NBMETHODE];
    int (*getCenterX)(ObjetGraphique *);
    int (*getCenterY)(ObjetGraphique *);
    void (*display) (ObjetGraphique * objet); //methode virtuelle pure.



    //Methode de classe
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
    void ** vtable;
};

void initMetaOG(void);

#endif	/* OBJETGRAPHIQUE_H */

