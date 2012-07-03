// Gardien //---------------------------------------------------------------------------------------
#ifndef _CONTROLEUR_TEXTE_HPP_
#define _CONTROLEUR_TEXTE_HPP_

// Entetes //---------------------------------------------------------------------------------------
#include <iostream>
#include <solitaire/controleur.hpp>

// Declarations Fonctions //------------------------------------------------------------------------
std::ostream & operator<< (std::ostream &,const Carte *);
std::ostream & operator << (std::ostream &,const Dock &);
std::ostream & operator << (std::ostream &,const Pioche &);

// Classe  C o n t r o l e u r T e x t e //---------------------------------------------------------
class ControleurTexte : public Controleur {
 //--------------------------------------------------------------------------------------------Amies
 friend std::ostream & operator<< (std::ostream &,const Carte *);
 friend std::ostream & operator << (std::ostream &,const Dock &);
 friend std::ostream & operator << (std::ostream &,const Pioche &);
 //----------------------------------------------------------------------------------------Attributs
 protected: static const char FAMILLES[];
 protected: static const char VALEURS[];
 protected: static const char COULEUR_DOS[];
 protected: static const char COULEUR_NOIR[];
 protected: static const char COULEUR_ROUGE[];
 protected: static const char COULEUR_NORMAL[];
 //------------------------------------------------------------------------------------Constructeurs
 public: ControleurTexte(Solitaire & solitaire) : Controleur(solitaire) {}
 //-------------------------------------------------------------------------------Methodes publiques
 public: void demarrer(void);
 public: void rafraichir(void);
};

// Fin //-------------------------------------------------------------------------------------------
#endif
