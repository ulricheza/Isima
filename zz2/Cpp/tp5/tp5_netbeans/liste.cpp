/* 
 * File:   liste.cpp
 * Author: escourbi
 * 
 * Created on November 17, 2010, 10:17 AM
 */

#include "liste.h"


/*--------------------------------------------------------------*/
/*Declaration des methodes pour la classe Cell                  */
/*--------------------------------------------------------------*/
template <typename T>
Cell<T>::Cell(const T & val,Cell * next): _valeur(val), _suiv(next)
{

}

/*--------------------------------------------------------------*/
/*Declaration des methodes pour la classe ItList                */
/*--------------------------------------------------------------*/

//Implementation du constructeur
template <typename T>
ItList<T>::ItList() : _list(NULL),_cour(NULL)
{

}

//Implementation de la surcharge de l'operateur =
template <typename T>
ItList<T> ItList<T>::operator= (const ItList<T> & inItList)
{
    if(this != &inItList)
    {
       _cour = inItList._cour;
       _list = inItList._list;
    }
}

//implementation de la methode de comparaison entre deux iterator de liste
template <typename T>
bool ItList<T>::operator == (const ItList<T> & inItList)
{
    return(_list == inItList._list && _cour == inItList._cour);
}

//implementation de la surcharge de l'opérateur *
template <typename T>
T & ItList<T>::operator* ()
{
    return (_cour->_valeur);
}

//implementation de la surcharge de l'operateur ++ prefixe
template <typename T>
ItList<T> & ItList<T>::operator++ (int)
{
    _cour = _cour->_suiv;
    return *this;
}

//implementation de la surcharge de l'operateur ++ postfixe
template <typename T>
ItList<T> ItList<T>::operator++ ()
{
    //on retourne une instance temporaire pour le cas ou on ferait 
    //*(i++) <== on doit pas modifier i avant de faire le *
    ItList<T> temp(*this);
    _cour = _cour->_suiv;
    return temp;
}

/*--------------------------------------------------------------*/
/*Declaration des methodes pour la classe List                  */
/*--------------------------------------------------------------*/

//implementation du constructeur
template <typename T>
List<T>::List(): _first(NULL),_last(NULL)
{
    
}

//implementation de la methode push_back
template <typename T>
void List<T>::push_back(const T & x)
{
    Cell<T> * temp = new Cell<T>(x,NULL);

    if(_last != NULL)
       _last->_suiv = temp;
    else
       _first = temp;
    _last = temp;
}

//implementation de la methode push_front
template <typename T>
void List<T>::push_front(const T & x)
{
   Cell<T> * temp = new Cell<T>(x,_first);
   if(_last == NULL)
   {
       _last = temp;
       temp->_suiv = NULL;
   }
   else
      temp->_suiv = _first;
   _first = temp;
}

//implementation de la methode pop_front
template <typename T>
T List<T>::pop_front()
{
  Cell<T> * temp = _first;
  T ret = _first->_valeur;
  _first = _first->_suiv;
  if(_first == NULL)
      _last = NULL;
  delete temp;
  return ret;
}

//implementation de la methode empty
template <typename T>
bool List<T>::empty() const
{
    return(_last == NULL && _first == NULL);
}

//implementation de la methode clear
template <typename T>
void List<T>::clear()
{
    Cell<T> * cour,*prec;
    cour = _first;
    while(!cour)
    {
        prec = cour;
        cour = cour->_suiv;
        delete prec;
    }
}

//implementation de la methode begin
template <typename T>
ItList<T> List<T>::begin() const 
{
    ItList<T> temp;
    temp._list = (List<T> *) this;
    temp._cour = _first;
    return temp;
}

//implementation de la fonction end
template <typename T>
ItList<T> List<T>::begin() const
{
    ItList<T> temp;
    temp._list = (List<T> *) this;
    temp._cour = _last;
    return temp;
}

//implementation de la methode remove
template <typename T>
void List<T>::remove(const ItList<T> & x)
{
    if(this == x._list)
    {
        Cell<T> * cour = _first;
        Cell<T> * prec = NULL;
        Cell<T> * val = x._cour;
        while(cour != val)
        {
            prec = cour;
            cour = cour->_suiv;
        }
        if(prec != NULL)
           prec->_suiv = cour->_suiv;
        else
           _first = cour->_suiv;
        delete cour;
     }
}

//implementation de la methode find
//conformement a la stl si la valeur est pas trouve on retourne end();
template <typename T>
ItList<T> List<T>::find(const T & x) const
{
    ItList<T> temp;
    Cell<T> * cour;
    temp._list = (List<T> *)this;
    cour = _first;
    while(cour != _last && cour->_valeur != x)
        cour = cour->_suiv;
    temp._cour = cour;
    return temp;
}
