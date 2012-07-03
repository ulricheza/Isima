/**
 * \file entite.h
 * \brief fichier de declaration de la classe Entite
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 27 Fevrier 2011
 * \version 1.0
 *
 */

#ifndef _ENTITE_H
#define	_ENTITE_H

#include "position.h"

class Simulator;
class World;

/**
 * \class Entite
 * \brief Specialisation de la classe entite a une role fixe
 *
 */

class Entite {
public:
    Entite(int x, int y,Simulator * simu, World * world);
    virtual ~Entite() {}

    //methodes
    virtual void Afficher() = 0;

    //getters et setters
    int getForce() {return _force;}
    Position getPosition() {return _placement;}
    int getType() {return _type;}
    void setForce( int force) { _force = force;}

protected:
    int _force;
    int _type;
    Position _placement;
    Simulator * _simu;
    World * _world;
};

#endif	/* _ENTITE_H */

