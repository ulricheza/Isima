// Gardien //---------------------------------------------------------------------------------------
#ifndef _SOLITAIRE_HPP_
#define _SOLITAIRE_HPP_

// Entetes //---------------------------------------------------------------------------------------
#include <solitaire/controleur.hpp>
#include <solitaire/paquet.hpp>
#include <solitaire/plateau.hpp>

// Declarations anticipees //-----------------------------------------------------------------------
class Controleur;

// Classe  S o l i t a i r e //---------------------------------------------------------------------
class Solitaire {
 //----------------------------------------------------------------------------------------Attributs
 protected: Paquet       paquet_;
 protected: Plateau      plateau_;
 protected: Controleur * controleur_;
 //---------------------------------------------------------------------------------------Accesseurs
 public: const Plateau & getPlateau(void) const { return plateau_; }

 public: void setControleur(Controleur & controleur) { controleur_=&controleur; }
 //------------------------------------------------------------------------------------Constructeurs
 public: Solitaire(void);
 //-------------------------------------------------------------------------------Methodes publiques
 public: void initialiser(void);
};

// Fin //-------------------------------------------------------------------------------------------
#endif
