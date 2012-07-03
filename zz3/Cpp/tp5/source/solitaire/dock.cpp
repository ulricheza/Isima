#include "dock.h"

Dock::Dock()
{
}

Carte * Dock::retirer()
{
    Carte * carte = 0;
    if(_dock.empty())
    {
	   carte = _dock.top();
       _dock.pop();
	}
    return carte;
}
