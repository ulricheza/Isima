// Gardien //---------------------------------------------------------------------------------------
#ifndef _CONTROLEUR_GRAPHIQUE_HPP_
#define _CONTROLEUR_GRAPHIQUE_HPP_

// Entetes //---------------------------------------------------------------------------------------
#include <interface_qt/fenetrePrincipale.hpp>
#include <interface_qt/idCarte.hpp>
#include <interface_qt/idZone.hpp>
#include <solitaire/controleur.hpp>

// Declarations anticipees //-----------------------------------------------------------------------
class QApplication;

// Classe  C o n t r o l e u r G r a p h i q u e //-------------------------------------------------
class ControleurGraphique : public QObject, public Controleur {
 Q_OBJECT
 //----------------------------------------------------------------------------------------Attributs
 protected: QApplication      & appli_;
 protected: FenetrePrincipale   fenetre_;
 //-------------------------------------------------------------------------------Methodes publiques
 public: ControleurGraphique(Solitaire &,QApplication &);

 public: void demarrer(void);
 public: void rafraichir(void);
};

// Fin //-------------------------------------------------------------------------------------------
#endif
