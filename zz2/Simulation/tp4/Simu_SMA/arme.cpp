/**
 * \file arme.cpp
 * \brief fichier d'implementation de la classe Arme
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 27 Fevrier 2011
 * \version 1.0
 *
 */

#include "arme.h"
#include "simulator.h"
#include "graphic.h"


/**
 * \fn Arme::Arme(int x, int y, Simulator * simu,World * world)
 * \brief Constructeur de la classe Arme
 * \param x     coordonnee de placement initial
 * \param y     coordonnee de placement initial
 * \param simu  pointeur vers l'instance de simulation
 * \param world pointeur sur le monde ou sera contenu l'agent
 *
 */

Arme::Arme(int x,int y,Simulator * simu, World * world):
Entite(x, y, simu, world)
{
    //la force d'une arme peut varier de 1 a 5
    _force = _simu->GeneInt(1,5);
    _type = 2;
    //rajout au monde
    world->AjouterEntite(x,y,this);
}

/**
 * \fn void Arme::Afficher()
 * \brief fonction qui encapsule une fonction d'affichage de la classe Graphics
 *
 */

void Arme::Afficher()
{
    Graphic::AfficherArme(_placement._x,_placement._y);
}

