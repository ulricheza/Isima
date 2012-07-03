#include "Cercle.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Constructeur de Cercle */
Cercle * MetaCercle_init( Cercle * this, int x, int y, int rayon )
{
    /* Partie "generee" */
    assert(this);

    this->maClasse = & LeMetaCercle;
    this->maClasse->superClasse->init( & this->super /* ou simplement this */, x, y);

    #ifdef TEST
    printf( "  --> appel de Cercle::Cercle\n" );
    #endif

    this->super.vptr = this->maClasse->TMV;
    /*
       Comme le vptr est le premier membre de la structure, on peut aussi faire :
           * ( ( void *** ) this ) = this->maClasse->VMT;
       Cela permet d'eviter, surtout dans les sous-classes, la multiplication des
       "->super".
     */

    /* Partie utilisateur */
    this->rayon = rayon;

    return this;
}

/* Methodes non virtuelles */

void Cercle_setRayon( Cercle * this, int rayon )
{
    this->rayon = rayon;
}

int Cercle_getRayon( Cercle * this )
{
    return this->rayon;
}

/* (Re)definition de la methode afficher pour Cercle */
void Cercle_afficher( Cercle * this )
{
    printf( "Cercle : x=%d, y=%d, rayon=%d",
            this->super.x,
            this->super.y,
            this->rayon );
}


/*
  Fonction d'initialisation du meta-cercle.
  Preconditions : LeMetaObjetGraphique doit etre initialise (cf. initMetaObjetGraphique)
 */
void initMetaCercle( void )
{
    struct MetaCercle_t * that = & LeMetaCercle;

    that->superClasse = & LeMetaObjetGraphique;

    /* Initialisation des pointeurs de fonctions (methodes) */

    that->init   = & MetaCercle_init;
    that->reset  = ( void (*)( Cercle * ) ) that->superClasse->reset;

    that->setRayon = & Cercle_setRayon;
    that->getRayon = & Cercle_getRayon;

    /* Initialisation de la table des methodes virtuelles */

    /*
      Le Cercle n'a pas de destructeur "propre", on peut appeler directement
      celui de la classe de base (ObjetGraphique en l'occurence).
     */
    that->TMV[ RESET ]      = ( ptrFonction ) that->superClasse->TMV[ RESET ];
    that->TMV[ GETCENTREX ] = ( ptrFonction ) that->superClasse->TMV[ GETCENTREX ];
    that->TMV[ GETCENTREY ] = ( ptrFonction ) that->superClasse->TMV[ GETCENTREY ];
    that->TMV[ AFFICHER ]   = ( ptrFonction ) & Cercle_afficher;


    /* Initialisation des methode heritees */

    that->setX        = ( void (*)( Cercle *, int ) ) that->superClasse->setX;
    that->getX        = ( int  (*)( Cercle * ) )      that->superClasse->getX;
    that->setY        = ( void (*)( Cercle *, int ) ) that->superClasse->setY;
    that->getY        = ( int  (*)( Cercle * ) )      that->superClasse->getY;
    that->getCentreX  = ( int  (*)( Cercle * ) )      that->superClasse->getCentreX;
    that->getCentreY  = ( int  (*)( Cercle * ) )      that->superClasse->getCentreY;
    that->afficher    = ( void (*)( Cercle * ) )      that->superClasse->afficher;

    that->GetNbObjetsGraphiques = that->superClasse->GetNbObjetsGraphiques;
}
