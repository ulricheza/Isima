#include "ObjetGraphique.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/* Constructeur d'ObjetGraphique */
ObjetGraphique * MetaObjetGraphique_init( ObjetGraphique * this, int x, int y )
{
    #ifdef TEST
    printf( "  --> appel de ObjetGraphique::ObjetGraphique\n" );
    #endif

    /* Partie "generee" */
    assert( this );

    this->maClasse = & LeMetaObjetGraphique;
    this->vptr     = this->maClasse->TMV;

    /* Partie utilisateur */
    this->x = x;
    this->y = y;

    ++LeMetaObjetGraphique.NbObjetsGraphiques;

    return this;
}

/* Fonction de dispatch pour le destructeur */
void Generique_reset( ObjetGraphique * this )
{
    typedef void ( * funcType )( ObjetGraphique * );

    ptrFonction funcPtr = this->vptr[ RESET ];

    ( ( funcType ) funcPtr ) ( this );
}

/* Destructeur d'ObjetGraphique */
void MetaObjetGraphique_reset( ObjetGraphique * this )
{
    #ifdef TEST
    printf( "  --> appel de ObjetGraphique::~ObjetGraphique\n" );
    #endif

    /* Partie "generee" */

    /*
      Il faut reinitialiser le vptr pour que les appels de methodes virtuelles
      fonctionnent dans le destructeur. (Comme il n'y a pas d'appel ici, on
      pourrait se passer de la reinitialisation.)
     */
    this->vptr = this->maClasse->TMV;

    /* Partie utilisateur */

    --LeMetaObjetGraphique.NbObjetsGraphiques;
}

/* Methodes non virtuelles */

void ObjetGraphique_setX( ObjetGraphique * this, int x )
{
    this->x = x;
}

int ObjetGraphique_getX( ObjetGraphique * this )
{
    return this->x;
}

void ObjetGraphique_setY( ObjetGraphique * this, int y )
{
    this->y = y;
}

int ObjetGraphique_getY( ObjetGraphique * this )
{
    return this->y;
}

/* Methodes virtuelles */

/* Fonction de dispatch pour getCentreX */
int Generique_getCentreX( ObjetGraphique * this )
{
    typedef int ( * funcType )( ObjetGraphique * );

    ptrFonction funcPtr = this->vptr[ GETCENTREX ];

    return ( ( funcType ) funcPtr ) ( this );
}

/* Implementation de getCentreX pour ObjetGraphique */
int ObjetGraphique_getCentreX( ObjetGraphique * this )
{
    return this->x;
}

/* Fonction de dispatch pour getCentreY */
int Generique_getCentreY( ObjetGraphique * this )
{
    typedef int ( * funcType )( ObjetGraphique * );

    ptrFonction funcPtr = this->vptr[ GETCENTREY ];

    return ( ( funcType ) funcPtr ) ( this );
}

/* Implementation de getCentreY pour ObjetGraphique */
int  ObjetGraphique_getCentreY( ObjetGraphique * this )
{
    return this->y;
}

/* Fonction de dispatch pour afficher */
void Generique_afficher( ObjetGraphique * this )
{
    typedef int ( * funcType )( ObjetGraphique * );

    ptrFonction funcPtr = this->vptr[ AFFICHER ];

    ( ( funcType ) funcPtr ) ( this );
}

/* Pas d'implementation de afficher pour ObjetGraphique (car virtuelle pure) */


/* Methodes statiques. */
int MetaObjetGraphique_GetNbObjetsGraphiques( void )
{
    return LeMetaObjetGraphique.NbObjetsGraphiques;
}


/* Fonction d'initialisation du meta-objetGraphique */
void initMetaObjetGraphique( void )
{
    struct MetaObjetGraphique_t * that = & LeMetaObjetGraphique;

    /* Initialisation des pointeurs de fonctions (methodes) */

    that->init   = & MetaObjetGraphique_init;
    that->reset  = & Generique_reset;

    that->setX = & ObjetGraphique_setX;
    that->getX = & ObjetGraphique_getX;
    that->setY = & ObjetGraphique_setY;
    that->getY = & ObjetGraphique_getY;

    that->getCentreX = & Generique_getCentreX;
    that->getCentreY = & Generique_getCentreY;
    that->afficher   = & Generique_afficher;

    /* Initialisation de la table des methodes virtuelles */

    that->TMV[ RESET ]      = ( ptrFonction ) & MetaObjetGraphique_reset;
    that->TMV[ GETCENTREX ] = ( ptrFonction ) & ObjetGraphique_getCentreX;
    that->TMV[ GETCENTREY ] = ( ptrFonction ) & ObjetGraphique_getCentreY;
    that->TMV[ AFFICHER ]   = 0; /* virtuelle pure, pas d'implementation */

    /* Initialisation des membres statiques */

    that->NbObjetsGraphiques = 0;

    that->GetNbObjetsGraphiques = & MetaObjetGraphique_GetNbObjetsGraphiques;
}


/* Ce qui suit permettrait d'initialiser le meta-objet sans avoir besoin
   d'appeler explicitement une fonction d'initialisation, mais pose
   probleme dans les classes filles : la valeur d'initialisation doit etre
   constante, ce qui n'est pas le cas lorsqu'on accede aux TMV des classes
   de base.
*/
/*
struct MetaObjetGraphique_t LeMetaObjetGraphique = {
    .init   = & MetaObjetGraphique_init,
    .reset  = & MetaObjetGraphique_reset,

    .setX = & ObjetGraphique_setX,
    .getX = & ObjetGraphique_getX,
    .setY = & ObjetGraphique_setY,
    .getY = & ObjetGraphique_getY,

    .getCentreX = & Generique_getCentreX,
    .getCentreY = & Generique_getCentreY,
    .effacer    = & Generique_effacer,
    .afficher   = & Generique_afficher,

    .TMV[ GETCENTREX ] = & ObjetGraphique_getCentreX,
    .TMV[ GETCENTREY ] = & ObjetGraphique_getCentreY,
    .TMV[ AFFICHER ]   = 0,

    .NbObjetsGraphiques = 0,

    .GetNbObjetsGraphiques = & MetaObjetGraphique_GetNbObjetsGraphiques
};
*/
