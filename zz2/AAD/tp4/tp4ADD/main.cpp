/*
 * \file main.cpp
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \brief TP4 AAD Heuristiques pour le PDPTW
 * \version 1.0
 * \date 7 janvier 2011
 */


#include <iostream>
#include <cstdlib>

#include "Program.h"

using namespace std;
  
int main(int argc , char** argv ) {

    if(argc == 2){
        Program p;
        srand(time(0));
        p.LireFichier("lc101.txt");
        for(int i=0;i<20;++i){
            chromosome *c= p.algoGenetique();
            cout << "Vehicule= " << c->_vehiculeutilise << " Distance = " << c->_dureetournee << endl;
    
        }
    }
    else
        cout << " Probleme argument" << endl;
    return (EXIT_SUCCESS);
}

