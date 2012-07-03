/* 
 * File:   polaire.h
 * Author: escourbi
 *
 * Created on October 10, 2011, 1:42 PM
 */

#ifndef _POLAIRE_H
#define	_POLAIRE_H

#include "point.h"



class Cartesien;

class Polaire : public Point {
public:

    //Constructeur et destructeur
    Polaire();
    Polaire(double rho, double theta);
    Polaire(Cartesien & cartesien);
    
    virtual ~Polaire();

    //surcharge d'operateur

    operator Cartesien(); //operateur de conversion.

    //Methodes
    virtual void   afficher() const;
    virtual string toString() const;
    virtual void   bary(double & x, double & y);
    //Accesseurs
    double getRho()   {return _rho;}
    double getTheta() {return _theta;}
    void   setRho( double rho ) { _rho = rho; }
    void   setTheta( double theta ) { _theta = theta; }

private:

    double _rho;
    double _theta;

};

#endif	/* _POLAIRE_H */

