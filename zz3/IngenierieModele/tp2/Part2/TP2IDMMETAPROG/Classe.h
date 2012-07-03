/* 
 * File:   Classe.h
 * Author: maxime
 *
 * Created on 6 novembre 2011, 00:57
 */

#ifndef _CLASSE_H
#define	_CLASSE_H

#include <iostream>
#include <fstream>
#include "Attribut.h"
#include "Methode.h"
#include "Specialisation.h"


class Classe {
public:

    //Constructeurs et Destructeurs
    Classe();
    Classe(string name);
    virtual ~Classe();
    
    //Methodes
    string afficherAttributs();
    string afficherMethodes();
    string afficherAttributsStatiques();
    string afficherMethodesStatiques();
    
    void genererHppFile(string file);
    void genererJavaFile(string file);
    
    void addMethod( Methode * methode)       { _methodes.push_back(methode);}
    void addAttribut( Attribut * attribut)   { _attributs.push_back(attribut);}
    void addParent( Specialisation * parent) {_parents.push_back(parent);}

    //Getter et Setter
    string getName()            {return _name;}
    void   setName(string name) { _name = name;}

private:

    string                _name;
    list<Specialisation*> _parents;
    list<Attribut*>       _attributs;
    list<Methode*>        _methodes;
};

#endif	/* _CLASSE_H */

