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

using namespace std;

int main(int, char**) {

    Simulateur sim;
    int duree_simu;
    sim.initialiser_simu();
    srand(0);//time(0));
    
    printf("Quelle est la duree de la simulation en mois?\n");
    scanf("%d",&duree_simu);
    
    while(sim.getTemps()<duree_simu)
    {
        cout << "---------------------------" << endl;
        cout << " mois " << sim.getTemps() << endl;
        sim.gestion_mois();
        sim.incrementer_temps();
        printf("Lapins Male crees: %d \n", LapinMale::getLapinMaleCree());
        printf("Lapins Male vivants: %d \n",
                LapinMale::getLapinMaleVivant());
        printf("Lapins Femelle crees %d \n",
                LapinFemelle::getLapinFemelleCree());
        printf("Lapins Femelle vivants: %d \n",
                LapinFemelle::getLapinFemelleVivant());
    }
    return (EXIT_SUCCESS);
}

