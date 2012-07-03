/**
 * \file entite.h
 * \brief fichier d'implementation de la classe Entite
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 27 Fevrier 2011
 * \version 1.0
 *
 */

#include "entite.h"

/**
 * \fn  Entite::Entite(int x, int y, Simulator * simu,World * world)
 * \brief Constructeur de la classe Entite
 * \param x     coordonnee de placement initial
 * \param y     coordonnee de placement initial
 * \param simu  pointeur vers l'instance de simulation
 * \param world pointeur sur le monde ou sera contenu l'agent
 *
 */

Entite::Entite(int x, int y, Simulator * simu,World * world):_simu(simu),
                                                             _world(world)
{
    _placement._x = x;
    _placement._y = y;
}


