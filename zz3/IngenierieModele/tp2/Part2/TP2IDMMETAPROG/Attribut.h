/* 
 * File:   Attribut.h
 * Author: maxime
 *
 * Created on 5 novembre 2011, 23:13
 */

#ifndef _ATTRIBUT_H
#define	_ATTRIBUT_H

#include <string>
#include "Membre.h"

using namespace std;

/**
 * \class Attribut
 * \brief Classe representant un attribut de classe ou d'instance
 *
 */
class Attribut : public Membre{
public:

    //Constructeur et Destructeur
    Attribut();
    Attribut(string identificateur, string type, Accesibility access, unsigned char characteristics);
    virtual ~Attribut();

    //Methode
    virtual string toString();
};

#endif	/* _ATTRIBUT_H */

