/**
 * \file agent.h
 * \brief fichier de declaration de la classe agent
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 27 fevrier 2011
 * \version 1.0
 *
 */

#ifndef _AGENT_H
#define	_AGENT_H

#include "position.h"
#include "entite.h"

class Simulator;
class World;


/**
 * \class Agent
 * \brief classe abstraite qui regroupe tous les agents de la simulation
 *
 */

class Agent : public Entite
{
public:
    Agent(int x,int y,Simulator * simu, World * world);
    virtual ~Agent() {};

    virtual void Afficher() = 0;
    virtual void Tour()     = 0;
    virtual bool Action()   = 0;
    virtual bool Attaquer(Agent * cible) = 0;

    void         Deplacement(int sens);
    void         Tuer(Agent * cible);

protected:
    int _prec; // Modification due au monde torique
    int _vitesse;
};

#endif	/* _AGENT_H */

