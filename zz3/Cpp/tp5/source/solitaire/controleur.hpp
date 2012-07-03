// Gardien //---------------------------------------------------------------------------------------
#ifndef _CONTROLEUR_HPP_
#define _CONTROLEUR_HPP_

// Entetes //---------------------------------------------------------------------------------------
#include <solitaire/solitaire.hpp>

// Declarations anticipees //-----------------------------------------------------------------------
class Solitaire;

// Classe  C o n t r o l e u r //-------------------------------------------------------------------
class Controleur {
 //----------------------------------------------------------------------------------------Attributs
 public: Solitaire & solitaire_;
 //------------------------------------------------------------------------------------Constructeurs
 public: Controleur(Solitaire & solitaire) : solitaire_(solitaire) {}
 //--------------------------------------------------------------------------------------Destructeur
 public: virtual ~Controleur(void) {}
 //-------------------------------------------------------------------------------Methodes publiques
 public: virtual void demarrer(void) = 0;
 public: virtual void rafraichir(void) = 0;
};

// Fin //-------------------------------------------------------------------------------------------
#endif
