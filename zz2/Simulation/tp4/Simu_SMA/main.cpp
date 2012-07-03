/**
 * \file main.cpp
 * \brief fichier main du projet du simulateur
 * \author Maxime ESCOURBIAC Jean Christophe SEPTIER
 * \date 27 fevrier 2011
 * \version 1.0
 *
 */

#include <stdlib.h>
#include <iostream>

#include "simulator.h"
#include "agent.h"
#include "humain.h"
#include "arme.h"



using namespace std;

int main(int argc, char** argv) {

    int largeur;
    int hauteur;
    int nb_zombie;
    int nb_humain;
    int nb_arme;
    int delay;

    cout << "------------------------------------------" << endl;
    cout << "Simulation SMA Humain vs Zombie"            << endl;
    cout << "Tp de simulation numero 4"                  << endl;
    cout << "Maxime ESCOURBIAC Jean-Christophe SEPTIER"  << endl;
    cout << "------------------------------------------" << endl;

    cout << "Largeur?" << endl;
    cin >> largeur ;
    cout << "Hauteur?" << endl;
    cin >> hauteur ;
    cout << "nombre de zombie?" << endl;
    cin >> nb_zombie ;
    cout << "nombre d'humain?" << endl;
    cin >> nb_humain ;
    cout << "nombre d'arme" << endl;
    cin >> nb_arme;
    cout << "delay entre chaque operation?" << endl;
    cin >> delay;

    Simulator::Programme(largeur,hauteur,nb_zombie,nb_humain,nb_arme,delay);

    return(EXIT_SUCCESS);
}

