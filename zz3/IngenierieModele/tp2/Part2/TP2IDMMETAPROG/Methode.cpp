/* 
 * File:   Methode.cpp
 * Author: maxime
 * 
 * Created on 5 novembre 2011, 23:55
 */

#include "Methode.h"

Methode::Methode() {
}

Methode::Methode(string identificateur, string type, Accesibility acces, unsigned char caracteristique, list<string> & parametres)
: Membre(identificateur,type,acces,caracteristique)
{
    _parametres = parametres;
}

Methode::~Methode() {
}

string Methode::toString()
{
    string affic = "";
    string param = "";

    list<string>::iterator it = _parametres.begin();

    //on transfome la liste d'argument en chaine de type arg1,arg2,arg3
    if( it != _parametres.end())
    {
        param += (*it);
        ++it;
    }

    while(it != _parametres.end())
    {
        param += "," + (*it);
        ++it;
    }


    if(isVirtual())
    {
        affic += "virtual ";
    }
    if(isStatic())
    {
        affic += "static ";
    }

    affic += _type + " " + _id + "(" + param + ")";

    if(isPureVirtual())
    {
        affic += "=0";
    }

    return affic;
}

