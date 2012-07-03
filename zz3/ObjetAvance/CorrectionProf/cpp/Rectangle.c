#include "Rectangle.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


/* Constructeur statique de Rectangle */
Rectangle * MetaRectangle_init( Rectangle * this, int x, int y, int largeur, int hauteur )
{
    /* Partie "generee" */
    assert(this);

    this->maClasse = & LeMetaRectangle;
    this->maClasse->superClasse->init( & this->super /* ou simplement this */, x, y );

    #ifdef TEST
    printf( "  --> appel de Rectangle::Rectangle\n" );
    #endif

    this->super.vptr = this->maClasse->TMV;
    /* * ( ( void *** ) this ) = this->maClasse->TMV; */

    /* Partie utilisateur */
    this->largeur = largeur;
    this->hauteur = hauteur;

    return this;
}

/* Methodes non virtuelles */

void Rectangle_setLargeur( Rectangle * this, int largeur )
{
    this->largeur = largeur;
}

int Rectangle_getLargeur( Rectangle * this )
{
    return this->largeur;
}

void Rectangle_setHauteur( Rectangle * this, int hauteur )
{
    this->hauteur = hauteur;
}

int Rectangle_getHauteur( Rectangle * this )
{
    return this->hauteur;
}

/* Methodes virtuelles */

/* Redefinition de getCentreX pour Rectangle */
int Rectangle_getCentreX( Rectangle * this )
{
    return this->super.x + this->largeur / 2;
}

/* Redefinition de getCentreY pour Rectangle */
int Rectangle_getCentreY( Rectangle * this )
{
    return this->super.y + this->hauteur / 2;
}

/* (Re)definition de afficher pour Rectangle */
void Rectangle_afficher( Rectangle * this )
{
    printf( "Rectangle : x=%d, y=%d, largeur=%d, hauteur=%d",
            this->super.x,
            this->super.y,
            this->largeur,
            this->hauteur );

    /*
      On aurait aussi pu reutiliser la methode 'afficher' de la classe de
      base (cf. ZoneTexte::tourner).
     */
}

/* Fonction de dispatch pour tourner */
void Generique_tourner( Rectangle * this, int rotation )
{
    typedef void ( * funcType )( Rectangle *, int );

    ptrFonction funcPtr = this->super.vptr[ TOURNER ];
    /*
       Comme le vptr est le premier membre de la structure, on peut aussi faire :
           void ** TMV = * ( ( void *** ) this );
           void * funcPtr = TMV[ TOURNER ];
       Cela permet d'eviter, surtout dans les sous-classes, la multiplication des
       "->super".
     */

    ( ( funcType ) funcPtr ) ( this, rotation );
}

/* Implementation de tourner pour Rectangle */
void Rectangle_tourner( Rectangle * this, int rotation )
{
    if ( rotation % 2 != 0 )
    {
        int tmp = this->largeur;
        this->largeur = this->hauteur;
        this->hauteur = tmp;
    }
}


/*
  Fonction d'initialisation du meta-rectangle.
  Preconditions : LeMetaObjetGraphique doit etre initialise (cf. initMetaObjetGraphique)
 */
void initMetaRectangle( void )
{
    struct MetaRectangle_t * that = & LeMetaRectangle;

    that->superClasse = & LeMetaObjetGraphique;

    /* Initialisation des pointeurs de fonctions (methodes) */

    that->init   = & MetaRectangle_init;
    that->reset  = ( void (*)( Rectangle * ) ) that->superClasse->reset;

    that->setLargeur = & Rectangle_setLargeur;
    that->getLargeur = & Rectangle_getLargeur;
    that->setHauteur = & Rectangle_setHauteur;
    that->getHauteur = & Rectangle_getHauteur;

    that->tourner = & Generique_tourner;

    /* Initialisation de la table des methodes virtuelles */

    /*
      Le Rectangle n'a pas de destructeur "propre", on peut appeler directement
      celui de la classe de base (ObjetGraphique en l'occurence).
     */
    that->TMV[ RESET ]      = that->superClasse->TMV[ RESET ];
    that->TMV[ GETCENTREX ] = ( ptrFonction ) & Rectangle_getCentreX;
    that->TMV[ GETCENTREY ] = ( ptrFonction ) & Rectangle_getCentreY;
    that->TMV[ AFFICHER ]   = ( ptrFonction ) & Rectangle_afficher;

    that->TMV[ TOURNER ]    = ( ptrFonction ) & Rectangle_tourner;


    /* Initialisation des methode heritees */

    that->setX        = ( void (*)( Rectangle *, int ) ) that->superClasse->setX;
    that->getX        = ( int  (*)( Rectangle * ) )      that->superClasse->getX;
    that->setY        = ( void (*)( Rectangle *, int ) ) that->superClasse->setY;
    that->getY        = ( int  (*)( Rectangle * ) )      that->superClasse->getY;
    that->getCentreX  = ( int  (*)( Rectangle * ) )      that->superClasse->getCentreX;
    that->getCentreY  = ( int  (*)( Rectangle * ) )      that->superClasse->getCentreY;
    that->afficher    = ( void (*)( Rectangle * ) )      that->superClasse->afficher;

    that->GetNbObjetsGraphiques = that->superClasse->GetNbObjetsGraphiques;
}
