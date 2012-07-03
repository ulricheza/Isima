/* 
 * File:   circle.h
 * Author: escourbi
 * 
 * Created on November 3, 2010, 10:14 AM
 */


#ifndef _CIRCLE_H
#define	_CIRCLE_H

#include "graphicalobject.h"

class Circle : public GraphicalObject {
   public:
      Circle(Point pPoint, int pW, int pH);
      Circle(Point pPoint, int pRadius);
      string toString(); //virtual par defaut
      void display();
      bool isSelected(Point pPoint);
};

#endif
