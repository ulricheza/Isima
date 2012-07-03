#ifndef OBJETGRAPHIQUE_H_INCLUDED
#define OBJETGRAPHIQUE_H_INCLUDED

#include "typedefs.h"

/* Forward declaration de la metaclasse */
struct MetaObjetGraphique_t;

/* Definition de la "classe" ObjetGraphique */
typedef struct
{
    ptrFonction * vptr;                     /* pointeur de TMV */
    struct MetaObjetGraphique_t * maClasse; /* pointeur vers le meta-objetGraphique */

    /* Donnees membres (attributs) */
    int x;
    int y;

} ObjetGraphique;


/* Enumeration pour l'indexation des methodes virtuelles */
enum ObjetGraphiqueMV { RESET, GETCENTREX, GETCENTREY, AFFICHER, OBJETGRAPHIQUE_NB_MV };


/* Definition de la metaclasse */
struct MetaObjetGraphique_t
{
    /* "Constructeur" (renvoie 'this' par commodite) */
    ObjetGraphique * ( * init )( ObjetGraphique *, int, int );

    /*
      "Destructeur". Comme on manipule les objets de facon polymorphique, il doit
      etre virtuel.
     */
    void ( * reset ) ( ObjetGraphique * );

    /* "Methodes" non virtuelles */
    void ( * setX )( ObjetGraphique *, int );
    int  ( * getX )( ObjetGraphique * );
    void ( * setY )( ObjetGraphique *, int );
    int  ( * getY )( ObjetGraphique * );

    /*
      "Methodes" virtuelles. Ces pointeurs pointeront sur des fonctions "generiques" qui
      servent juste a aller chercher la bonne fonction dans la TMV.
     */
    int  ( * getCentreX )( ObjetGraphique * );
    int  ( * getCentreY )( ObjetGraphique * );

    void ( * afficher )( ObjetGraphique * ); /* virtuelle pure */


    ptrFonction TMV[ OBJETGRAPHIQUE_NB_MV ]; /* Table des methodes virtuelles */


    /* Donnees membres statiques */
    int NbObjetsGraphiques;

    /* "Methodes" statiques */
    int ( * GetNbObjetsGraphiques )( void );
};


/* Instance de la metaclasse : meta-objetGraphique */
struct MetaObjetGraphique_t LeMetaObjetGraphique;

/* Fonction d'initialisation du meta-objetGraphique */
void initMetaObjetGraphique( void );

#endif /* OBJETGRAPHIQUE_H_INCLUDED */
