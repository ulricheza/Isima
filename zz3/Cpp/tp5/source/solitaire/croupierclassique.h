#ifndef CROUPIERCLASSIQUE_H
#define CROUPIERCLASSIQUE_H

#include "croupier.h"
class CroupierClassique : public Croupier
{
public:
    CroupierClassique();    
    virtual void melanger(Paquet & paquet);
};

#endif // CROUPIERCLASSIQUE_H
