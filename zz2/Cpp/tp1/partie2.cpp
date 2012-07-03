/**
 * \file partie2.cpp
 * \brief partie 2 tp1 en C++
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mardi 5 octobre 2010
 */


#include "partie2.h"

//initialisation des variables de classes
int mere::_compteur = 0;

int main()
{
  mere * a = new mere(4);
  mere * b = new mere(); // valeur par defaut du constructeur
  fille * c = new fille(10);
  cout << "b->getID " << b->getID() << endl;
  a->setID(15);
  cout << "a->getID " << a->getID() << endl;
  cout << "nombre de classe mere cree " << mere::getCOMPTEUR() << endl;
  cout << "c->getID " << c->getID() << endl;
  c->setID(10);
  cout << "c->getID " << c->getID() << endl;
  //fille accede a la methode de classe mere
  cout << "nombre de classe mere cree " << fille::getCOMPTEUR() << endl;
  a->whoami();
  b->whoami();
  c->whoami();
  return 1;
}


mere :: mere(int id):
        _id(id)
{
   cout << "construction d'une instance de classe mere " << id << endl;
   _compteur++;
}


fille :: fille(int id) :
         mere(id)
{
  cout << "Creation d'une instance de classe fille" << endl;
}
                 