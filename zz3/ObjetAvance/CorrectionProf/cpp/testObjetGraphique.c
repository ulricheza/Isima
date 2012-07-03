#include <stdio.h>
#include <stdlib.h>

#include "ObjetGraphique.h"
#include "Cercle.h"
#include "Rectangle.h"
#include "ZoneTexte.h"

#include "dynamic.h"

void initAll()
{
    initMetaObjetGraphique();
    initMetaCercle();
    initMetaRectangle();
    initMetaZoneTexte();
}


#define PRINT_CODE( pseudoCode ) \
    printf( "\n" #pseudoCode "\n" )


void testConstructionEtDestruction( void )
{
    printf( "\n\n------ Test de construction/destruction ------\n" );

    {
        printf( "\nObjetGraphique og( 0, 0 );\n" );
        ObjetGraphique og;
        LeMetaObjetGraphique.init( & og, 0, 0 );

        printf( "\nObjetGraphique * pog = new ObjetGraphique( 0, 0 );\n" );
        ObjetGraphique * pog = NEW( ObjetGraphique, ( 0 )( 0 ) );

        printf( "\ndelete pog;\n" );
        DELETE( pog );

        printf( "\n//Sortie de la portee : destruction de og\n" );
        og.maClasse->reset( & og );
    }

    {
        printf( "\nCercle c( 0, 0, 10 );\n" );
        Cercle c;
        LeMetaCercle.init( & c, 0, 0, 10 );

        printf( "\nCercle * pc = new Cercle( 0, 0, 10 );\n" );
        Cercle * pc = NEW( Cercle, ( 0 )( 0 )( 10 ) );

        printf( "\ndelete pc;\n" );
        DELETE( pc );

        printf( "\n//Sortie de la portee : destruction de c\n" );
        c.maClasse->reset( & c );
    }

    {
        printf( "\nZoneTexte zt( 0, 0, 100, 10, \"du texte\" );\n" );
        ZoneTexte zt;
        LeMetaZoneTexte.init( & zt, 0, 0, 100, 10, "du texte" );

        printf( "\nZoneTexte * pzt = new ZoneTexte( 0, 0, 100, 10, \"du texte\" );\n" );
        ZoneTexte * pzt = NEW( ZoneTexte, ( 0 )( 0 )( 100 )( 10 )( "du texte" ) );

        printf( "\ndelete pzt;\n" );
        DELETE( pzt );

        printf( "\n//Sortie de la portee : destruction de zt\n" );
        zt.maClasse->reset( & zt );
    }
}

void testAppelsMethodesDeClasse( void )
{
    printf( "\n\n------ Test d'appels de methodes de classe ------\n" );

/*    printf( "printf( \"%%d\", ObjetGraphique::GetNbObjetGraphiques() );\n" ); */
/*    printf( "  --> %d\n", LeMetaObjetGraphique.GetNbObjetsGraphiques() ); */

    PRINT_CODE( printf( "%%d\n", ObjetGraphique::GetNbObjetGraphique() ); );
    printf( "  --> %d\n", LeMetaObjetGraphique.GetNbObjetsGraphiques() );

    {
        PRINT_CODE( ObjetGraphique og( 0, 0 ); );
        ObjetGraphique og;
        LeMetaObjetGraphique.init( & og, 0, 0 );

        PRINT_CODE( printf( "%%d", ObjetGraphique::GetNbObjetGraphiques() ); );
        printf( "  --> %d\n", LeMetaObjetGraphique.GetNbObjetsGraphiques() );

        PRINT_CODE( printf( "%%d", og.GetNbObjetGraphiques() ); );
        printf( "  --> %d\n", og.maClasse->GetNbObjetsGraphiques() );

        {
            PRINT_CODE( Cercle c( 0, 0, 10 ); );
            Cercle c;
            LeMetaCercle.init( & c, 0, 0, 10 );

            PRINT_CODE( printf( "%%d", ObjetGraphique::GetNbObjetGraphiques() ); );
            printf( "  --> %d\n", LeMetaObjetGraphique.GetNbObjetsGraphiques() );

            PRINT_CODE( printf( "%%d", og.GetNbObjetGraphiques() ); );
            printf( "  --> %d\n", og.maClasse->GetNbObjetsGraphiques() );

            PRINT_CODE( printf( "%%d", c.GetNbObjetGraphiques() ); );
            printf( "  --> %d\n", c.maClasse->GetNbObjetsGraphiques() );

            PRINT_CODE( Cercle * pc = & c; );
            Cercle * pc = & c;

            PRINT_CODE( printf( "%%d", pc->GetNbObjetsGraphiques() ); );
            printf( "  --> %d\n", pc->maClasse->GetNbObjetsGraphiques() );

            printf( "\n// Sortie de la portee : destruction de c\n" );

            c.maClasse->reset( & c );
        }

        PRINT_CODE( printf( "%%d", ObjetGraphique::GetNbObjetGraphiques() ); );
        printf( "%d\n", LeMetaObjetGraphique.GetNbObjetsGraphiques() );

        PRINT_CODE( printf( "%%d", og.GetNbObjetGraphiques() ); );
        printf( "  --> %d\n", og.maClasse->GetNbObjetsGraphiques() );

        printf( "\n// Sortie de la portee : destruction de og\n" );
        og.maClasse->reset( & og );
    }

    PRINT_CODE( printf( "%%d", ObjetGraphique::GetNbObjetGraphiques() ); );
    printf( "  --> %d\n", LeMetaObjetGraphique.GetNbObjetsGraphiques() );
}

void testAppelsMethodesNonVirtuelles( void )
{
    printf( "\n\n------ Test d'appels de methodes d'instance non virtuelles ------\n\n" );

    PRINT_CODE( ObjetGraphique og( 0, 0 ); );
    ObjetGraphique og;
    LeMetaObjetGraphique.init( & og, 0, 0 );

    PRINT_CODE( printf( "og.x == %%d", og.getX() ); );
    printf( "  --> og.x == %d\n", og.maClasse->getX( & og ) );

    PRINT_CODE( og.setX( 42 ); );
    og.maClasse->setX( & og, 42 );

    PRINT_CODE( printf( "og.x == %%d", og.getX() ); );
    printf( "  --> og.x == %d\n", og.maClasse->getX( & og ) );


    PRINT_CODE( ZoneTexte zt( 0, 0, 100, 10, "du texte" ); );
    ZoneTexte zt;
    LeMetaZoneTexte.init( & zt, 0, 0, 100, 10, "du texte" );

    PRINT_CODE( printf( "zt.y == %%d, zt.texte == %%s", zt.getY(), zt.getTexte() ); );
    printf( "  --> zt.y == %d, zt.texte == %s\n", zt.maClasse->getY( & zt ), zt.maClasse->getTexte( & zt ) );

    PRINT_CODE( zt.setY( 99 ); );
    zt.maClasse->setY( & zt, 99 );

    PRINT_CODE( zt.setTexte( "nouveau texte" ); );
    zt.maClasse->setTexte( & zt, "nouveau texte" );

    PRINT_CODE( printf( "zt.y == %%d, texte == %%s", zt.getY(), zt.getTexte() ); );
    printf( "  --> zt.y == %d, texte == %s\n", zt.maClasse->getY( & zt ), zt.maClasse->getTexte( & zt ) );


    PRINT_CODE( ZoneTexte * pzt = & zt; );
    ZoneTexte * pzt = & zt;

    PRINT_CODE( printf( "pzt->y == %%d, pzt->texte == %%s", pzt->getY(), pzt->getTexte() ); );
    printf( "  --> pzt->y == %d, pzt->texte == %s\n", pzt->maClasse->getY( pzt ), pzt->maClasse->getTexte( pzt ) );


    PRINT_CODE( Rectangle * pr2zt = pzt; );
    Rectangle * pr2zt = ( Rectangle * ) pzt;

    PRINT_CODE( printf( "pr2zt->y == %%d, pr2zt->hauteur == %%d", pr2zt->getY(), pr2zt->getHauteur() ); );
    printf( "  --> pr2zt->y == %d, pr2zt->hauteur == %d\n", pr2zt->maClasse->getY( pr2zt ), pr2zt->maClasse->getHauteur( pr2zt ) );


    printf( "\n// Sortie de la portee : destruction de og et zt\n" );
    og.maClasse->reset( & og );
    zt.maClasse->reset( & zt );
}

void testAppelsMethodesVirtuelles( void )
{
    printf( "\n\n------ Test d'appels de methodes d'instance virtuelles ------\n\n" );

    PRINT_CODE( ObjetGraphique og( 0, 0 ); );
    ObjetGraphique og;
    LeMetaObjetGraphique.init( & og, 0, 0 );

    PRINT_CODE( printf( "og.centreX == %%d", og.getCentreX() ); );
    printf( "  --> og.centreX == %d\n", og.maClasse->getCentreX( & og ) );

    PRINT_CODE( og.setX( 42 ); );
    og.maClasse->setX( & og, 42 );

    PRINT_CODE( printf( "og.centreX == %%d", og.getCentreX() ); );
    printf( "  --> og.centreX == %d\n", og.maClasse->getCentreX( & og ) );


    PRINT_CODE( ZoneTexte zt( 0, 0, 100, 10, "du texte" ); );
    ZoneTexte zt;
    LeMetaZoneTexte.init( & zt, 0, 0, 100, 10, "du texte" );

    PRINT_CODE( zt.afficher(); );
    printf( "  --> " );
    zt.maClasse->afficher( & zt );
    printf( "\n" );

    PRINT_CODE( printf( "zt.centreX == %%d", zt.getCentreX() ); );
    printf( "  --> zt.centreX == %d\n", zt.maClasse->getCentreX( & zt ) );

    PRINT_CODE( zt.setLargeur( 500 ); );
    zt.maClasse->setLargeur( & zt, 500 );

    PRINT_CODE( printf( "zt.centreX == %%d", zt.getCentreX() ); );
    printf( "  --> zt.centreX == %d\n", zt.maClasse->getCentreX( & zt ) );


    PRINT_CODE( Rectangle * pr2zt = & zt; );
    Rectangle * pr2zt = ( Rectangle * ) & zt;

    PRINT_CODE( pr2zt->afficher(); );
    printf( "  --> " );
    pr2zt->maClasse->afficher( pr2zt );
    printf( "\n" );

    PRINT_CODE( pr2zt->tourner( 1 ); );
    pr2zt->maClasse->tourner( pr2zt, 1 );

    PRINT_CODE( pr2zt->afficher(); );
    printf( "  --> " );
    pr2zt->maClasse->afficher( pr2zt );
    printf( "\n" );

    PRINT_CODE( pr2zt->tourner( 2 ); );
    pr2zt->maClasse->tourner( pr2zt, 2 );

    PRINT_CODE( pr2zt->afficher(); );
    printf( "  --> " );
    pr2zt->maClasse->afficher( pr2zt );
    printf( "\n" );


    printf( "\n// Sortie de la portee : destruction de og et zt\n" );
    og.maClasse->reset( & og );
    zt.maClasse->reset( & zt );
}


int main()
{
    initAll();

    testConstructionEtDestruction();
    testAppelsMethodesDeClasse();
    testAppelsMethodesNonVirtuelles();
    testAppelsMethodesVirtuelles();

    return 0;
}
