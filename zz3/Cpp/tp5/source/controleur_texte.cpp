// Entetes //---------------------------------------------------------------------------------------
#include <controleur_texte.hpp>

// Implementation  C o n t r o l e u r T e x t e //-------------------------------------------------

//-----------------------------------------------------------------------------------------Attributs
const char ControleurTexte::FAMILLES[] = "*$#@";
const char ControleurTexte::VALEURS[] = "1234567890VDR";
const char ControleurTexte::COULEUR_DOS[] = "\033[42m";
const char ControleurTexte::COULEUR_NOIR[] = "\033[40m";
const char ControleurTexte::COULEUR_ROUGE[] = "\033[41m";
const char ControleurTexte::COULEUR_NORMAL[] = "\033[0m";

//------------------------------------------------------------------------------------------Demarrer
void ControleurTexte::demarrer(void) {
// char choix[32];
// int  colonne;
// int  ligne;
// bool ok;
//
// const Plateau & plateau = solitaire_.getPlateau();
// Arbitre &       arbitre = solitaire_.getArbitre();
//
// solitaire_.initialiser();
//
// do {
//  std::cout << std::endl << "Action: ";
//  std::cin >> choix;
//
//  colonne=999;
//  ok=false;
//
//  if (choix[0]>='a' && choix[0]<='g') colonne=choix[0]-'a';
//  else if (choix[0]>='A' && choix[0]<='G') colonne=choix[0]-'A';
//  else if (choix[0]>='w' && choix[0]<='z') colonne=10+choix[0]-'w';
//  else if (choix[0]>='W' && choix[0]<='Z') colonne=10+choix[0]-'W';
//  else if (choix[0]=='o' || choix[0]=='0') colonne=100;
//  else if (choix[0]=='p' || choix[0]=='P') colonne=101;
//
//  if (colonne<7) {
//   if (plateau.getMain().empty()) {
//    if (sscanf(choix+1,"%d",&ligne)!=1) ligne=plateau.getColonne(colonne).getTaille();
//    std::cout << "Retrait colonne " << char('A'+colonne) << ligne << "... ";
//    ok=arbitre.retirerColonne(colonne,ligne-1);
//   }
//   else {
//    std::cout << "Depot colonne " << char('A'+colonne) << "... ";
//    ok=arbitre.deposerColonne(colonne);
//   }
//  }
//  else if (colonne<100) {
//   if (!plateau.getMain().empty()) {
//    colonne-=10;
//    std::cout << "Depot dock " << char('W'+colonne) << "... ";
//    ok=arbitre.deposerDock(colonne);
//   }
//  }
//  else if (colonne==100) {
//   if (plateau.getMain().empty()) {
//    std::cout << std::endl << "Piocher... ";
//    ok=arbitre.piocher();
//   }
//  }
//  else if (colonne==101) {
//   if (plateau.getMain().empty()) {
//    std::cout << "Retrait pioche... ";
//    ok=arbitre.retirerPioche();
//   }
//  }
//  else if (choix[0]=='u' || choix[0]=='U') {
//   std::cout << "Annuler... ";
//   ok=arbitre.annuler();
//  }
//
//  if (choix[0]!='q' && choix[0]!='Q') {
//   std::cout << (ok ? "OK" : "NON") << std::endl;
//   if (ok) rafraichir();
//  }
// }
// while (choix[0]!='q' && choix[0]!='Q');
    rafraichir();
}

//----------------------------------------------------------------------------------------Rafraichir
void ControleurTexte::rafraichir(void) {
   size_t i;
   size_t j;

   size_t max = 0;

   const Plateau & plateau = solitaire_.getPlateau();

// // 1ere Ligne //
   std::cout << std::endl << "    " << plateau.getPioche() << "      ";
   for (i=0; i<4; ++i) std::cout << plateau.getDock(i) << " ";
//
// // 2nde Ligne //
   std::cout << std::endl << "     O    P         ";
   for (i=0; i<4; ++i) std::cout << char('W'+i) << "    ";
//
// // Colonnes //
   for (i=0; i<7; ++i)
    if (max<plateau.getColonne(i).getTaille()) max=plateau.getColonne(i).getTaille();

   std::cout << std::endl << std::endl << "    ";
   for (i=0; i<7; ++i) std::cout << " " << char('A'+i) << "   ";

   if (max==0) {
    std::cout << std::endl << "    ";
    for (i=0; i<7; ++i) std::cout << (Carte *)0 << " ";
   }

   for (j=0; j<max; ++j) {
    std::cout << std::endl << ' ' << (j<9 ? " " : "") << (j+1) << " ";
    for (i=0; i<7; ++i) std::cout << plateau.getColonne(i).getCarte(j) << " ";
   }

   // Main //
   std::cout << std::endl << std::endl << "    ";

   if (plateau.getMain().size()==0) std::cout << "[  ]";
   else for (i=plateau.getMain().size(); i>0; --i) std::cout << plateau.getMain()[i-1] << " ";

   std::cout << std::endl;
}

// Fonctions //-------------------------------------------------------------------------------------

//------------------------------------------------------------------------------Operateur << (Carte)
std::ostream & operator<< (std::ostream & flux,const Carte * carte) {
 if (carte==0) flux << "[  ]";
 else if (carte->estCachee()) flux << ControleurTexte::COULEUR_DOS << "[<>]";
 else {
  flux << (carte->estRouge() ? ControleurTexte::COULEUR_ROUGE : ControleurTexte::COULEUR_NOIR);

  flux << '[' << ControleurTexte::FAMILLES[carte->getFamille()]
              << ControleurTexte::VALEURS[carte->getValeur()] << ']';
 }

 flux << ControleurTexte::COULEUR_NORMAL;

 return flux;
}

//--------------------------------------------------------------------------------Operator << (Dock)
   std::ostream & operator << (std::ostream & flux,const Dock & dock) {
    flux << dock.getSommet();
    return flux;
  }

//------------------------------------------------------------------------------Operator << (Pioche)
   std::ostream & operator << (std::ostream & flux,const Pioche & pioche) {
    flux << pioche.getProchaine() << ' ' << pioche.getVisible();
    return flux;
   }

// Fin //-------------------------------------------------------------------------------------------
