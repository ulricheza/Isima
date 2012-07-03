#include "ZoneTexte.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


/* Constructeur de ZoneTexte */
ZoneTexte * MetaZoneTexte_init( ZoneTexte * this, int x, int y, int largeur, int hauteur, char * texte )
{
    /* Partie "generee" */
    assert(this);

    this->maClasse = & LeMetaZoneTexte;
    this->maClasse->superClasse->init( & this->super /* ou simplement this */, x, y, largeur, hauteur );

    #ifdef TEST
    printf( "  --> appel de ZoneTexte::ZoneTexte\n" );
    #endif

    /* this->super.super.vptr = this->maClasse->TMV; */
    * ( ( ptrFonction ** ) this ) = this->maClasse->TMV;

    /* Partie utilisateur */
    this->texte = ( char * ) malloc( strlen( texte ) + 1 );
    strcpy( this->texte, texte );
    this->orientation = GAUCHE_DROITE;

    return this;
}

/* Destructeur de ZoneTexte */
void MetaZoneTexte_reset( ZoneTexte * this )
{
    #ifdef TEST
    printf( "  --> appel de ZoneTexte::~ZoneTexte\n" );
    #endif

    /* Partie "generee" */

    * ( ( ptrFonction ** ) this ) = this->maClasse->TMV; /* Reinitialisation du vptr */

    /* Partie utilisateur */

    free( this->texte );

    /* Partie "generee" */

    /* Appel du destructeur de la classe de base. */
    ( ( void (*)( void * ) ) this->maClasse->superClasse->TMV[ RESET ] )( this );

    /* cf. la methode 'tourner' */
}

/* Methodes non virtuelles */

void ZoneTexte_setTexte( ZoneTexte * this, char * texte )
{
    char * tmp = strcpy( ( char * ) malloc( strlen( texte ) ), texte );
    free( this->texte );
    this->texte = tmp;
}

char * ZoneTexte_getTexte( ZoneTexte * this )
{
    return this->texte;
}

/* Methodes virtuelles */

/* Redefinition de afficher pour ZoneTexte */
void ZoneTexte_afficher( ZoneTexte * this )
{
    Rectangle      * this_r  = ( Rectangle * )      this;
    ObjetGraphique * this_og = ( ObjetGraphique * ) this;

    char const * orientation;

    switch( this->orientation )
    {
        case GAUCHE_DROITE : orientation = "GD"; break;
        case HAUT_BAS      : orientation = "HB"; break;
        case DROITE_GAUCHE : orientation = "DG"; break;
        case BAS_HAUT      : orientation = "BH"; break;

        default : assert( 0 );
    }

    printf( "ZoneTexte : x=%d, y=%d, largeur=%d, hauteur=%d, texte=%s (%s)",
            this_og->x,
            this_og->y,
            this_r->largeur,
            this_r->hauteur,
            this->texte,
            orientation );
}

/* Redefinition de tourner pour ZoneTexte */
void ZoneTexte_tourner( ZoneTexte * this, int rotation )
{
    /*
      Les trois lignes suivantes servent a appeler la methode tourner de la classe
      de base (Rectangle en l'occurence). Ce serait plus ou moins l'equivalent de
      'super.tourner' en Java.
      J'utilise un 'void *' en parametre pour limiter au maximum les references
      explicites a la classe Rectangle (histoire d'augmenter le decouplage).
     */
    typedef void ( * fonctionTourner )( void *, int );

    fonctionTourner super_tourner = ( fonctionTourner ) this->maClasse->superClasse->TMV[ TOURNER ];

    super_tourner( this, rotation );


    this->orientation = ( this->orientation + rotation ) % ZONE_TEXTE_NB_ORIENTATIONS;
}


/*
  Fonction d'initialisation du meta-rectangle.
  Preconditions : LeMetaRectangle doit etre initialise (cf. initMetaRectangle)
 */
void initMetaZoneTexte( void )
{
    struct MetaZoneTexte_t * that = & LeMetaZoneTexte;

    that->superClasse = & LeMetaRectangle;

    /* Initialisation des pointeurs de fonctions (methodes) */

    that->init   = & MetaZoneTexte_init;
    that->reset  = ( void (*)( ZoneTexte * ) ) that->superClasse->reset;

    that->setTexte = & ZoneTexte_setTexte;
    that->getTexte = & ZoneTexte_getTexte;

    /* Initialisation de la table des methodes virtuelles */

    /* La ZoneTexte a un destructeur "propre". */
    that->TMV[ RESET ]      = ( ptrFonction ) & MetaZoneTexte_reset;
    that->TMV[ GETCENTREX ] = that->superClasse->TMV[ GETCENTREX ];
    that->TMV[ GETCENTREY ] = that->superClasse->TMV[ GETCENTREY ];;
    that->TMV[ AFFICHER ]   = ( ptrFonction ) & ZoneTexte_afficher;

    that->TMV[ TOURNER ]    = ( ptrFonction ) & ZoneTexte_tourner;


    /* Initialisation des methode heritees */

    that->setX        = ( void (*)( ZoneTexte *, int ) ) that->superClasse->setX;
    that->getX        = ( int  (*)( ZoneTexte * ) )      that->superClasse->getX;
    that->setY        = ( void (*)( ZoneTexte *, int ) ) that->superClasse->setY;
    that->getY        = ( int  (*)( ZoneTexte * ) )      that->superClasse->getY;
    that->getCentreX  = ( int  (*)( ZoneTexte * ) )      that->superClasse->getCentreX;
    that->getCentreY  = ( int  (*)( ZoneTexte * ) )      that->superClasse->getCentreY;
    that->afficher    = ( void (*)( ZoneTexte * ) )      that->superClasse->afficher;

    that->setLargeur  = ( void (*)( ZoneTexte *, int ) ) that->superClasse->setLargeur;
    that->getLargeur  = ( int  (*)( ZoneTexte * ) )      that->superClasse->getLargeur;
    that->setHauteur  = ( void (*)( ZoneTexte *, int ) ) that->superClasse->setHauteur;
    that->getHauteur  = ( int  (*)( ZoneTexte * ) )      that->superClasse->getHauteur;
    that->tourner     = ( void (*)( ZoneTexte *, int ) ) that->superClasse->tourner;

    that->GetNbObjetsGraphiques = that->superClasse->GetNbObjetsGraphiques;
}

