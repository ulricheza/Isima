/*
 * \file Program.h
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \brief fichier de declaration de la classe Program
 * \version 1.0
 * \date 7 janvier 2011
 */

#ifndef _PROGRAM_H
#define	_PROGRAM_H

#include <list>
#include <vector>
#include "Point.h"


using namespace std;

class Vehicule;
class Lieu;
class Tournee;
class Requete;

//structure de stockage
struct chromosome {
    list<Requete*> _liste;
    int _dureetournee;
    int _vehiculeutilise;
};

struct arc
{
    int i;
    int j;
    int gain;
    Requete *ri;
    Requete *rj;
};

class Program {
public:

    virtual ~Program();
    //methodes
    int  Calcul_dist(Point a, Point b);
    void HeuInsertion(chromosome * gene);
    void LireFichier(char * fichier);
    int  SommeDistance();
    chromosome * Savings();
    void VarianteHeuInsertion(chromosome * gene);
    chromosome * generateChromosome();
    chromosome * algoGenetique();
    void croisementLOX(chromosome *P1,chromosome *P2, chromosome **F1, chromosome **F2);
    bool RechercheVal(list<Requete*> *r, Requete * val);
    chromosome * mutation(chromosome *r);
    //predicat
    friend bool Predicat_suppr(Requete * test);

    //getters
    vector<Lieu*> * getLieu() {return &_lieu;}

public:
    int _temps;
    int _lieuactuel;
    vector<Lieu*>  _lieu;
    list<Tournee*> _tournee; //sert de liste de calcul pour une heuristique
    list<Requete*> _requete;
    list<chromosome *> _population;
};
#endif	/* _PROGRAM_H */
