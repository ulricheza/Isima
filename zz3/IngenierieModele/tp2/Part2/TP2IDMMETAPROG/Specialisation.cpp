/* 
 * File:   Specialisation.cpp
 * Author: maxime
 * 
 * Created on 6 novembre 2011, 01:11
 */

#include "Specialisation.h"
#include "Classe.h"

Specialisation::Specialisation() {
}

Specialisation::Specialisation(Classe* classe, Accesibility access):
_classe(classe),_access(access)
{
}

Specialisation::~Specialisation() {
}

