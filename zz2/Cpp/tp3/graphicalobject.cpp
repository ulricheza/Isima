/* 
 * File:   graphicalobject.cpp
 * Author: escourbi
 *
 * Created on November 3, 2010, 10:14 AM
 */

#include "graphicalobject.h"

const Point GraphicalObject::ORIGINE(0,0);
int         GraphicalObject::cpt = 0;

//implementation du constructeur

GraphicalObject::GraphicalObject(Point pPoint,int pW,int pH ) : _origin(pPoint),_wdth(pW),_height(pH)
{
  _id = cpt;
  ++cpt;
}

//implementation de la methode to_string

string GraphicalObject::toString()
{
  ostringstream temp;
  temp << "origine: X:" << _origin.getX() << " Y:" << _origin.getX() << endl;
  temp << "hauteur:"<< _wdth << endl << "largeur:" << _height << endl;
  return (temp.str());
}

//implementation de la fonction Display

void GraphicalObject::display()
{
  cout << "origine: X:" << _origin.getX() << " Y:" << _origin.getX() << endl;
  cout << "hauteur:"<< _wdth << endl << "largeur:" << _height << endl;
}

//implementation de la fonction de deplacement d'origine du point
void GraphicalObject::move(Point pPoint)
{
  _origin = pPoint;
}

//implementation du deplacement de point
void GraphicalObject::shift(Point pPoint)
{
  _origin.add(pPoint);
}