/*
 * \file Lieu.h
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \brief fichier de declaration de la classe Lieu
 * \version 1.0
 * \date 7 janvier 2011
 */

#ifndef _LIEU_H
#define	_LIEU_H

#include "Point.h"

class Program;

class Lieu {
public:
    Lieu(int id,const Point & coord, int ouverture, int fermeture, int demande,
         int tempservice, int clientcollecte, int clientlivraison,
         Program * myprogram);
    
    //getters
    Point getCoord()       {return _coord;}
    int   getDemande()     {return _demande;}
    int   getFermeture()   {return _fermeture;}
    int   getId()          {return _id;}
    int   getOuverture()   {return _ouverture;}
    int   getTempservice() {return _tempservice;}

private:
    Program * _myprogram;
    int _id;
    Point _coord;
    int _ouverture;
    int _fermeture;
    int _demande;
    int _tempservice;
    int _clientcollecte;
    int _clientlivraison;
};
#endif	/* _LIEU_H */
