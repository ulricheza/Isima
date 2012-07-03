#include "histogramme.h"

Histogramme::Histogramme()
{
}

void Histogramme::constructionEchantillion(const Echantillon & echantillon)
{
    int nb = echantillon.getSize();

    for(int i = 0; i < nb ; ++i)
    {
        _classes.insert(Classe(i,i+1,echantillon[i]->getValeur()));
    }
}
