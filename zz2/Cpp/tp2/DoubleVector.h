/**
 * \file DoubleVector.h
 * \brief fichier d'en tete de la classe DoubleVector
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Lundi 25 Octobre 2010
 */


#ifndef __DOUBLEVECTOR_H_MAX__
#define __DOUBLEVECTOR_H_MAX__

#include <iostream>

using std::cout;
using std::endl;

class DoubleVector
{
   private:
      int _size;
      double * _pData;
   public:
      //Constructeur & destructeur
      DoubleVector();
      DoubleVector(double * inVector,int size);
      DoubleVector(const DoubleVector & inVector);
      DoubleVector(int size);
      ~DoubleVector() ;
      //getter
      int getSize() const        {return _size;}
      double * getPData() const  {return _pData;}
      //surcharge d'operateur
      DoubleVector & operator= (const DoubleVector & inVector);
      double & operator[] (int i);
      
};
DoubleVector operator+ (const DoubleVector & , const DoubleVector & );
std::ostream & operator<< (std::ostream & flux, const DoubleVector & v);
#endif
