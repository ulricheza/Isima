#ifndef PIOCHE_H
#define PIOCHE_H

#include <stack>
#include "carte.hpp"

using std::stack;

class Pioche
{
public:
    Pioche();

    void    ajouter(Carte * carte) { _cartesCachees.push(carte);}
    bool    rienRetourne()         { return _cartesVisibles.empty(); }
    bool    rienRetourne() const   { return _cartesVisibles.empty(); }
    bool    toutRetourne()         { return _cartesCachees.empty();  }
    bool    estVide()              { return (rienRetourne() && toutRetourne());}
    bool    tirer();
    //bool    tirer() const;
    Carte * retirer();
    Carte * getVisible()           { return (rienRetourne())? NULL : _cartesVisibles.top(); }
    Carte * getVisible() const     { return (rienRetourne())? NULL : _cartesVisibles.top(); }
    Carte * getProchaine();
    Carte * getProchaine() const;

private:

    stack<Carte*> _cartesVisibles;
    stack<Carte*> _cartesCachees;
};

#endif // PIOCHE_H
