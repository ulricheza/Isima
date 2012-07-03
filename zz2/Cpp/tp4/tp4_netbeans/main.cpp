/* 
 * File:   main.cpp
 * Author: escourbi
 *
 * Created on November 10, 2010, 10:55 AM
 */

#include <stdlib.h>
#include "vecteur.hxx"
#include "pile.hxx"

/*
 * 
 */
int main(int argc, char** argv) {

    int tab[3] = {1,2,3};
    Vecteur<int> A(tab,3);
    cout << A[0] << " " << A[1] << endl;
    cout << A;
    Vecteur<int> B;
    B.ajout_fin(0);
    B.ajout_fin(1);
    B.ajout_fin(2);
    B.ajout_fin(3);
    B.ajout_fin(4);
    B.ajout_fin(5);
    B.ajout_fin(6);
    return (EXIT_SUCCESS);
}

