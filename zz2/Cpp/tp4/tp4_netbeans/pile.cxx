/*
 * File:   pile.cxx
 * Author: escourbi
 *
 * Created on November 10, 2010, 11:31 AM
 */


//implementation du constructeur
template <typename T>
Pile<T>::Pile(int taille_max) : _index(-1),_taille_max(taille_max)
{
    _tab = new T[taille_max];
}

//implementation du destructeur
template <typename T>
Pile<T>::~Pile()
{
    delete[] _tab;
}

//implementation de la methode empiler
template <typename T>
bool Pile<T>::empiler(const T & val)
{
    if(_index < _taille_max-1)
    {
        ++_index;
        _tab[_index] = val;
        return true;
    }
    else
        return false;
}

//attention la fonction depiler ne verifie pas si la pile est vide
template <typename T>
T Pile<T>::depiler()
{
    T temp;
    temp = _tab[_index--];
    return temp;
}
