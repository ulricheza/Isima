#ifndef ECHANTILLON_H
#define ECHANTILLON_H

#include <vector>
#include "valeur.h"

using std::vector;

class Echantillon
{
public:
    Echantillon();

    //Ajout d'une valeur dans l'echantillon.
    void addValeur(Valeur * valeur) { _vecteur.push_back(valeur); }

    //Surcharge de l'operateur [] pour acceder aux valeurs du vecteur.
    Valeur * operator[] (int indice) const { return _vecteur[indice]; }
    Valeur * operator[] (int indice)       { return _vecteur[indice]; }

    int getSize() const {return _vecteur.size();}
    int getSize()       { return _vecteur.size();}

protected:
    vector<Valeur*> _vecteur;
};

#endif // ECHANTILLON_H
