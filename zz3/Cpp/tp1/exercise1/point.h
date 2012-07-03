/** 
 * File:   point.h
 * Author: escourbi
 *
 * Created on October 10, 2011, 1:35 PM
 */

#ifndef _POINT_H
#define	_POINT_H

#include <iostream>
#include <string>

using namespace std;

class Point {
public:
    Point();
    virtual ~Point();

    virtual void   afficher() const             = 0;
    virtual string toString() const             = 0;
    virtual void   bary(double & x, double & y) = 0;
    
private:
};

//declaration des surcharges operateur
ostream & operator<< (ostream & stream, const Point & point);

#endif	/* _POINT_H */

