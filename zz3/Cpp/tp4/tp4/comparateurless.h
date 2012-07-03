#ifndef COMPARATEURLESS_H
#define COMPARATEURLESS_H

#endif // COMPARATEURLESS_H

#include "classe.h"

class comparateurLess
{
public:
    comparateurLess() {}

    bool operator() (const Classe &  a, const Classe & b)
    {
        return ( a.getMin() < b.getMin());
    }
};
