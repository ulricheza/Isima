/* 
 * File:   Vecteur.h
 * Author: maxime
 *
 * Created on 11 octobre 2011, 14:11
 */

#ifndef _VECTEUR_H
#define	_VECTEUR_H

#include<iostream>

#include "Iterator.h"

using namespace std;

class Vecteur {
public:

    //Constructeur et destructeur
    Vecteur();
    Vecteur(int taille);
    Vecteur(int taille, int * tab);
    Vecteur(const Vecteur& orig);
    virtual ~Vecteur();

    //surcharge d'operateur
    Vecteur   operator=  (Vecteur & vect);
    Vecteur   operator+  (Vecteur & vect);
    int       operator*  (Vecteur & vect);
    int &     operator[] (const int & iter);

    //Methodes
    void   push_back(int x);
    void   pop_back();
    int    front();
    int    back();
    int    size()    { return _longueur; }
    int    max_size(){ return _longueurMax;}
    string toString() const;
    Iterator begin();
    Iterator end();

private:
    int   _longueur;
    int   _longueurMax;
    int * _tableau;
};

ostream & operator<< (ostream & stream, const Vecteur & vecteur);

#endif	/* _VECTEUR_H */

