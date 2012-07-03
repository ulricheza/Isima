#include "croupierclassique.h"

#include <cstdlib>
#include <ctime>

CroupierClassique::CroupierClassique()
{
    srand(time(NULL));
}


void CroupierClassique::melanger(Paquet &paquet)
{
    Carte * carte = paquet.getSuivante();

    while(carte != 0)
    {
        if(rand()%2 == 0)
        {
            _cartesMelanges.push_back(carte);
        }
        else
        {
            _cartesMelanges.push_front(carte);
        }
        paquet.getSuivante();
    }
}
