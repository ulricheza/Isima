/* 
 * File:   cartesien.h
 * Author: escourbi
 *
 * Created on October 10, 2011, 1:37 PM
 */

#ifndef _CARTESIEN_H
#define	_CARTESIEN_H

#include "point.h"


class Polaire;

class Cartesien : public Point {
public:
    //Constructeur et destructeur
    Cartesien();
    Cartesien(double x, double y);
    Cartesien(Polaire & polaire);
    virtual ~Cartesien();

    //surcharge d'operateur
    operator Polaire();

    //Methodes
    virtual void   afficher() const;
    virtual string toString() const;
    virtual void   bary(double & x, double & y);

    //Acceseurs
    double getX() { return _x; }
    double getY() { return _y; }
    void   setX( double X ) { _x = X;}
    void   setY( double Y ) { _y = Y;}

private:

    double _x;
    double _y;
};

#endif	/* _CARTESIEN_H */

