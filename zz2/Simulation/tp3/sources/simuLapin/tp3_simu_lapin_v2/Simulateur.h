/**
 * \file simulateur.h
 * \author Maxime ESCOURBIAC Jean Christophe SEPTIER
 * \brief Fichier d'en tete de la classe simulateur
 * \version 2.0
 * \date 15 decembre 2010
 */



#ifndef __SIMULATEUR_H__
#define __SIMULATEUR_H__

#include <list>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Lapin.h"
#include "mt19937ar.h"

using namespace std;

/**
 * \class Simulateur
 * \brief Contient tous les elements pour gerer la simulation
 */
class Lapin;

class Simulateur {
 public:
    Simulateur();
    ~Simulateur() {}
    int    gene_int(int modulo)const;
    int    gene_porte_annee()  const;
    int    gene_lapin_portee() const;
    int    duree_vie_annee()   const;
    int    duree_vie_mois()    const;
    int    male_femelle()      const;
    void   gestion_mois();
    void   initialiser_simu();
    void   purger_simu();
    void   addLapin(bool ismale);
    int    getTemps() {return temps;}
    void   incrementer_temps() { ++temps;}

 protected:
    int _it_lapinfemelle; //sert d'iterateur pour le pool de lapin femelle
    int _it_lapinmale;    //sert d'itérateur pour le pool de lapin male
    list<Lapin *> _Lapin; //Pour travailler seulement sur les lapins vivants
    int temps;
};

#endif // Simulateur_h
