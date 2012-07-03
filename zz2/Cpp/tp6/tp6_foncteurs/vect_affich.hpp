/* 
 * File:   vect_affich.hpp
 * Author: escourbi
 *
 * Created on 23 décembre 2010, 01:21
 */

#ifndef _VECT_AFFICH_HPP
#define	_VECT_AFFICH_HPP

#include <iostream>

using namespace std;

class vect_affich{
public:
    vect_affich() {}
    void operator() (const int & a) { cout << a << " ";}

};

#endif	/* _VECT_AFFICH_HPP */

