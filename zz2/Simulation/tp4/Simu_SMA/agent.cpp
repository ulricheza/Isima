/**
 * \file Agent.cpp
 * \brief fichier d'implementation de la classe Agent
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 27 Fevrier 2011
 * \version 1.0
 *
 */

#include "agent.h"
#include "entite.h"
#include "world.h"
#include "simulator.h"
#include <iostream>
#include <list>

/**
 * Conventions pour les sens de deplacements:
 * 0 = Nord
 * 1 = Nord-Est
 * 2 = Est
 * 3 = Sud-Est
 * 4 = Sud
 * 5 = Sud-Ouest
 * 6 = Ouest
 * 7 = Nord-Ouest
 */

/**
 * \fn  Agent::Agent(int x,int y,Simulator * simu,World * world)
 * \brief constructeur de la classe abstraite agent
 * \param x coordonnee de placement initial
 * \param y coordonnee de placement initial
 * \param simu pointeur vers l'instance de simulation
 * \param world pointeur sur le monde ou sera contenu l'agent
 */

Agent::Agent(int x, int y, Simulator * simu, World * world):
Entite(x,y,simu,world)
{
    //aleatoire sur la case prec
    _prec = _simu->GeneInt(0,7);
}

/**
 * \fn void Agent::Deplacement(int inSens);
 * \brief effectue un deplacement d'un agent sur la map
 * \param inSens sens de deplacement 
 * 0 = Nord
 * 1 = Nord-Est
 * 2 = Est
 * 3 = Sud-Es
 * 4 = Sud
 * 5 = Sud-Ouest
 * 6 = Ouest
 * 7 = Nord-Ouest
 */

void Agent::Deplacement(int inSens)
{
    cout << "Deplacement de l'agent dans la direction: " << inSens << endl;
    //on supprime l'element du liste de la map
    _world->SupprimerEntite(_placement._x,_placement._y, this);

    //sauvegarde de l'emplacement
    _prec = (inSens + 4)%8;

    switch(inSens)
    {
        case 0: //nord
            --(_placement._y);
            break;
        case 1: //nordest
            --(_placement._y);
            ++(_placement._x);
            break;
        case 2: //est
            ++(_placement._x);
            break;
        case 3: //sudest
            ++(_placement._x);
            ++(_placement._y);
            break;
        case 4: //sud
            ++(_placement._y);
            break;
        case 5: //sudouest
            ++(_placement._y);
            --(_placement._x);
            break;
        case 6: //ouest
            --(_placement._x);
            break;
        case 7: //nordouest
            --(_placement._y);
            --(_placement._x);
            break;
        default:
            cerr << "Agent:Deplacement: Erreur dans le sens" << endl;
    }
    _world->ConvertisseurCase(_placement);
    //on place l'agent
    cout << "nouvelle position x: " << _placement._x << " y: " << _placement._y << endl;
    _world->AjouterEntite(_placement._x,_placement._y, this);
}


/**
 * \fn void Agent::Tuer(Agent * victime)
 * \brief cette fonction permet de tuer un Agent en le faisant disparaitre de la map et de la liste des agents
 * \param victime sur la victime
 */

void Agent::Tuer(Agent * victime)
{
    cout << "Procedure de meurtre d'un agent de type: " << victime->_type << endl;
    //on supprime l'humain de la liste de simulateur
    _simu->SupprAgent(victime);
}



