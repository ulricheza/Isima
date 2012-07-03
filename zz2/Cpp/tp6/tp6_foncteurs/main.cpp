/* 
 * File:   main.cpp
 * Author: escourbi
 *
 * Created on 22 décembre 2010, 16:29
 */

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "Rand_0_100.hpp"
#include "vect_affich.hpp"
#include "gene_alea.hpp"
#include "fibo.hpp"

using namespace std;

int main(int, char**) {

    srand(time(0));
    vector<int> vect1(10);
    vector<int> vect2(10);
    vector<int> vect3(10);
    vector<int> vect4(10);

    //initialisation du vecteur en utilisant l'algorithme standard generate
    generate(vect1.begin(),vect1.end(),Rand_0_100());
    generate_n(vect2.begin(),10,Rand_0_100());

    //affichage du vecteur en utilisant un for_each et un foncteur
    //vect_affich est en fait une reference sur une instance.
    for_each(vect1.begin(),vect1.end(),vect_affich());
    cout << endl;
    for_each(vect2.begin(),vect2.end(),vect_affich());
    cout << endl;
    //calcul de la moyenne des valeurs du vecteur 1
    cout << (float)std::accumulate(vect1.begin(),vect1.end(),0) / (float)vect1.size() << endl;;

    //geneteur de nombre entre un min et max
    generate(vect3.begin(),vect3.end(),gene_alea(250,280));
    for_each(vect3.begin(),vect3.end(),vect_affich());
    cout << endl;

    //fibonnacci
    generate(vect4.begin(),vect4.end(),fibo());
    for_each(vect4.begin(),vect4.end(),vect_affich());
    cout << endl;
    return (EXIT_SUCCESS);
}

