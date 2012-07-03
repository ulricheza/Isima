#ifndef COLONNE_H
#define COLONNE_H

#include <list>
#include "carte.hpp"

using std::list;

class Colonne
{
public:
    Colonne();

    bool         estVide()         { return ( _cartesVisibles.empty() && _cartesCachees.empty()); }
    unsigned int getTaille()       { return _cartesVisibles.size(); }
    unsigned int getTaille() const { return _cartesVisibles.size(); }
    Carte *      getSommet();
    Carte *      getCarte(int position);
    Carte *      getCarte(int position) const;
    void         ajouter(Main & main);
    void         ajouter(Carte * carte);
    void         ajouterCarteCachee(Carte * carte) { _cartesCachees.push_back(carte); }
    void         retirer(int pos, Main & main);
    void         retourner();


private:
    list<Carte*> _cartesVisibles;
    list<Carte*> _cartesCachees;
};

#endif // COLONNE_H
