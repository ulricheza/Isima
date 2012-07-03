/*
 * \file Requete.h
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \brief fichier de declaration de la classe requete
 * \version 1.0
 * \date 7 janvier 2011
 */
#ifndef _REQUETE_H
#define	_REQUETE_H

class Program;
class Tournee;

class Requete {
public:
    Requete(int collecte, int livraison, int quantite, Program * myprogram);

    //getters
    int getCollecte()       {return _collecte;}
    int getLivraison()      {return _livraison;}
    int getArriveCollecte() {return _ArriveCollecte;}
    int getDepartCollecte() {return _DepartCollecte;}
    int getArriveLivraison(){return _ArriveLivraison;}
    int getDepartLivraison(){return _DepartLivraison;}
    int getQuantite()       {return _quantite;}
    Program * getMyprogram(){return _myprogram;}
    Tournee * getTournee() { return _tournee; }

    //setters
    void setArriveCollecte  (int val) {_ArriveCollecte = val;}
    void setDepartCollecte  (int val) {_DepartCollecte = val;}
    void setArriveLivraison (int val) {_ArriveLivraison = val;}
    void setDepartLivraison (int val) {_DepartLivraison = val;}
    void setTournee(Tournee * val)    { _tournee = val; }
   
private:
    int _collecte;
    int _livraison;
    int _ArriveCollecte;
    int _DepartCollecte;
    int _ArriveLivraison;
    int _DepartLivraison;
    int _quantite;
    Program * _myprogram;

    // Variable utilisée dans l'algorithme de Saving
    Tournee * _tournee;
};
#endif	/* _REQUETE_H */
