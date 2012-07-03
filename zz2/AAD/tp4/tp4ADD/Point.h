/* 
 * \file Point.h
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \brief fichier de declaration de la classe Point
 * \version 1.0
 * \date 7 janvier 2011
 *
 */

#ifndef _POINT_H
#define	_POINT_H

class Point {
public:
    //attributs en public pour faciliter la manipulation
    int x;
    int y;

    //Les constructeurs
    Point(int _x = 0, int _y = 0);
    Point(const Point& orig);
};

#endif	/* _POINT_H */

