/**
 * \file tp2_1.cpp
 * \brief fichier de test de la partie 1
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mercredi 20 Octobre 2010
 */

#include "String.h"

//declaration des fonctions
void displayByValue(String );
void displayByref(const String & );

int main (int, char**)
{
   cout << "Initialisation des chaines" << endl;
   String chaine1("Coucou toi");
   String chaine2(" max");
   cout << "appel fonction by val" << endl;
   displayByValue(chaine2);
   cout << "appel fonction by ref" << endl;
   displayByref(chaine1+chaine2);
   cout << chaine1 << endl;
   cout << chaine1[2] << endl;
   cout << "fin tp" << endl;
    
   return 0;
}

void displayByValue(String val)
{
   val.toScreen();
}

void displayByref(const String & val)
{
   val.toScreen();
}