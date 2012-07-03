/**
 * \file simulateur.h
 * \author Maxime ESCOURBIAC Jean Christophe SEPTIER
 * \brief Fichier d'en tete de la classe simulateur
 * \date 22 novembre 2010
 */



#ifndef __SIMULATEUR_H__
#define __SIMULATEUR_H__

#include <list>
#include <cstdio>
#include <cstdlib>
#include "Lapin.h"


using namespace std;

/**
 * \class Simulateur
 * \brief Contient tous les elements pour gerer la simulation
 */
class Lapin;

class Simulateur {

 public:
    Simulateur();
    ~Simulateur();
    float gene_rand()         const;
    int   gene_porte_annee()  const;
    int   gene_lapin_portee() const;
    int   duree_vie_annee()   const;
    int   duree_vie_mois()    const;
    int   male_femelle()      const;
    void  gestion_mois();
    void  initialiser_simu();
    void  addLapin(Lapin * ajout) { _Lapin.push_back(ajout);}
    int   getTemps() {return temps;}
    void  incrementer_temps() { ++temps;}

 protected:
    int temps;
    list<Lapin*>_Lapin;

};

#endif // Simulateur_h
