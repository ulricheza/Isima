/* 
 * File:   vecteur.hxx
 * Author: escourbi
 *
 * Created on November 10, 2010, 10:21 AM
 */

#ifndef _VECTEUR_HXX
#define	_VECTEUR_HXX

#include <iostream>
using namespace std;

template <typename T> class Vecteur;
//obligatoire quand on utilise une methode friend dans une classe template
template<typename U>
std::ostream & operator<< (std::ostream & flux, const Vecteur<U> & v);

template <typename T>
class Vecteur{
private:
      int _size;
      T * _pData;
      int _index;
   public:
      //Constructeur & destructeur
      Vecteur();
      Vecteur(T * inVector,int size);
      Vecteur(const Vecteur<T> & inVector);
      Vecteur(int size);
      ~Vecteur() ;
      //getter
      int getSize() const   {return _size;}
      T * getPData() const  {return _pData;}
      //methode de classe vector
      //on implemente cette methode pour travailler sur le comportement
      //dynamique de pour la taille tu vecteur
      void ajout_fin(const T & x);
      //surcharge d'operateur
      Vecteur<T> & operator= (const Vecteur<T> & inVector);
      // le <> permet de dire qu'on travaille avec le meme template
      friend std::ostream & operator<< <>(std::ostream & flux, const Vecteur<T> & v);
      T & operator[] (int i);

};

template <typename T>
Vecteur<T> operator+ (const T & , const T & );

#include "vecteur.cxx"
#endif	/* _VECTEUR_HXX */

