// Entetes //---------------------------------------------------------------------------------------
#include <adaptateur_controleur_graphique.hpp>

// Implementation  A d a p t a t e u r C o n t r o l e u r G r a p h i q u e //---------------------

//--------------------------------------------------------------------------------------Constructeur
AdaptateurControleurGraphique::AdaptateurControleurGraphique(Solitaire & solitaire,int argc,char ** argv)
: Controleur(solitaire),appli_(argc,argv),controleur_(solitaire,appli_) {}

//------------------------------------------------------------------------------------------Demarrer
void AdaptateurControleurGraphique::demarrer(void)
{
    controleur_.demarrer();
}

//----------------------------------------------------------------------------------------Rafraichir
void AdaptateurControleurGraphique::rafraichir(void)
{
    controleur_.rafraichir();
}
