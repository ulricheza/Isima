/**
 * \file graphe.h
 * \brief fichier de modelisation d'un graphe
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \version 1.0
 * \date Lundi 1 novembre 2010
 */

#ifndef __GRAPHE_H_MJC__
#define __GRAPHE_H_MJC__

#include <vector>
#include <list>

using std :: vector;
using std :: list;

struct sommet;
struct arc;

/*
 * \struct arc
 * \brief structure modelisant un arc
 */
struct arc{
	sommet * orig;
	sommet * dest;
	int duree;
};

/*
 * \struct sommet
 * \brief structure modelisant un sommet
 */
struct sommet
{
   int id_job;
   int id_machine;
   list<arc*> entree;
   list<arc*> sortie;
   // distance et sommet_restant sont des variables utilise pour bellman
   float distance; //distance du plus long chemin
   int sommet_restant;
   sommet * prec;
};

/*
 * \struct arc
 * \brief structure modelisant un graphe
 */
struct graphe
{
	vector<sommet *> V;
	vector<arc *> E;
};

#endif
