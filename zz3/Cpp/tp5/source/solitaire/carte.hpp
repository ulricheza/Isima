// Gardien //---------------------------------------------------------------------------------------
#ifndef _CARTE_HPP_
#define _CARTE_HPP_

#include <vector>

using std::vector;

// Classe  C a r t e //-----------------------------------------------------------------------------
class Carte {
 //--------------------------------------------------------------------------------------------Types
 public: typedef enum { PIQUE,COEUR,CARREAU,TREFLE } famille_t;
 public: typedef enum { AS,DEUX,TROIS,QUATRE,CINQ,SIX,SEPT,HUIT,NEUF,DIX,VALET,DAME,ROI } valeur_t;
 //----------------------------------------------------------------------------------------Attributs
 protected: famille_t famille_;
 protected: valeur_t  valeur_;
 protected: bool      cachee_;
 //---------------------------------------------------------------------------------------Accesseurs
 public: famille_t getFamille(void) const { return famille_; }
 public: valeur_t  getValeur(void) const { return valeur_; }
 public: size_t    getNumero(void) const { return 13*(size_t)famille_+(size_t)valeur_; }
 public: bool      estCachee(void) const { return cachee_; }

 public: void setFamille(famille_t famille) { famille_=famille; }
 public: void setValeur(valeur_t valeur) { valeur_=valeur; }
 public: void setCachee(bool cachee) { cachee_=cachee; }

 public: bool estRouge(void) const { return (famille_==COEUR || famille_==CARREAU); }
 public: bool estNoir(void) const { return (famille_==PIQUE || famille_==TREFLE); }
 //------------------------------------------------------------------------------------Constructeurs
 public: Carte(famille_t famille,valeur_t valeur,bool cachee = true)
 : famille_(famille),valeur_(valeur),cachee_(cachee) {}

 public: Carte(int famille,int valeur,bool cachee = true)
 : famille_(famille_t(famille)),valeur_(valeur_t(valeur)),cachee_(cachee) {}
};

typedef vector<Carte*> Main;

// Fin //-------------------------------------------------------------------------------------------
#endif
