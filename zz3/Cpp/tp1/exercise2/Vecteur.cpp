/* 
 * File:   Vecteur.cpp
 * Author: maxime
 * 
 * Created on 11 octobre 2011, 14:11
 */

#include "Vecteur.h"

#include <cstring>
#include <cstdio>

Vecteur::Vecteur()  
{
    _longueur    = 0;
    _longueurMax = 50;
    _tableau     = new int[50];
}

Vecteur::Vecteur(int taille)
{
    _longueur    = 0;
    _longueurMax = taille;
    _tableau     = new int[taille];
}

Vecteur::Vecteur(int taille, int* tab)
{
    _longueur    = 0;
    _longueurMax = taille;
    _tableau     = new int[taille];
    
    for(int i = 0 ; i < taille ; ++i)
    {
        _tableau[i] = tab[i];
    }
}

Vecteur::Vecteur(const Vecteur& orig) {

    _longueur    = orig._longueur;
    _longueurMax = orig._longueurMax;

    Vecteur(orig._longueur,orig._tableau);
}

Vecteur::~Vecteur() {
    
    _longueur    = 0;
    _longueurMax = 0;

    delete[] _tableau;
}

Vecteur Vecteur::operator =(Vecteur& vect)
{
    Vecteur result(vect);
    return result;
}

void Vecteur::push_back(int x)
{
    if (_longueur == _longueurMax )
    {
        int * temp = _tableau;
        _longueurMax += _longueurMax/2 + 1;
        _tableau   = new int[_longueurMax ];

        for(int i = 0; i <= _longueur ; ++i)
        {
            _tableau[i] = temp[i];
        }
    }
    _tableau[_longueur++] = x;
}

void Vecteur::pop_back()
{
    if(_longueur  > 0)
        --_longueur;
}

int Vecteur::back()
{
    return ( (_longueur)? _tableau[_longueur-1] : -1 );
}

int Vecteur::front()
{
    return ( (_longueur)? _tableau[0] : -1 );
}

Vecteur  Vecteur::operator +(Vecteur& vect)
{
    int i,j;
    Vecteur result(this->_longueurMax + vect._longueurMax);

    result._longueur = this->_longueur + vect._longueur;
    
    for(i = 0; i < this->_longueur ; ++i )
    {
        result._tableau[i] = this->_tableau[i];
    }

    for(j = 0; j < vect._longueur; ++j)
    {
        result._tableau[i++] = vect._tableau[j];
    }

    return result;
}

string Vecteur::toString() const
{
    char result[255] = "\0";
    char temp[255];

    for(int i = 0; i < _longueur; ++i)
    {
        sprintf(temp,"%d \0",_tableau[i]);
        strcat(result,temp);
    }

    string res(result);

    return res;

}

//attention pas de test sur la validite de l'iterateur
int & Vecteur::operator [](const int& iter)
{
    return _tableau[iter];
}

int Vecteur::operator *(Vecteur& vect)
{
    int result = 0;

    if(this->_longueur == vect._longueur)
    {
        for(int i = 0; i < this->_longueur ; ++i)
        {
            result += this->_tableau[i] * vect._tableau[i];
        }
    }

    return result;
}

ostream & operator<< (ostream & stream, const Vecteur & vecteur)
{
    stream << vecteur.toString();
    return stream;
}

Iterator Vecteur::begin()
{
    Iterator res(_tableau);
    return res;
}

Iterator Vecteur::end()
{
    Iterator res(&_tableau[max(0,_longueur-1)]);
    return res;
}