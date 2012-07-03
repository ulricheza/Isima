/**
 * \file humain.h
 * \brief fichier de declaration de la classe Humain
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 27 Fevrier 2011
 * \version 1.0
 *
 */


#ifndef _HUMAIN_H
#define	_HUMAIN_H

#include "agent.h"


/**
 * \class Humain
 * \brief Classe representant les humains, herite de la classe abstraite Agent
 *
 */

class Humain : public Agent {
public:
    
    Humain(int x,int y,Simulator * simu, World * world);
    virtual ~Humain() {}

    //methodes
    virtual bool Action();
    virtual bool Attaquer(Agent * cible);
    virtual void Afficher();
    virtual void Tour();

    bool PerceptionAuditive();
    bool PerceptionVisuelle();
    int  CalculSensPerception();
    
private:
    int _percept_aud_prim;
    int _percept_aud_sec;
    int _percept_vis_prim;
    int _percept_vis_sec;

};

#endif	/* _HUMAIN_H */

