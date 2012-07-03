#ifndef CERCLE_H_INCLUDED
#define CERCLE_H_INCLUDED

#include "ObjetGraphique.h"
#include "typedefs.h"

/* Forward declaration de la metaclasse */
struct MetaCercle_t;

/* Definition de la "classe" Cercle */
typedef struct Cercle_t
{
    ObjetGraphique super;           /* "super-objet" : partie ObjetGraphique du Cercle */
    struct MetaCercle_t * maClasse; /* pointeur vers le meta-cercle */

    /* Donnees membres */
    int rayon;

} Cercle;


/* Enumeration pour l'indexation des methodes virtuelles.
   Le Cercle ne rajoute pas de methodes virtuelles.
 */
enum CercleMV { CERCLE_NB_MV = OBJETGRAPHIQUE_NB_MV };


/* Definition de la metaclasse */
struct MetaCercle_t
{
    struct MetaObjetGraphique_t * superClasse; /* pointeur vers la classe de base */

    /* "Constructeur" (renvoie 'this' par commodite) */
    Cercle * ( * init )( Cercle *, int, int, int );

    /* "Destructeur" */
    void ( * reset ) ( Cercle * );

    /* "Methodes" non virtuelles */
    void ( * setRayon )( Cercle *, int );
    int  ( * getRayon )( Cercle * );

    ptrFonction TMV[ CERCLE_NB_MV ]; /* Table des methodes virtuelles */


    /*
      "Methode" heritees. Ce n'est pas forcement bien terrible de les dupliquer
      alors qu'on peut y acceder en passant par 'superClasse', mais ca permet
      de rendre plus clair les appels de methodes :
        monCercle.maClasse->getX( &monCercle );
      au lieu de
        monCercle.maClasse->superClasse->getX( ( ObjetGraphique * ) &monCercle );
      D'autre part, cela m'a egalement permis d'ecrire la macro 'delete' de façon
      plus simple que si cette redondance n'existait pas.

      Par contre, ca force a modifier toutes les sous-classes quand on ajoute une methode dans une
      classe de base, et ca c'est franchement pas terrible niveau maintenabilite...
     */
    void ( * setX )      ( Cercle *, int );
    int  ( * getX )      ( Cercle * );
    void ( * setY )      ( Cercle *, int );
    int  ( * getY )      ( Cercle * );
    int  ( * getCentreX )( Cercle * );
    int  ( * getCentreY )( Cercle * );
    void ( * afficher )  ( Cercle * );

    int ( * GetNbObjetsGraphiques )( void ); /* statique */

} LeMetaCercle;


/* Fonction d'initialisation du meta-cercle */
void initMetaCercle( void );


#endif /* CERCLE_H_INCLUDED */
