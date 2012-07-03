/* 
 * File:   listemots.cpp
 * Author: escourbi
 * 
 * Created on December 1, 2010, 10:22 AM
 */

#include "listemots.h"

ListeMots::ListeMots() {
}

ListeMots::~ListeMots() {
    maliste.clear();
}

void ListeMots::ajouterMot(const string & mot)
{
    maliste.push_back(mot);
    maliste.sort();
}

void ListeMots::supprimerMot(const string & mot)
{
    maliste.remove(mot);
}

void ListeMots::insert(list<string>::iterator & deb, list<string>::iterator & fin)
{
    maliste.insert(maliste.end(),deb,fin);
    maliste.sort();
}

