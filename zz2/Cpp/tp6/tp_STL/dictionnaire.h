/* 
 * File:   dictionnaire.h
 * Author: escourbi
 *
 * Created on December 1, 2010, 10:15 AM
 */

#ifndef _DICTIONNAIRE_H
#define	_DICTIONNAIRE_H

#include "listemots.h"
#include <string>
#include <map>

class Dictionnaire {
private:
    map<char, ListeMots> dico;
public:
    Dictionnaire();
    virtual ~Dictionnaire();
    void ajouter_mot(const string & mot);
    void supprimer_mot(const string  & mot);
    int getNbElement() const {return dico.size();}
    list<string> rechercherMots(const string & mot);
};

#endif	/* _DICTIONNAIRE_H */

