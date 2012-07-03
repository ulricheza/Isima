/* 
 * File:   rectangle.cpp
 * Author: escourbi
 * 
 * Created on November 3, 2010, 10:14 AM
 */

#include "rectangle.h"

Rectangle::Rectangle(Point pPoint, int pW, int pH)
   : GraphicalObject(pPoint,pW,pH)
{
}

string Rectangle::toString()
{
   return ("Rectangle " + GraphicalObject::toString());
}

void Rectangle::display()
{
   std::cout << "Rectangle ";
   GraphicalObject::display();
}

bool Rectangle::isSelected(Point pPoint)
{
   float x = (float)pPoint.getX() - (float)_origin.getX();
   float y = (float)pPoint.getY() - (float)_origin.getY();
   return( x < (float)_origin.getX() && y < (float)_origin.getY());
}
