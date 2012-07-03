/* 
 * File:   point.cpp
 * Author: escourbi
 * 
 * Created on October 10, 2011, 1:35 PM
 */

#include "point.h"



Point::Point() {
}


Point::~Point() {
}


ostream & operator<< (ostream & stream, const Point & point)
{
    stream << point.toString();
    return stream;
}
