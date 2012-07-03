/* 
 * File:   circle.cpp
 * Author: escourbi
 * 
 * Created on November 3, 2010, 10:14 AM
 */

#include "circle.h"

Circle::Circle(Point pPoint, int pW, int pH)
   : GraphicalObject(pPoint,pW,pH)
{
}

Circle::Circle(Point pPoint, int pRadius)
   : GraphicalObject(Point(pPoint.getX()-pRadius,pPoint.getY()-pRadius),pRadius,pRadius)
{

}

string Circle::toString()
{
   string A;
   if(_height == _wdth)
      A = "Cercle ";
   else
      A = "Ellipse ";
   return (A + GraphicalObject::toString());
}

void Circle::display()
{
   if(_height == _wdth)
      std::cout << "Cercle ";
   else
      std::cout << "Ellipse ";
   GraphicalObject::display();
}

bool Circle::isSelected(Point pPoint)
{
   float x = (float)pPoint.getX() - (float)_origin.getX();
   float y = (float)pPoint.getY() - (float)_origin.getY();
   return( sqrt(x*x + y*y) < _height);
}
