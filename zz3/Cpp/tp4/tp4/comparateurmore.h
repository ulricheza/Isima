#ifndef COMPARATEURMORE_H
#define COMPARATEURMORE_H

#endif // COMPARATEURMORE_H

#include "classe.h"

class comparateurMore
{
    comparateurMore() {}

    bool operator() (const Classe &  a, const Classe & b)
    {
        return ( a.getMin() > b.getMin());
    }
};
