/* 
 * File:   position.cpp
 * Author: escourbi
 * 
 * Created on January 4, 2011, 10:37 AM
 */

#include "position.h"

/**
 * \fn Position::Position(int x,int y)
 * \brief constructeur par defaut de la classe position
 * \param x coordonee d'une case
 * \param y coordonee d'une case
 */
Position::Position(int x,int y): _x(x), _y(y)
{
}

/**
 * \fn Position Position::operator =(const Position& pos)
 * \brief surcharge de l'operateur =
 * \param pos instance de Position a copier
 */
void Position::operator =(const Position& pos)
{
    (*this)._x = pos._x;
    (*this)._y = pos._y;
}