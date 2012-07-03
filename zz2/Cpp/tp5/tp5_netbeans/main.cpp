/* 
 * File:   main.cpp
 * Author: escourbi
 *
 * Created on November 17, 2010, 10:36 AM
 */

#include "liste.h"
#include <iostream>

using namespace std;
/*
 * 
 */
int main(int, char**) {

    List<int> maliste;
    ItList<int> iter1;
    ItList<int> iter2;


    //test de la fonction push_back
    maliste.push_back(0);
    maliste.push_back(1);
    maliste.push_front(-1);
    maliste.push_back(2);
    maliste.push_back(3);

    //test sur les iterateurs
    iter1 = maliste.begin();
    cout << *iter1;
    iter1++;
    cout << *iter1;
    ++iter1;
    cout << *iter1;

    cout << endl;
    iter2 = maliste.find(2);
    cout << *iter2;
    maliste.remove(iter2);
    maliste.clear();
  

    return (EXIT_SUCCESS);
}

