// Gardien //---------------------------------------------------------------------------------------
#ifndef _ADAPTATEUR_CONTROLEUR_GRAPHIQUE_HPP
#define _ADAPTATEUR_CONTROLEUR_GRAPHIQUE_HPP

// Entetes //---------------------------------------------------------------------------------------
#include <QtGui/QApplication>

#include <solitaire/controleur.hpp>
#include <controleur_graphique.hpp>

// Declarations anticipees //-----------------------------------------------------------------------
class Solitaire;

class AdaptateurControleurGraphique : public Controleur
{
 //----------------------------------------------------------------------------------------Attributs
 protected: QApplication        appli_;
 protected: ControleurGraphique controleur_;
 //-------------------------------------------------------------------------------Methodes publiques
 public: AdaptateurControleurGraphique(Solitaire &,int,char **);

 public: void demarrer(void);
 public: void rafraichir(void);
};

// Fin //-------------------------------------------------------------------------------------------
#endif
