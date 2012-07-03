/**
 * \file zombie.h
 * \brief fichier de declaration de la classe Zombie
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 26 Janvier 2011
 * \version 1.0
 *
 */

#ifndef _ZOMBIE_H
#define	_ZOMBIE_H

#include "agent.h"

class Simulator;
class World;

/**
 * \class Zombie
 * \brief Classe representant les zombies, herite de la classe abstraite Agent
 *
 */
class Zombie : public Agent {
public:
    Zombie(int x,int y,Simulator * simu, World * world);
    virtual ~Zombie() {}

    virtual bool Action();
    virtual void Afficher() ;
    virtual bool Attaquer(Agent * cible);
    virtual void Tour();
    
    void Contaminer();
    void PerceptionOlfactive();

private:
    int _percept_olf_prim;
    int _percept_olf_sec;
};

#endif	/* _ZOMBIE_H */

