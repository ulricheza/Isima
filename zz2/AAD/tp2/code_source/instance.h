/**
 * \file instance.h
 * \brief fichier d'en tete de la classe instance
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \version 1.0
 * \date Lundi 1 novembre 2010
 */

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include "graphe.h"

const float EPS = 0.000001f;

class instance
{
   public:
      int _nbMachine;
      int _nbJob;
      char _nom[10];
      graphe * _graph;
      int ** _ordreMachine;
      int ** _ordreJob;
      vector <sommet *> _sommetEntrantModif;
      vector <sommet *> _sommetSortantModif;

   public:
      instance(char * fichier);
      ~instance(void);
      void ajoutArcsVecteur(int * vecteur);
      void bellman();
      void supArc();
      int * gene_vecteur_alea();
      void recherche_locale(int * vecteur,int itermax);
      int * mutation(const int * tab);
      void croisementLOX(int *P1,int *P2, int **F1, int **F2);
      float getMakespan(){return _graph->V[1]->distance;}
};