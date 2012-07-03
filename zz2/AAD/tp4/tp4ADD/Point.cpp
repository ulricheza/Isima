/*
 * \file point.cpp
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \brief fichier d'implementation de la classe Point
 * \version 1.0
 * \date 7 janvier 2011
 */

#include "Point.h"

/**
 *\fn Point::Point(int _x, int _y)
 *\brief constructeur d'un point
 *\param _x coordonne en x
 *\param _y coordonne en y
 *
 */
Point::Point(int _x, int _y): x(_x), y(_y)
{

}

/**
 *\fn Point::Point(const Point& orig)
 *\brief constructeur par copie d'un point
 *\param orig point a copier
 *
 */
Point::Point(const Point& orig): x(orig.x),y(orig.y)
{
}
