/* 
 * File:   main.cpp
 * Author: escourbi
 *
 * Created on October 10, 2011, 1:40 PM
 */

#include <iostream>
#include <stdlib.h>
#include <vector>

#include "cartesien.h"
#include "polaire.h"
#include "nuage.h"

using namespace std;
/*
 * 
 */

int main(int argc, char** argv) {

    Cartesien cart(2.,2.);
    Polaire   pol(1.,1.55);

    vector<Point*> vecteur;


    vecteur.push_back(&cart);
    vecteur.push_back(&pol);

    
    cout << "Premiere partie:" << endl;
    (vecteur.front())->afficher();
    (vecteur.back())->afficher();

    cout << "Seconde partie" << endl;

    Nuage nuage;

    cout << "Insertion des points" <<endl;
    nuage.push_back(new Cartesien(1.,2.));
    nuage.push_back(new Cartesien(4.,5.));
    nuage.push_back(new Cartesien(-1.,2.5));
    nuage.push_back(new Polaire(1.,1.));
    nuage.push_back(new Polaire(0.5,0.5));

    cout << "Calcul du barycentre" << endl;
    Cartesien result = nuage.calculBarycentre();

    cout << "Affichage du resultat" <<endl ;
    result.afficher();

    return (EXIT_SUCCESS);
}

