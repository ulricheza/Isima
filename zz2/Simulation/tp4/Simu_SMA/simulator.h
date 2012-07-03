/**
 * \file Simulator.h
 * \brief fichier de declaration de la classe Simulator
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 7 fevrier 2011
 * \version 1.0
 *
 */

#ifndef _SIMULATOR_H
#define	_SIMULATOR_H

#include "world.h"
#include "entite.h"
#include <list>

class World;
class Entite;
class Agent;

using namespace std;

/**
 * \class Simulator
 * \brief classe principale du simulateur elle coordonne tous les elements
 *
 */

class Simulator {
public:
    Simulator(int largeur, int hauteur, int nb_zombie, int nb_humain, int nb_arme);
    ~Simulator();

    void AjoutAgent(Agent * inAdd);
    int  GeneInt(int min,int max);
    void FinSimu();
    void PlacementAgent(int longu, int placement, int type);
    bool RechAgent(Agent * inRech);
    void SupprAgent(Agent * inSuppr);
    void SupprAutre(Entite * inSuppr);
    void TourSimulation();

    static void Programme(int largeur, int hauteur, int nb_zombie, int nb_humain,
                          int nb_arme, int time_trans);

private:
    bool _fin;
    World * _monde;
    list<Agent *> _agent;
    list<Entite *> _autre;
};

#endif	/* _SIMULATOR_H */

