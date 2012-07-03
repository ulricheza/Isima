/**
 * \file String.h
 * \brief fichier d'en tete de la classe String
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Mercredi 20 Octobre 2010
 */


#ifndef __STRING_H_MAX__
#define __STRING_H_MAX__

#include <cstring>
#include <iostream>

using std::cout;
using std::endl;

class String
{
   private:
      int _size;
      char * _pData;
   public:
      //Constructeur & destructeur
      String();
      String(char * inCString);
      String(const String & inString);
      String(int size);
      ~String() ;
      //getter
      int getSize() const      {return _size;}
      char * getPData() const  {return _pData;}
      //surcharge d'operateur
      String & operator= (const String & inString);
      char & operator[] (int i);
      //methodes
      void toScreen() const { cout << _pData << endl;}

};

String operator+ (const String & , const String & );
std::ostream & operator<< (std::ostream & flux, const String & v);
#endif
