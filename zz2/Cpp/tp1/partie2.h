/**
 * \file partie2.h
 * \brief partie 2 tp1 en C++
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mardi 5 octobre 2010
 */

#ifndef __PARTIE2_H_MAX__
#define __PARTIE2_H_MAX__


#include <iostream>


using namespace std;

class mere
{
  protected:
    int _id;
    static int _compteur ;
  public:
    mere(int id = 0);
    ~mere() {_compteur--;}
    static int getCOMPTEUR() {return _compteur;}
    int getID()              {return _id;} //declaration de type inline pour les setters, getters
    void setID(int id)       {_id = id;}
    virtual void whoami()    { cout << "ceci est une classe mere " << endl;}

};


class fille : public mere
{
  public:
    fille(int id = 0);
    ~fille() {}
    void whoami() { cout << "ceci est une classe fille " << endl;}
};
#endif
