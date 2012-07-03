/* 
 * File:   graphicalobject.h
 * Author: escourbi
 *
 * Created on November 3, 2010, 10:14 AM
 */

#ifndef _GRAPHICALOBJECT_H
#define	_GRAPHICALOBJECT_H

#include "point.h"
#include <string>
#include <iostream>
#include <sstream>
#include <math.h>

using namespace std;

class Point;

enum color{
    rouge = 1,
    bleu ,
    vert,
    violet,
};


class GraphicalObject {
public:
    ~GraphicalObject() {};
    GraphicalObject(Point pPoint = ORIGINE ,int pW = 0,int pH = 0 );
    virtual string toString() = 0;
    virtual void display() = 0;
    virtual bool isSelected(Point pPoint) = 0;
    void move(Point pPoint);
    void shift(Point pPoint);
protected:
    static const Point ORIGINE;
    static int cpt;
    Point _origin;
    int _id;
    int _wdth;
    int _height;
    color _COLORS;
};

#endif	/* _GRAPHICALOBJECT_H */

