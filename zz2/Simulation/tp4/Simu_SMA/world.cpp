/**
 * \file world.h
 * \brief fichier d'implementation de la classe World
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 26 Janvier 2011
 * \version 1.0
 *
 */

#include <iostream>

#include "world.h"
#include "graphic.h"
#include "position.h"
#include "entite.h"

/**
 * \fn World::World(int haut, int longu)
 * \brief Constructeur de la classe World
 * \param haut definit le nombre de case sur y
 * \param longu definit le nombre de case sur x
 *
 */

World::World(int haut, int larg): _hauteur(haut),_largeur(larg)
{
   _map= new  list<Entite*>*[_largeur];

   for(int i=0;i<_largeur;++i)
      _map[i]=new list<Entite*>[_hauteur];

}

/**
 * \fn World::~World()
 * \brief Destructeur de la classe World
 *
 */
World::~World()
{
    for(int i = 0 ; i < _largeur ; ++i)
    {
        for(int j = 0 ; j < _hauteur ; ++j)
        {
            _map[i][j].clear();
        }
        delete[] _map[i];
    }
    delete[] _map;
}


/**
 * \fn void World::ConvertisseurCase(Position & atest)
 * \brief Permet de gerer le monde ouvert ( monde torique)
 * \param atest reference sur la case a tester et eventuellement a modifier
 *
 */

void World::ConvertisseurCase(Position & atest)
{
    //convertir sur x
    if(atest._x < 0)
    {
        atest._x = _largeur + atest._x;
    }
    else
    {
        if(atest._x >= _largeur)
            atest._x = atest._x - _largeur;
    }

    //convertir sur y
    if(atest._y < 0)
    {
        atest._y = _hauteur + atest._y;
    }
    else
    {
        if(atest._y >= _hauteur)
        {
            atest._y = atest._y - _hauteur;
        }
    }
}

/**
 * \fn void World::AfficWorld()
 * \brief methode d'affichage du monde
 *
 */

void World::AfficWorld()
{
    int i,j;

    Graphic::AfficherBackground();

    for(j = 0 ; j < _hauteur ; ++j)
    {
        for(i = 0 ; i < _largeur ; ++i)
        {
            if(!_map[i][j].empty())
            {
                switch( _map[i][j].back()->getType())
                {
                    case 0: //un zombie a afficher
                        Graphic::AfficherZombie(i,j);
                        break;
                    case 1:
                        Graphic::AfficherHumain(i,j);
                        break;
                    case 2:
                        Graphic::AfficherArme(i,j);
                        break;
                    default:
                        std::cerr << "AfficWorld:Entite non reconnue" << std::endl;
                }
            }
        }
    }
    Graphic::Rafraichir();
}

/**
 * \fn void World::AjouterEntite(int x, int y , Entite * inAdd)
 * \brief ajoute une entite sur la map
 * \param x coordonne de l'entite a rajouter
 * \param y coordonne de l'entite a rejouter
 * \param inAdd pointeur sur l'entite a ajouter
 *
 */

void World::AjouterEntite(int x, int y, Entite * inAdd)
{
    _map[x][y].push_back(inAdd);
}

/**
 * \fn void World::SupprimerEntite(int x, int y , Entite * inSuppr)
 * \brief supprime une entite sur la map
 * \param x coordonne de l'entite a rajouter
 * \param y coordonne de l'entite a rejouter
 * \param inSuppr pointeur sur l'entite a ajouter
 *
 */

void World::SupprimerEntite(int x, int y, Entite * inAdd)
{
    _map[x][y].remove(inAdd);
}


