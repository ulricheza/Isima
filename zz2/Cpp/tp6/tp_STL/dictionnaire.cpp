/* 
 * File:   dictionnaire.cpp
 * Author: escourbi
 * 
 * Created on December 1, 2010, 10:15 AM
 */

#include "dictionnaire.h"

Dictionnaire::Dictionnaire(){
}


Dictionnaire::~Dictionnaire() { 
}

void Dictionnaire::ajouter_mot(const string & mot)
{
    dico[mot[0]].ajouterMot(mot);
}

void Dictionnaire::supprimer_mot(const string & mot)
{
    dico[mot[0]].supprimerMot(mot);
}

list<string> Dictionnaire::rechercherMots(const string& mot)
{
    list<string> ret;
    ListeMots::iterator temp = dico[mot[0]].begin();
    while(temp != dico[mot[0]].end() && (*temp).find(mot,0) != 0 )
        ++temp;
    if(temp != dico[mot[0]].end())
    {
        while((*temp).find(mot,0) == 0){
            ret.push_back((*temp));
            ++temp;
        }
    }
    return ret;
}
