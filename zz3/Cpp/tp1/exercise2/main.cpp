/* 
 * File:   main.cpp
 * Author: maxime
 *
 * Created on 11 octobre 2011, 14:10
 */

#include <stdlib.h>
#include <iostream>

#include "Vecteur.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {
    
    Vecteur vect(2);

    cout << "Test du code de la question 1" << endl;

    cout << "Test insertion" << endl;
    vect.push_back(0);
    vect.push_back(1);
    cout << "Test Insertion Vecteur plein" << endl;
    vect.push_back(2);

    cout << "Size: " << vect.size() << "Max size: " << vect.max_size() << endl;

    cout << "Front: " << vect.front() << "Back: " << vect.back() << endl;

    cout << "Test pop" << endl;
    vect.pop_back();
    cout << "Back: " << vect.back() << endl;

    cout << "Test pop_back sur vecteur vide" << endl;
    vect.pop_back();
    vect.pop_back();
    vect.pop_back();

    cout << "Test sur la concatenation de deux vecteur" << endl;

    Vecteur vect1(10);
    Vecteur vect2(10);

    vect1.push_back(0);
    vect1.push_back(1);
    vect1.push_back(2);
    vect2.push_back(3);
    vect2.push_back(4);
    vect2.push_back(5);

    Vecteur vect3 = vect1 + vect2;

    cout << "Test de la surcharge d'operateur <<" << endl;
    cout << vect3 << endl;

    cout << "Test de la surcharge de l'operateur [] en lecture" << endl;
    cout << vect3[2] << endl;

    cout << "Test de la surcharge de l'operateur [] en ecriture" << endl;
    vect3[2] = 42;
    cout << vect3[2] << endl;
    
    cout << "Test sur le produit scalaire" << endl;
    cout << "Produit scalaire de vect1 et vect2: " << (vect1 * vect2) << endl;

    cout << "Test sur les iterateur" << endl;
    Iterator it1 = vect3.begin();
    Iterator it2 = vect3.end();

    cout << "it1: " << *(it1) << " it2: " << *(it2) <<endl;

    cout << "it1: " << *(it1++) << endl;
    cout << "it1: " << *(it1)   << endl;

    cout << "it1: " << *(++it1) << endl;
    cout << "it1: " << *(it1)   << endl;



    return (EXIT_SUCCESS);
}

