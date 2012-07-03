#include "pioche.h"

Pioche::Pioche()
{
}

bool Pioche::tirer()
{
    bool result = _cartesCachees.empty();

    if(result)
    {
        _cartesVisibles.push(_cartesCachees.top());
        _cartesCachees.pop();
    }

    return result;
}

Carte * Pioche::retirer()
{
    Carte * carte = _cartesVisibles.top();
    _cartesVisibles.pop();
    return carte;
}

Carte * Pioche::getProchaine()
{
    return (_cartesCachees.empty())? NULL :_cartesCachees.top();
}

Carte * Pioche::getProchaine() const
{
    return (_cartesCachees.empty())? NULL :_cartesCachees.top() ;
}
