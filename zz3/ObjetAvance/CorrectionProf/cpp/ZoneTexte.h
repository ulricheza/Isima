#ifndef ZONETEXTE_H_INCLUDED
#define ZONETEXTE_H_INCLUDED

#include "Rectangle.h"
#include "typedefs.h"

/* Forward declaration de la metaclasse */
struct MetaZoneTexte_t;

/* Enumeration pour l'orientation du texte */
enum OrientationTexte { GAUCHE_DROITE, HAUT_BAS, DROITE_GAUCHE, BAS_HAUT, ZONE_TEXTE_NB_ORIENTATIONS };

/* Definition de la "classe" ZoneTexte */
typedef struct ZoneTexte_t
{
    Rectangle super;                   /* "super-objet" : partie Rectangle de la ZoneTexte */
    struct MetaZoneTexte_t * maClasse; /* pointeur vers la meta-zoneTexte */

    /* Donnees membres */
    char * texte;
    enum OrientationTexte orientation;

} ZoneTexte;


/* Enumeration pour l'indexation des methodes virtuelles.
   La ZoneTexte n'ajoute pas de methodes virtuelles.
 */
enum ZoneTexteMV { ZONETEXTE_NB_MV = RECTANGLE_NB_MV };


/* Definition de la metaclasse */
struct MetaZoneTexte_t
{
    struct MetaRectangle_t * superClasse; /* pointeur vers la classe de base */

    /* "Constructeur" (renvoie 'this' par commodite) */
    ZoneTexte * ( * init )( ZoneTexte *, int, int, int, int, char * );

    /* "Destructeur" */
    void ( * reset  )( ZoneTexte * );

    /* "Methodes" non virtuelles */
    void   ( * setTexte )( ZoneTexte *, char * );
    char * ( * getTexte )( ZoneTexte * );


    ptrFonction TMV[ ZONETEXTE_NB_MV ]; /* Table des methodes virtuelles */


    /*
      "Methode" heritees. Ce n'est pas forcement bien terrible de les dupliquer
      alors qu'on peut y acceder en passant par 'superClasse', mais ca permet
      de rendre plus clair les appels de methodes :
        maZoneTexte.maClasse->afficher( &maZoneTexte );
        maZoneTexte.maClasse->getLargeur( &maZoneTexte );
      au lieu de
        maZoneTexte.maClasse->superClasse->superClasse->afficher( ( ObjetGraphique * ) &maZoneTexte );
        maZoneTexte.maClasse->superClasse->getLargeur( ( Rectangle * ) &maZoneTexte );
      D'autre part, cela m'a egalement permis d'ecrire la macro 'delete' de façon
      plus simple que si cette redondance n'existait pas.

      Par contre, ca force a modifier toutes les sous-classes quand on ajoute une methode dans une
      classe de base, et ca c'est franchement pas terrible niveau maintenabilite...
     */
    void ( * setX )      ( ZoneTexte *, int );
    int  ( * getX )      ( ZoneTexte * );
    void ( * setY )      ( ZoneTexte *, int );
    int  ( * getY )      ( ZoneTexte * );
    int  ( * getCentreX )( ZoneTexte * );
    int  ( * getCentreY )( ZoneTexte * );
    void ( * afficher )  ( ZoneTexte * );

    void ( * setLargeur )( ZoneTexte *, int );
    int  ( * getLargeur )( ZoneTexte * );
    void ( * setHauteur )( ZoneTexte *, int );
    int  ( * getHauteur )( ZoneTexte * );
    void ( * tourner )   ( ZoneTexte *, int );

    int ( * GetNbObjetsGraphiques )( void ); /* statique */

} LeMetaZoneTexte;


/* Fonction d'initialisation de la meta-zoneTexte */
void initMetaZoneTexte( void );


#endif /* ZONETEXTE_H_INCLUDED */
