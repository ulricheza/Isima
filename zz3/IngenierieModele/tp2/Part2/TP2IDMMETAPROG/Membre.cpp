/* 
 * File:   Membre.cpp
 * Author: maxime
 * 
 * Created on 5 novembre 2011, 22:35
 */

#include "Membre.h"

Membre::Membre() {
}

Membre::Membre(string id, string type, Accesibility acces, unsigned char characteristics)
{
    _id              = id;
    _type            = type;
    _acces           = acces;
    _characteristics = characteristics;
}

Membre::~Membre() {
}

