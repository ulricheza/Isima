#ifndef CROUPIER_H
#define CROUPIER_H

#include <list>
#include "paquet.hpp"
#include "plateau.hpp"
#include "carte.hpp"

using std::list;

class Croupier
{
public:
    Croupier();

    void         distribuer(Paquet & paquet, Plateau & plateau);
    virtual void melanger  (Paquet & paquet) = 0;

protected:
    list<Carte*> _cartesMelanges;
};
#endif // CROUPIER_H
