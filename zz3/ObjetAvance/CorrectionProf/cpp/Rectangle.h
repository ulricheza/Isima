#ifndef RECTANGLE_H_INCLUDED
#define RECTANGLE_H_INCLUDED

#include "ObjetGraphique.h"
#include "typedefs.h"

/* Forward declaration de la metaclasse */
struct MetaRectangle_t;

/* Definition de la "classe" Rectangle */
typedef struct Rectangle_t
{
    ObjetGraphique super;              /* "super-objet" : partie ObjetGraphique du Rectangle */
    struct MetaRectangle_t * maClasse; /* pointeur vers le meta-rectangle */

    /* Donnees membres */
    int largeur;
    int hauteur;

} Rectangle;


/* Enumeration pour l'indexation des methodes virtuelles.
   Le Rectangle rajoute une methode virtuelle "tourner" ; pour n'avoir qu'un
   seul vptr dans l'objet, on ajoute cette methode a la suite de la TMV
   existante.
 */
enum RectangleMV { TOURNER = OBJETGRAPHIQUE_NB_MV, RECTANGLE_NB_MV };


/* Definition de la metaclasse */
struct MetaRectangle_t
{
    struct MetaObjetGraphique_t * superClasse; /* pointeur vers la classe de base */

    /* "Constructeur" (renvoie 'this' par commodite) */
    Rectangle * ( * init )( Rectangle *, int, int, int, int );

    /* "Destructeur" */
    void ( * reset  )( Rectangle * );

    /* "Methodes" non virtuelles */
    void ( * setLargeur )( Rectangle *, int );
    int  ( * getLargeur )( Rectangle * );
    void ( * setHauteur )( Rectangle *, int );
    int  ( * getHauteur )( Rectangle * );

    /* "Methodes" virtuelles */
    void ( * tourner )( Rectangle *, int );


    ptrFonction TMV[ RECTANGLE_NB_MV ]; /* Table des methodes virtuelles */


    /*
      "Methode" heritees. Ce n'est pas forcement bien terrible de les dupliquer
      alors qu'on peut y acceder en passant par 'superClasse', mais ca permet
      de rendre plus clair les appels de methodes :
        monRectangle.maClasse->getX( &monRectangle );
      au lieu de
        monRectangle.maClasse->superClasse->getX( ( ObjetGraphique * ) &monRectangle );
      D'autre part, cela m'a egalement permis d'ecrire la macro 'delete' de façon
      plus simple que si cette redondance n'existait pas.

      Par contre, ca force a modifier toutes les sous-classes quand on ajoute une methode dans une
      classe de base, et ca c'est franchement pas terrible niveau maintenabilite...
     */
    void ( * setX )      ( Rectangle *, int );
    int  ( * getX )      ( Rectangle * );
    void ( * setY )      ( Rectangle *, int );
    int  ( * getY )      ( Rectangle * );
    int  ( * getCentreX )( Rectangle * );
    int  ( * getCentreY )( Rectangle * );
    void ( * afficher )  ( Rectangle * );

    int ( * GetNbObjetsGraphiques )( void ); /* statique */

} LeMetaRectangle;


/* Fonction d'initialisation du meta-rectangle */
void initMetaRectangle( void );


#endif /* RECTANGLE_H_INCLUDED */
