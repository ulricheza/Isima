#include "croupier.h"

Croupier::Croupier()
{
}

void Croupier::distribuer(Paquet &paquet, Plateau &plateau)
{
    //remplissage des colonne;
    for(int i = 0; i < 7 ; ++i)
    {
        for(int j = 0; j < i ; ++j)
        {
            plateau.getColonne(i).ajouterCarteCachee(_cartesMelanges.back());
            _cartesMelanges.pop_back();
        }
        plateau.getColonne(i).retourner();
    }

    //remplissage du dock
    while(!_cartesMelanges.empty())
    {
        plateau.getPioche().ajouter(_cartesMelanges.back());
        _cartesMelanges.pop_back();
    }
}
