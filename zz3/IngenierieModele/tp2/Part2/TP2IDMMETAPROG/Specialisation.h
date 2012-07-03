/* 
 * File:   Specialisation.h
 * Author: maxime
 *
 * Created on 6 novembre 2011, 01:11
 */

#ifndef _SPECIALISATION_H
#define	_SPECIALISATION_H


#include "Membre.h"

//Predeclaration
class Classe;

class Specialisation {
public:
    Specialisation();
    Specialisation(Classe * classe, Accesibility access);
    virtual ~Specialisation();

    //Getters & setters
    void         setClasse(Classe * classe)     { _classe = classe;}
    void         setAccess(Accesibility access) { _access = access; }
    Classe *     getClasse()                    { return _classe; }
    Accesibility getAccess()                    {return _access;}

private:

    Classe *     _classe;
    Accesibility _access;

};

#endif	/* _SPECIALISATION_H */

