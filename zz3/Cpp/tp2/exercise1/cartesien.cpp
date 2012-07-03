/* 
 * File:   cartesien.cpp
 * Author: escourbi
 * 
 * Created on October 10, 2011, 1:37 PM
 */

#include "cartesien.h"
#include "polaire.h"

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

Cartesien::Cartesien() {
}

Cartesien::Cartesien(double x, double y)
{
    _x = x;
    _y = y;
}

Cartesien::Cartesien(Polaire & polaire)
{
    double rho   = polaire.getRho();
    double theta = polaire.getTheta();

    _x = rho * cos(theta);
    _y = rho * sin(theta);
}


Cartesien::~Cartesien() {
}

void Cartesien::afficher() const
{
    cout << "x: " << _x << " y: " << _y << endl;
}

string Cartesien::toString() const
{
    char temp[255];
    sprintf(temp,"x: %5.2lf , x: %5.2lf ",_x,_y);

    string a(temp);
    return a;
}

void Cartesien::bary(double& x, double& y)
{
    x = _x;
    y = _y;
}

Cartesien::operator  Polaire()
{
    Polaire res(_x*_y,atan2(_y,_x));
    return res;
}
