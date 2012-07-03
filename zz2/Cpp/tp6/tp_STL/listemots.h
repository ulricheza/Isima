/* 
 * File:   listemots.h
 * Author: escourbi
 *
 * Created on December 1, 2010, 10:22 AM
 */

#ifndef _LISTEMOTS_H
#define	_LISTEMOTS_H

#include <list>
#include <string>
using namespace std;

class ListeMots {
private:
    list<string> maliste;
public:
    //creation d'une interface dans le cas ou on change de type de donnee
    typedef list<string>::iterator iterator;
    typedef list<string>::const_iterator const_iterator;
    
    ListeMots();
    virtual ~ListeMots();
    void ajouterMot(const string & mot);
    void supprimerMot(const string & mot);
    void insert(list<string>::iterator &, list<string>::iterator &);
    int getNbElement()             {return maliste.size();}
    list<string>::iterator begin() {return maliste.begin();}
    list<string>::iterator end()   {return maliste.end();}
    list<string>::const_iterator begin() const {return maliste.begin();}
    list<string>::const_iterator end()   const {return maliste.end();}
};

#endif	/* _LISTEMOTS_H */
