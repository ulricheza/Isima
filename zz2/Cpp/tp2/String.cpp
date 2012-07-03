/**
 * \file String.cpp
 * \brief fichier de declaration de methode de la classe String
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mercredi 20 Octobre 2010
 */

#include "String.h"

/**
 * \fn String :: String()
 * \brief Constructeur par defaut de la classe String
 */

String :: String(): _size(0), _pData(0)
{
   cout << "constructeur par defaut" << endl;
}

/**
 * \fn String :: String(char * inCString)
 * \brief Constructeur utilisant une chaine de caractere
 * \param inCString tableau de caracteres a inserer l'instance de la classe String
 */

String :: String(char * inCString)
{
   _pData = new char[_size=strlen(inCString) + 1];
   strcpy(_pData,inCString);
   cout << "constructeur par char *" << endl;
}

/**
 * \fn String :: String(const string & inCString)
 * \brief Constructeur utilisant une instance de classe String
 * \param inCString instance de classe string
 */

String :: String(const String & inString)
{
   _pData = new char [_size = inString._size + 1];
   strcpy(_pData,inString._pData);
   cout << "constructeur par instance en parametre" << endl;
}

/**
 * \fn String :: String(int size)
 * \brief Constructeur utilisant un entier
 * \param size taille max de la chaine de caractere 
 */

String :: String(int size): _size(size)
{
  _pData = new char[size+1];
}


/**
 * \fn String :: ~String()
 * \brief Destructeur par defaut de la classe String
 */
String :: ~String()
{
   delete [] _pData;
   cout << "appel du destructeur" << endl;
}

/**
 * \fn String & String :: operator = (const String & inString)
 * \brief surcharge de l'operateur =
 * \param inString on veut a = instring
 */

String & String :: operator= (const String & inString)
{
   if( &inString != this)
   {
      delete [] _pData;
      _pData = new char [_size = inString._size +1];
      strcpy(_pData,inString._pData);
      cout << "surcharge d'operateur =" << endl;
   }
   return * this; // pour pouvoir effectuer chaine1=chaine2=chaine3 etc...
}

/**
 * \fn String operator+ (const String & s1, const String & s2)
 * \brief surcharge de l'operateur +
 * \param s1 on veut a = s1 + s2
 * \param s2 
 */
//fonctions de surcharge d'operateur 
//on les met en dehors de classe pour qu'ils puissent gerer les constructeurs implicites
// ex: on pourra faire s1 = "toto" + s2 , un constructeur par chaine sera utilise

String operator+ (const String & s1, const String & s2)
{
   char * chaine = new char[s1.getSize() + s2.getSize()]; //passage par declaration dynamique cause ISO C++
   strcat(strcpy(chaine,s1.getPData()),s2.getPData());
   String temp(chaine);
   delete[] chaine;
   return temp;
}

/**
 * \fn std::ostream & operator<< (const osteam & flux, const String & v)
 * \brief surcharge de l'operateur <<
 * \param flux flux que l'on veut utiliser
 * \param v string que l'on veut afficher
 * \return retourne le flux surcharge
 */

std::ostream & operator<< (std::ostream & flux, const String & v)
{
   flux << v.getPData();
   return flux;
}

/**
 * \fn char & operator[] (const int i)
 * \brief surcharge de l'operateur []
 * \param i indice du caractere que l'on veux voir,modifier
 * \return retourne le caractere dans la chaine desire
 */

char & String::operator[] (int i)
{
   return(_pData[i]);
}