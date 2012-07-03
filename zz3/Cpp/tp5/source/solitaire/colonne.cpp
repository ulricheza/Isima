#include "colonne.h"

Colonne::Colonne()
{
}

Carte * Colonne::getSommet()
{
    Carte * result = NULL;
    if(!_cartesVisibles.empty())
    {
        result = _cartesVisibles.back();
    }
    return result;
}

Carte * Colonne::getCarte( int position)
{
    Carte * result = NULL;
    list<Carte*>::iterator it = _cartesVisibles.end();

    if( position < (int)_cartesVisibles.size())
    {
        for(int i = 0; i <= position; ++i)
            --it;
        result = (*it);
    }

    return result;
}

Carte * Colonne::getCarte( int position) const
{
    Carte * result = NULL;
    list<Carte*>::const_iterator it = _cartesVisibles.end();

    if( position < (int)_cartesVisibles.size())
    {
        for(int i = 0; i <= position; ++i)
            --it;
        result = (*it);
    }

    return result;
}

void Colonne::ajouter(Main &main)
{
    int tailleMain = main.size();

    for(int i = 0; i < tailleMain; ++i)
    {
        _cartesVisibles.push_back(main[i]);
    }
}

void Colonne::ajouter(Carte *carte)
{
    if(!_cartesVisibles.empty())
    {
        Carte * sup = _cartesVisibles.back();

        if(sup->getValeur() == carte->getValeur()-1)
        {
            if(sup->estNoir() && carte->estRouge())
            {
                _cartesVisibles.push_back(carte);
            }
            else
            {
                if(carte->estNoir() && sup->estRouge())
                {
                    _cartesVisibles.push_back(carte);
                }
            }
        }
    }
    else
    {
        _cartesVisibles.push_back(carte);
    }
}


void Colonne::retirer(int pos, Main &main)
{
    if(pos < (int)_cartesVisibles.size())
    {
        for(int i = 0; i < pos ; ++i)
        {
            main.push_back(_cartesVisibles.back());
            _cartesVisibles.pop_back();
        }
    }
}

void Colonne::retourner()
{
    if(_cartesVisibles.empty())
    {
        if(!_cartesCachees.empty())
        {
            _cartesVisibles.push_back(_cartesCachees.back());
			_cartesCachees.pop_back();
        }
    }
}
