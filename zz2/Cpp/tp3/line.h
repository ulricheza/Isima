/* 
 * File:   line.h
 * Author: escourbi
 * 
 * Created on November 3, 2010, 10:14 AM
 */


#ifndef _LINE_H
#define	_LINE_H

#include "graphicalobject.h"

class Line : public GraphicalObject {
   public:
      Line(Point pPoint, int pW, int pH);
      string toString();
      void display();
      bool isSelected(Point pPoint);
};

#endif