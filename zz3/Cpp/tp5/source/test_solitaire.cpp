// Entetes //---------------------------------------------------------------------------------------
#include <ctime>
#include <cstdlib>

#include <adaptateur_controleur_graphique.hpp>
#include <controleur_texte.hpp>

Controleur * creerControleur( const std::string &  type,
                              Solitaire         &  solitaire,
                              int                  argc,
                              char              ** argv )
{
    if ( type == "txt" )
    {
        return new ControleurTexte( solitaire );
    }
    else if ( type == "gui" )
    {
        return new AdaptateurControleurGraphique( solitaire, argc, argv );
    }

    return NULL;
}


int main(int argc, char ** argv) {

 std::string typeInterface( "gui" );

 if ( argc >= 2 )
 {
  typeInterface = argv[ 1 ];
 }

 Solitaire    solitaire;
 Controleur * controleur = creerControleur( typeInterface, solitaire, argc, argv );

 if ( controleur == NULL )
 {
  std::cout << "Option d'affichage invalide." << std::endl;
  return 1;
 }

 std::srand(time(0));
 solitaire.setControleur(*controleur);
 controleur->demarrer();

 delete controleur;

 return 0;
}

// Fin //-------------------------------------------------------------------------------------------
