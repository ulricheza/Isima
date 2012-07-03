/* 
 * File:   line.cpp
 * Author: escourbi
 * 
 * Created on November 3, 2010, 10:14 AM
 */

#include "line.h"

Line::Line(Point pPoint, int pW, int pH)
   : GraphicalObject(pPoint,pW,pH)
{
}

string Line::toString()
{
   return ("Line " + GraphicalObject::toString());
}

void Line::display()
{
   std::cout << "Line ";
   GraphicalObject::display();
}

bool Line::isSelected(Point pPoint)
{
//TO DO fonction d'appartenance a une ligne
   return true;
}
