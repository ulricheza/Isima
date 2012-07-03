      /**
 * \file Simulator.h
 * \brief fichier d'implementation de la classe Simulator
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 7 fevrier 2011
 * \version 1.0
 *
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "agent.h"
#include "arme.h"
#include "humain.h"
#include "mt19937ar.h"
#include "simulator.h"
#include "zombie.h"
#include "graphic.h"

using namespace std;

/**
 * \fn Simulator::Simulator(int largeur, int longueur, int nb_zombie, int nb_humain, int nb_arme)
 * \brief Constructeur de la classe Simulator
 * \param largeur largeur de la map
 * \param longueur longueur de la map
 * \param nb_zombie nombre de zombie initial
 * \param nb_humain nombre d'humain initial
 * \param nb_arme nombre d'arme initial
 */

Simulator::Simulator(int largeur, int hauteur, int nb_zombie, int nb_humain, int nb_arme)
{
    int i;
    int placementrestant;
    int tirage;
    int temp;

    //initialisation du monde
    _monde = new World(hauteur,largeur);

    //initialisation des variables
    _fin = false;

    //initialisation du generateur
    srand(time(0));
    init_genrand(rand());



    //initialisation du tableau pour placer aleatoirement les entite
    placementrestant = largeur*hauteur;
    int * tabalea = new int[placementrestant];
    for (i = 0; i < placementrestant; ++i)
    {
        tabalea[i] = i;
    }
    --placementrestant;

    //placement des zombie
    i = 0;
    while( i < nb_zombie)
    {
        tirage = GeneInt(0,placementrestant);
        temp = tabalea[tirage];
        tabalea[tirage] = tabalea[placementrestant];
        PlacementAgent(largeur,temp,0);
        --placementrestant;
        ++i;
    }

    //placement des humains
    i = 0;
    while(i < nb_humain)
    {
        tirage = GeneInt(0,placementrestant);
        temp = tabalea[tirage];
        tabalea[tirage] = tabalea[placementrestant];
        PlacementAgent(largeur,temp,1);
        --placementrestant;
        ++i;
    }

    //placement des armes
    i = 0;
    while(i < nb_arme)
    {
        tirage = GeneInt(0,placementrestant);
        temp = tabalea[tirage];
        tabalea[tirage] = tabalea[placementrestant];
        PlacementAgent(largeur,temp,2);
        --placementrestant;
        ++i;
    }
	delete[] tabalea;
}

/**
 * \fn Simulator::~Simulator()
 * \brief Destructeur de la classe Simulator
 *
 */

Simulator::~Simulator()
{
    //destruction du monde
    delete _monde;
    
    //destruction de la liste d'agent
    while(!_agent.empty())
    {
        delete _agent.front();
        _agent.pop_front();
    }

    //destruction de la liste des entites
    while(!_autre.empty())
    {
        delete _autre.front();
        _autre.pop_front();
    }
}

/**
 * \fn void Simulator::Programme(int largeur, int hauteur, int nb_zombie, int nb_humain,int nb_arme, int time_trans)
 * \brief Methode statique de lancement de la simulation
 * \param largeur largeur de la map
 * \param hauteur hauteur de la map
 * \param nb_zombie nombre de zombie initial
 * \param nb_humain nombre d'humain initial
 * \param nb_arme nombre d'arme initial
 * \param time_trans temps de transition entre chaque action de la simulation
 * 
 */
void Simulator::Programme(int largeur, int hauteur, int nb_zombie, int nb_humain,
                                 int nb_arme, int time_trans)
{
    //initialisation des variables
    Simulator * simu = new Simulator(largeur,hauteur,nb_zombie,nb_humain,nb_arme);
    Graphic * gui = new Graphic();
    Graphic::Initialisation(largeur,hauteur,time_trans,simu);
    simu->_monde->AfficWorld();

    cout << "Lancement de la simulation" << endl;
    
    while(! simu->_fin)
    {
        simu->TourSimulation();
        Graphic::Transition();
    }
    Graphic::LiberationRessource();
    delete gui;
    delete simu;
}
/**
 * \fn int Simulator::GeneInt(int min,int max)
 * \brief Generateur de nombre aleatoire entre min et max inclus
 * \param min borne minimale du tirage
 * \param max borne maximale du tirage
 * \return val un nombre aleatoire entre min et max inclus
 */

int Simulator::GeneInt(int min,int max)
{
    int val = genrand_int32() %(max-min + 1);
    val += min;
    return val;
}

/**
 * \fn void Simulator::PlacementAgent(int longu, int placement, int type)
 * \brief Initialise un agent dans l'instance de simulation
 * \param longu longueur du monde
 * \param placement coordonne 1D du placement de l'entite
 * \param type de l'entite a inserer
 *
 */

void Simulator::PlacementAgent(int longu, int placement, int type)
{
    int x,y;
    Entite * add;
    //transformation de la coordonnee 1D en coordonnees 2D

    y = placement / longu;
    x = placement - y*longu;

    switch(type) 
    {
        case 0: //creation de zombie
            add = new Zombie(x,y,this,_monde);
            //rajout a la liste d'agent
            _agent.push_back((Agent *)add);
            break;
        case 1: //creation d'humain
            add = new Humain(x,y,this,_monde);
            //rajout a la liste d'agent
            _agent.push_back((Agent *)add);
            break;
        case 2: //creation d'arme
            add = new Arme(x,y,this,_monde);
            //rajout a la liste d'arme
            _autre.push_back(add);
            break;
        default:
            cerr << "Simulator:PlacementInitAgent: type non reconnu" << endl;
    }
}

/**
 * \fn  void Simulator::SupprAgent(Agent * inSuppr)
 * \brief Supprime un agent de la liste
 * \param inSuppr pointeur sur l'agent a supprimer
 *
 */
void Simulator::SupprAgent(Agent * inSuppr)
{
    Position poseAgent = inSuppr->getPosition();
    
    //on supprime l'agent de la liste du simulateur
    _agent.remove(inSuppr);

    //on supprime l'element de la map
    _monde->SupprimerEntite(poseAgent._x, poseAgent._y, inSuppr);
    
    delete inSuppr;
}

/**
 * \fn  void Simulator::SupprAutre(Entite * inSuppr)
 * \brief Supprime une entite de la liste
 * \param inSuppr pointeur sur l'entite a supprimer
 *
 */
void Simulator::SupprAutre(Entite * inSuppr)
{
    Position poseAgent = inSuppr->getPosition();
    //on supprime l'entite de la liste du simulateur
    _autre.remove(inSuppr);

    //on supprime l'element de la map
    _monde->SupprimerEntite(poseAgent._x, poseAgent._y, inSuppr);

    delete inSuppr;
}


/**
 * \fn void Simulator::TourSimulation()
 * \brief effectue un tour de la simulation
 *
 */
void Simulator::TourSimulation()
{
    int i,tirage;
    int agent_restant;
    Agent * actif;
    list<Agent*>::iterator it = _agent.begin();
    //on effectue un ordre aleatoire pour les actions des agents
    //on construit un tableau de pointeur de tous les agents actifs
    agent_restant = _agent.size();
    Agent ** tab_alea = new Agent*[agent_restant];

    for(i=0; i<agent_restant; ++i)
    {
        tab_alea[i] = (*it);
        ++it;
    }

    while(agent_restant > 0)
    {
        tirage = GeneInt(0,agent_restant-1);
        actif = tab_alea[tirage];
        tab_alea[tirage] = tab_alea[agent_restant - 1];
        --agent_restant;
        //il faut tester la presence de l'agent dans le pool d'agent actif
        if( RechAgent(actif))
        {
            actif->Tour();
        }
        Graphic::TransitionTourSimulation();
    }
    delete[] tab_alea;
}

/**
 * \fn void Simulator::AjoutAgent( Agent * inAdd)
 * \brief ajoute un agent dans la pool
 * \param inAdd agent a ajouter
 *
 */

void Simulator::AjoutAgent(Agent* inAdd)
{
    _agent.push_back(inAdd);
}

/**
 * \fn bool Simulator::RechAgent(Agent * inRech)
 * \brief permet de savoir si l'agent est toujours parmi le pool d'agent du simulateur
 * \return true si l'agent est dans le pool
 * \param inRech agent a chercher
 *
 */

bool Simulator::RechAgent(Agent * inRech)
{
    list<Agent*>::iterator it = _agent.begin();

    while( it != _agent.end() && (*it) != inRech)
        ++it;

    return(!(it == _agent.end()));
}

/**
 * \fn void Simulator::FinSimu()
 * \brief fonction qui signifie a l'instance de simulation qu'elle doit s'arreter
 *
 */

void Simulator::FinSimu()
{
    cout << "L'arret de la simulation ete demande" << endl;
    _fin = true;
}