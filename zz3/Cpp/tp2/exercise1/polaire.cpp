/* 
 * File:   polaire.cpp
 * Author: escourbi
 * 
 * Created on October 10, 2011, 1:42 PM
 */

#include "polaire.h"
#include "cartesien.h"

#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

Polaire::Polaire() {
}

Polaire::Polaire(double rho, double theta)
{
    _rho   = rho;
    _theta = theta;
}

Polaire::Polaire(Cartesien& cartesien)
{
    double x = cartesien.getX();
    double y = cartesien.getY();

    _rho   = x*x + y*y;
    _theta = atan2(y,x);
}

Polaire::~Polaire() {
}

void Polaire::afficher() const
{
    cout << "rho: " << _rho << " theta: " << _theta << endl;
}

string Polaire::toString() const
{
    char temp[255];
    sprintf(temp,"rho: %5.2lf , theta: %5.2lf ",_rho,_theta);

    string a(temp);
    return a;
}

void Polaire::bary(double& x, double& y)
{
    x = _rho * cos(_theta);
    y = _rho * sin(_theta);
}

Polaire::operator  Cartesien()
{
   Cartesien res( _rho * cos(_theta),_rho * sin(_theta));
   return res;
}
