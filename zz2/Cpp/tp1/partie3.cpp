/**
 * \file partie3.cpp
 * \brief partie 3 tp1 en C++
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mercredi 6 octobre 2010
 */

#include <iostream>

using namespace std;

class A
{
   public:
      A(void)      {cout << "A()" << endl;}
      A(const A &) {cout <<"A(A)" << endl;} //si n'est pas present genera par defaut par le compilo
      ~A(void)     {cout <<"~A()" << endl;}
};

class B : public A
{
   public:
      B(void)      {cout << "B()" << endl;}
      B(const B &) {cout << "B(B)" << endl;}
      ~B(void)     {cout <<"~B()" << endl;}
};

int main(int, char**)
{
   A a1; //affiche le constructeur A(void)
   cout << "instruction suivante " << endl;
   B b1; //affiche le constructeur de ma classe mere A puis le constructeur de la classe B(void)
   cout << "instruction suivante " << endl; 
   A a2(a1); //utilise le second constructeur de la classe A
   cout << "instruction suivante " << endl;
   //si A( const & A) n'est pas declare dans la classe il est genere par defaut par le compilo
   //dans ce cas la il fera juste de la copie d'attribut
   A a3 = a1; // copie les attribut de l'instance a1 
   cout << "instruction suivante " << endl;
   B b2(b1);// appelle le constructeur A() puis le constructeur B(B)
   cout << "instruction suivante " << endl;
   A a4(a2); // utilise le second constructeur de la classe A
   cout << "instruction suivante " << endl;
   A ta[5]; //effectue 5 fois le constructeur A()
   cout << "instruction suivante " << endl;
   B tb[3]; //effectue A() B() A() B() A() B()

   cout << "fin partie 3" << endl;
   //appelle les destructeurs de tous les elements utilise ici
   //Pour une classe fille on detruit d'abord l'instance fille puis l'instance mere
   return 1;
}





