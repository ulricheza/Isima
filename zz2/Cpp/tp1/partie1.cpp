/**
 * \file helloworld.cpp
 * \brief Hello world en c++
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mardi 5 octobre 2010
 */

#include<iostream>

using namespace std;

/*declaration des fonctions*/
void swap( int * a, int * b);
void swap(int & a, int & b);

int main(int , char ** ) /* a demander parametre muet*/
{
   int a = 0,b = 1;
   float x= 0.0, y=1.0;
   cout << "Hello World" << endl;
   cout << "a= " << a << "b= " << b << endl;
   cout << "echange par pointeur" << endl;
   swap(&a,&b);
   cout << "a= " << a << "b= " << b << endl;
   cout << "echange par reference " << endl;
   swap(a,b);
   cout << "a= " << a << "b= " << b << endl;
   cout << "maintenant valeur reelles" << endl;
   cout << "x= " << x << "y= " << y << endl;
   cout << "echange de valeur reelles par reference" << endl;
   swap(x,y);
   cout << "x= " << x << "y= " << y << endl;
   return(1);
}

/*swap par pointeur*/
void swap( int * a, int * b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

/*swap par reference*/
void swap(int & a, int & b)
{
  int temp = a;
  a = b;
  b = temp;
}

/*swap de valeur reelles*/
void swap( float & a, float & b)
{
  float temp = a;
  a = b;
  b = temp;
}

