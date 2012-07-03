/* 
 * File:   main.cpp
 * Author: escourbi
 *
 * Created on October 17, 2011, 2:31 PM
 */

#include <iostream>
#include <cstdlib>
#include <vector>

#include "cartesien.h"
#include "polaire.h"
#include "nuage.hxx"

using namespace std;
/*
 *
 */


int main(int argc, char** argv) {

    Cartesien cart(2.,2.);

    vector<Cartesien> vecteur;


    vecteur.push_back(cart);
    vecteur.push_back(cart);


    cout << "Premiere partie:" << endl;
    (vecteur.front()).afficher();
    (vecteur.back()).afficher();

    cout << "Seconde partie" << endl;

    Nuage<Cartesien> nuage;

    cout << "Insertion des points" <<endl;
    nuage.push_back(*(new Cartesien(1.,2.)));
    nuage.push_back(*(new Cartesien(4.,5.)));
    nuage.push_back(*(new Cartesien(-1.,2.5)));

    cout << "Calcul du barycentre" << endl;
    Cartesien result = nuage.calculBarycentre();

    cout << "Affichage du resultat" <<endl ;
    result.afficher();

    Nuage<Cartesien>::iterator it ;

    for( it = nuage.begin() ; it != nuage.end() ; it++)
    {
        cout << (*it) << endl;
    }

    return (EXIT_SUCCESS);
}

