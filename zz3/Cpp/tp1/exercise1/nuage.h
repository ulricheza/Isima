/* 
 * File:   nuage.h
 * Author: escourbi
 *
 * Created on October 10, 2011, 3:04 PM
 */

#ifndef _NUAGE_H
#define	_NUAGE_H

#include <vector>
#include "cartesien.h"
#include "point.h"


class Nuage {
public:

    //Constructeur et destructeur
    Nuage();
    virtual ~Nuage();

    //Creation des types
    typedef vector<Point*>::iterator iterator;

    //Methodes
    void    push_back(Point * point) { _nuage.push_back(point);}
    Point * front()                  { _nuage.front();}
    Point * back()                   { _nuage.back();}
    
    vector<Point*>::iterator begin() { return _nuage.begin(); }
    vector<Point*>::iterator end()   { return _nuage.end();   }
    Cartesien calculBarycentre();


private:
    vector<Point*> _nuage;


};

#endif	/* _NUAGE_H */

