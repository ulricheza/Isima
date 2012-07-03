/**
 * \file main.cpp
 * \author Maxime ESCOURBIAC Jean Christophe SEPTIER
 * \brief Fichier main du tp 3 de simulation
 * \date 22 novembre 2010
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Lapin.h"
#include "Simulateur.h"
#include "math.h"

using namespace std;

int main(int, char**) {

    Simulateur sim;
    double result[1000];
    double moyenne  = 0.0;
    double variance = 0.0;
    double ecart_type;
    double rayon;
    int i;

    cout << "********Simulation de reproduction des Lapins*********" << endl;
    cout << "1000 replications avec au depart 5 males et 5 femelles" << endl;
    cout << "******************************************************" << endl;

    //Pour le compte rendu on effectuera des experiences de 60mois(5ans) avec
    //comme elevage de depart 5 nouveaux ne de chaque sexe que l'on repetera
    //1000 fois.
    //Pour les chiffres on retiendra juste le nombre de lapins quelquesoit leur
    //sexe.
    for(i=0;i<1000;++i)
    {
        sim.initialiser_simu(); //RAZ des compteurs de l'experience
    
        while(sim.getTemps()<42)
        {
            sim.gestion_mois();
            sim.incrementer_temps();
        }
        result[i] = (double)(Lapin::nb_femelle_vivante() + Lapin::nb_male_vivant());
        moyenne += result[i]/1000.0;
        sim.purger_simu();
    }
    cout << "moyenne: " << moyenne << endl;

    //calcul de la variance
    for(i=0;i<1000;++i)
    {
        variance += (result[i]-moyenne)*(result[i]-moyenne);
    }
    variance /= 1000.0;
    ecart_type = sqrt(variance);
    cout << "Ecart type " << ecart_type << endl;

    //calcul du rayon de l'intervalle de confiance a 0.05
    //1.960 valeur obtenu dans l'annexe
    rayon = 1.960 * sqrt(variance/1000.0);
    cout << "rayon " << rayon << endl;


    return (EXIT_SUCCESS);
}

