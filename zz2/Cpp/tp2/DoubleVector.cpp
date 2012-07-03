/**
 * \file DoubleVector.cpp
 * \brief fichier de declaration de methode de la classe DoubleVector
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Lundi 25 octobre
 */

#include "DoubleVector.h"

/**
 * \fn DoubleVector :: DoubleVector()
 * \brief Constructeur par defaut de la classe DoubleVector
 */

DoubleVector :: DoubleVector(): _size(0), _pData(0)
{
   cout << "constructeur par defaut" << endl;
}

/**
 * \fn String :: String(char * inCString)
 * \brief Constructeur utilisant une chaine de caractere
 * \param tab tableau de double
 * \param size taille du tableau passer en parametre
 */

DoubleVector :: DoubleVector(double * tab,int size) : _size(size)
{
   int i;
   _pData = new double[_size];
   for(i=0;i<size;++i)
      _pData[i]=tab[i];
    
   cout << "constructeur par double * et int size" << endl;
}

/**
 * \fn DoubleVector :: DoubleVector(const DoubleVector & inVector)
 * \brief Constructeur utilisant une instance de classe DoubleVector
 * \param inVector instance de classe DoubleVector
 */

DoubleVector :: DoubleVector(const DoubleVector & inVector)
{
   _pData = new double [_size = inVector._size];
   for(int i=0;i<_size;++i)
      _pData[i]=inVector._pData[i];
   
   cout << "constructeur par instance en parametre" << endl;
}

/**
 * \fn DoubleVector :: DoubleVector(int size)
 * \brief Constructeur utilisant un entier
 * \param size taille max du vecteur 
 */

DoubleVector :: DoubleVector(int size): _size(size)
{
  _pData = new double[size];
}


/**
 * \fn DoubleVector :: ~DoubleVector()
 * \brief Destructeur par defaut de la classe DoubleVector
 */
DoubleVector :: ~DoubleVector()
{
   delete [] _pData;
   cout << "appel du destructeur" << endl;
}

/**
 * \fn DoubleVector & DoubleVector :: operator = (const DoubleVector & DoubleVector)
 * \brief surcharge de l'operateur =
 * \param inVector on veut a = inVector
 */

DoubleVector & DoubleVector :: operator= (const DoubleVector & inVector)
{
   if( &inVector != this)
   {
      delete [] _pData;
      _pData = new double [_size = inVector._size];
      for(int i=0;i<_size;++i)
         _pData[i]=inVector._pData[i];
      cout << "surcharge d'operateur =" << endl;
   }
   return * this; // pour pouvoir effectuer chaine1=chaine2=chaine3 etc...
}

/**
 * \fn DoubleVector :: DoubleVector operator+ (const DoubleVector & s1, const DoubleVector & s2)
 * \brief surcharge de l'operateur +
 * \param s1 on veut a = s1 + s2
 * \param s2
 * Construira une instance de la classe de DoubleVector avec une taille de la taille max des deux tableau
 */


DoubleVector operator+ (const DoubleVector & s1, const DoubleVector & s2)
{
   
   int taille_max,taille_min,i;
   double * tab,*tab_fin,*x1,*x2;
   
   taille_max = (s1.getSize()>s2.getSize())? s1.getSize():s2.getSize();
   taille_min = (s1.getSize()>s2.getSize())? s2.getSize():s1.getSize();
   
   tab_fin    = (s1.getSize()>s2.getSize())? s1.getPData():s2.getPData();
   x1 = s1.getPData();
   x2 = s2.getPData();
   
   tab = new double(taille_max);
   
   for(i=0;i<taille_min;++i)
      tab[i]=x1[i]+x2[i];
   
   for(i=taille_min;i<taille_max;++i)
      tab[i] = tab_fin[i];
   
    DoubleVector temp(tab,taille_max);
    delete[] tab;
    return temp;
}

/**
 * \fn std::ostream & operator<< (const osteam & flux, const DoubleVector & v)
 * \brief surcharge de l'operateur <<
 * \param flux flux que l'on veut utiliser
 * \param v DoubleVector que l'on veut afficher
 * \return retourne le flux surcharge
 */

std::ostream & operator<< (std::ostream & flux, const DoubleVector & v)
{
   double * tab = v.getPData();
   int taille = v.getSize();
   for(int i = 0; i<taille;++i)
      flux << tab[i]; 
   return flux;
}

/**
 * \fn double & operator[] (const int i)
 * \brief surcharge de l'operateur []
 * \param i indice du nombre que l'on veux voir,modifier
 * \return retourne le nombre du vecteur desire
 */

double & DoubleVector::operator[] (int i)
{
   return(_pData[i]);
}