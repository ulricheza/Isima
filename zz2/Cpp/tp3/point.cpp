/* 
 * File:   point.cpp
 * Author: escourbi
 * 
 * Created on November 3, 2010, 10:17 AM
 */

#include "point.h"

Point::Point(int x, int y): _x(x),_y(y)
{

}

void Point::add(Point p)
{
   _x += p._x;
   _y += p._y;
}
