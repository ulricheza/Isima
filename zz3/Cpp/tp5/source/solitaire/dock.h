#ifndef DOCK_H
#define DOCK_H

#include <stack>
#include <carte.hpp>

using std::stack;

class Dock
{
public:
    Dock();

    bool    estVide()              { return _dock.empty(); }
    void    ajouter(Carte * carte) { _dock.push(carte); }
    Carte * getSommet()            { return (_dock.empty()? NULL : _dock.top()); }
    Carte * getSommet() const      { return (_dock.empty()? NULL : _dock.top()); }
    Carte * retirer();

private:
    stack<Carte*> _dock;
};

#endif // DOCK_H
