/**
 * \file partie4.cpp
 * \brief partie 4 tp1 en C++
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mercredi 6 octobre 2010
 */


#include<iostream> // autre declaration possible <iostream.h> mais warning au compilo

using namespace std;

// la solution pour avoir un nombre minimal de constructeur de A est d'ajouter
// le mot cle virtual devant les classes qui herite de A
class A
{
   public:
      A(void)      {cout << "A()" << endl;}
      ~A(void)     {cout <<"~A()" << endl;}
};

class B : virtual public A
{
   public:
      B(void)      {cout << "B()" << endl;}
      ~B(void)     {cout <<"~B()" << endl;}
};

class C : virtual public A
{
   public:
      C(void)      {cout << "C()" << endl;}
      ~C(void)     {cout <<"~C()" << endl;}
};

class D : public B, public C
{
   public:
      D(void)      {cout << "D()" << endl;}
      ~D(void)     {cout <<"~D()" << endl;}
};

int main(int, char**)
{
   D d;
   cout << "end of partie 4" << endl;
   return 0;
}



