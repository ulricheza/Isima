// Gardien //---------------------------------------------------------------------------------------
#ifndef _PLATEAU_HPP_
#define _PLATEAU_HPP_


#include "pioche.h"
#include "dock.h"
#include "colonne.h"
#include "carte.hpp"




// Entetes //---------------------------------------------------------------------------------------

// Classe  P l a t e a u //-------------------------------------------------------------------------
class Plateau {
 //----------------------------------------------------------------------------------------Attributs
    protected: Colonne colonnes_[7];
    protected: Dock    docks_[4];
    protected: Pioche  pioche_;
    protected: Main    main_;
 //---------------------------------------------------------------------------------------Accesseurs
    public: Colonne & getColonne(size_t indice) { return colonnes_[indice]; }
    public: Dock &    getDock(size_t indice) { return docks_[indice]; }
    public: Pioche &  getPioche(void) { return pioche_; }
    public: Main &    getMain(void) { return main_; }
 //
    public: const Colonne & getColonne(size_t indice) const { return colonnes_[indice]; }
    public: const Dock &    getDock(size_t indice) const { return docks_[indice]; }
    public: const Pioche &  getPioche(void) const { return pioche_; }
    public: const Main &    getMain(void) const { return main_; }
};

// Fin //-------------------------------------------------------------------------------------------
#endif
