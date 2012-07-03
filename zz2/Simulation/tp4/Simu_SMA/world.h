/**
 * \file world.h
 * \brief fichier de declaration de la classe World
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 26 Janvier 2011
 * \version 1.0
 *
 */

#ifndef _WORLD_H
#define	_WORLD_H


#include <list>

class Position;
class Entite;

using namespace std;

/**
 * \class World
 * \brief Classe modelisant le monde ou evolueront les entites
 *
 */

class World {
public:
    //constructeurs
    World(int hauteur, int largeur);
    ~World();
    
    //methodes
    void AfficWorld();
    void AjouterEntite(int x, int y, Entite * inAdd);
    void ConvertisseurCase(Position & atest);
    void SupprimerEntite(int x, int y, Entite * inSuppr);
    
    
    //getters & setters
    list<Entite*> ** getMap(){return _map;}

private:
    int _hauteur;
    int _largeur;
    list<Entite*> ** _map;
};

#endif	/* _WORLD_H */

