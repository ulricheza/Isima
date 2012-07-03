/* 
 * File:   liste.h
 * Author: escourbi
 *
 * Created on November 17, 2010, 10:17 AM
 *Ce fichier regroupe les classes list,ItList et Cell
 */

#ifndef _LISTE_H
#define	_LISTE_H

#include <cstdlib>

template<typename T>
class List;
template<typename T>
class ItList;
 
template<typename T>
class Cell{
   private:
       T _valeur;
       Cell * _suiv;
   public:
       Cell(const T & val,Cell  * next = NULL);
       ~Cell() {}
       friend class List<T>;
       friend class ItList<T>;
};

template <typename T>
class ItList{
   private:
       List<T> * _list;
       Cell<T> * _cour;
   public:
       ItList();
       virtual ~ItList() {}
       ItList<T> operator=   (const ItList<T> & inItList);
       bool      operator == (const ItList<T> & inItList);
       T &       operator* ();

       //differencier les operateurs postfixes et prefixes
       ItList<T> & operator++(int); //i++
       ItList<T>   operator++();    //++i
       friend class List<T>;
};

template <typename T>
class List{
    private:
        Cell<T> * _first;
        Cell<T> * _last;
    public:
        List();
        virtual ~List() {}
        //methode de classe
        void push_back(const T & x);
        void push_front(const T & x);
        T    pop_front();
        bool empty()const;
        void clear();
        ItList<T> begin() const;
        ItList<T> end() const;
        void remove(const ItList<T> & x);
        ItList<T> find(const T & x) const;
};



#include "liste.cpp"
#endif	/* _LISTE_H */

