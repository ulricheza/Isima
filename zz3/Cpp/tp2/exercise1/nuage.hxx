/* 
 * File:   nuage.hxx
 * Author: escourbi
 *
 * Created on October 17, 2011, 2:25 PM
 */

#ifndef _NUAGE_HXX
#define	_NUAGE_HXX


#include <vector>

template < typename T >
class Nuage {

public:

    //Constructeur et destructeur
    Nuage();
    virtual ~Nuage();

    //Creation des types
    //obligation de mettre le typename car vector ne peut pas etre connu
    typedef typename vector<T>::iterator iterator;

    //Methodes
    void    push_back(T point) { _nuage.push_back(point);}
    T       front()            { _nuage.front();}
    T       back()             { _nuage.back();}

    iterator begin() { return _nuage.begin(); }
    iterator end()   { return _nuage.end();   }
    T calculBarycentre();

private:
    vector<T> _nuage;

};

#include "nuage.cxx"

#endif	/* _NUAGE_HXX */

