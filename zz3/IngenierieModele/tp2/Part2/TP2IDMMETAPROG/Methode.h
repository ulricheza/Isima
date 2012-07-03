/* 
 * File:   Methode.h
 * Author: maxime
 *
 * Created on 5 novembre 2011, 23:55
 */

#ifndef _METHODE_H
#define	_METHODE_H

#include <list>
#include "Membre.h"


using namespace std;

/**
 * \class Methode
 * \brief Classe de modelisation d'une classe en C++
 *
 */
class Methode : public Membre{
public:

    //Constructeur et destructeur
    Methode();
    Methode(string identificateur, string type, Accesibility acces, unsigned char characteristics, list<string> & parametres );
    virtual ~Methode();

    //Methodes
    virtual string toString();
    bool isPureVirtual() { return
                            ((_characteristics & M_PURE_VIRTUAL) == M_PURE_VIRTUAL);
                         } //teste si la methode est virtuelle pure
    bool isVirtual()     { return
                            ((_characteristics & M_VIRTUAL) == M_VIRTUAL);
                         } //teste si la methode est virtuelle

    //getters et setters
    list<string> & getParametres()                          {return _parametres;}
    void           setParametres(list<string> & parametres) { _parametres = parametres;}

private:
    list<string> _parametres;
};

#endif	/* _METHODE_H */

