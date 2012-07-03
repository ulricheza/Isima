// Gardien //---------------------------------------------------------------------------------------
#ifndef _PAQUET_HPP_
#define _PAQUET_HPP_

// Entetes //---------------------------------------------------------------------------------------
#include <vector>
#include <solitaire/carte.hpp>

// Classe  P a q u e t //---------------------------------------------------------------------------
class Paquet {
 //----------------------------------------------------------------------------------------Attributs
 protected: std::vector<Carte *> cartes_;
 protected: size_t               courante_;
 //-------------------------------------------------------------------------------Methodes publiques
 public: Paquet(void);
 public: ~Paquet(void);

 public: Carte * getSuivante(void);
 public: void    permuter(size_t,size_t);
 public: void    reinitialiser(void) { courante_=0; }
};

// Implementation  P a q u e t //-------------------------------------------------------------------

//---------------------------------------------------------------------------------------GetSuivante
inline Carte * Paquet::getSuivante(void) {
 if (courante_==52) return 0;
 return cartes_[courante_++];
}

//------------------------------------------------------------------------------------------Permuter
inline void Paquet::permuter(size_t i,size_t j) {
 Carte * tmp = cartes_[i];

 cartes_[i]=cartes_[j];
 cartes_[j]=tmp;
}

// Fin //-------------------------------------------------------------------------------------------
#endif
