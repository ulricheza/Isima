/* 
 * File:   rectangle.h
 * Author: escourbi
 * 
 * Created on November 3, 2010, 10:14 AM
 */


#ifndef _RECTANGLE_H
#define	_RECTANGLE_H

#include "graphicalobject.h"

class Rectangle : public GraphicalObject {
   public:
      Rectangle(Point pPoint, int pW, int pH);
      string toString();
      void display();
      bool isSelected(Point pPoint);
};

#endif
