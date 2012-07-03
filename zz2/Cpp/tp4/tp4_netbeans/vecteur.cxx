/*
 * File:   vecteur.cxx
 * Author: escourbi
 *
 * Created on November 10, 2010, 10:21 AM
 */



/**
 * \fn Vecteur<T> :: Vecteur(): _size(0), _pData(0)
 * \brief Constructeur par defaut de la classe DoubleVector
 */

template <typename T>
Vecteur<T> :: Vecteur(): _size(0), _pData(0),_index(0)
{
   cout << "constructeur par defaut" << endl;
}

/**
 * \fn Vecteur<T> :: Vecteur(T * tab,int size) : _size(size)
 * \brief Constructeur utilisant une chaine de caractere
 * \param tab tableau de type T
 * \param size taille du tableau passer en parametre
 */

template <typename T>
Vecteur<T> :: Vecteur(T * tab,int size) : _size(size),_index(size)
{
   int i;
   _pData = new T[_size];
   for(i=0;i<size;++i)
      _pData[i]=tab[i];

   cout << "constructeur par tableau et int size" << endl;
}

/**
 * \fn Vecteur<T> :: Vecteur(const Vecteur<T> & inVector)
 * \brief Constructeur utilisant une instance de classe DoubleVector
 * \param inVector instance de classe DoubleVector
 */

template <typename T>
Vecteur<T> :: Vecteur(const Vecteur<T> & inVector)
{
   _pData = new T[_size = inVector._size];
   for(int i=0;i<_size;++i)
      _pData[i]=inVector._pData[i];
   _index = _size;
   cout << "constructeur par instance en parametre" << endl;
}

/**
 * \fn Vecteur<T> :: Vecteur(int size): _size(size)
 * \brief Constructeur utilisant un entier
 * \param size taille max du vecteur
 */

template <typename T>
Vecteur<T> :: Vecteur(int size): _size(size)
{
  _pData = new T[size];
}


/**
 * \fn Vecteur<T> :: ~Vecteur()
 * \brief Destructeur par defaut de la classe DoubleVector
 */
template <typename T>
Vecteur<T> :: ~Vecteur()
{
   delete [] _pData;
   cout << "appel du destructeur" << endl;
}

/**
 * \fn Vecteur<T> & Vecteur<T> :: operator= (const Vecteur<T> & inVector)
 * \brief surcharge de l'operateur =
 * \param inVector on veut a = inVector
 */

template <typename T>
Vecteur<T> & Vecteur<T> :: operator= (const Vecteur<T> & inVector)
{
   if( &inVector != this)
   {
      delete [] _pData;
      _pData = new T[_size = inVector._size];
      for(int i=0;i<_size;++i)
         _pData[i]=inVector._pData[i];
      cout << "surcharge d'operateur =" << endl;
   }
   return * this; // pour pouvoir effectuer chaine1=chaine2=chaine3 etc...
}

/**
 * \fn Vecteur<T> operator+ (const Vecteur<T> & s1, const Vecteur<T> & s2)
 * \brief surcharge de l'operateur +
 * \param s1 on veut a = s1 + s2
 * \param s2
 * Construira une instance de la classe de DoubleVector avec une taille de la
 * taille max des deux tableau
 */

template <typename T>
Vecteur<T> operator+ (const Vecteur<T> & s1, const Vecteur<T> & s2)
{

   int taille_max,taille_min,i;
   T * tab,*tab_fin,*x1,*x2;

   taille_max = (s1.getSize()>s2.getSize())? s1.getSize():s2.getSize();
   taille_min = (s1.getSize()>s2.getSize())? s2.getSize():s1.getSize();

   tab_fin    = (s1.getSize()>s2.getSize())? s1.getPData():s2.getPData();
   x1 = s1.getPData();
   x2 = s2.getPData();

   tab = new T(taille_max);

   for(i=0;i<taille_min;++i)
      tab[i]=x1[i]+x2[i];

   for(i=taille_min;i<taille_max;++i)
      tab[i] = tab_fin[i];

    Vecteur<T> temp(tab,taille_max);
    delete[] tab;
    return temp;
}

/**
 * \fn std::ostream & operator<< (std::ostream & flux, const Vecteur<T> & v)
 * \brief surcharge de l'operateur <<
 * \param flux flux que l'on veut utiliser
 * \param v DoubleVector que l'on veut afficher
 * \return retourne le flux surcharge
 */
template <typename T>
std::ostream & operator<< (std::ostream & flux, const Vecteur<T> & v)
{
   T * tab = v.getPData();
   int taille = v.getSize();
   for(int i = 0; i<taille;++i)
      flux << tab[i];
   return flux;
}

/**
 * \fn T & DoubleVector::operator[] (int i)
 * \brief surcharge de l'operateur []
 * \param i indice du nombre que l'on veux voir,modifier
 * \return retourne le nombre du vecteur desire
 */

template <typename T>
T & Vecteur<T>::operator[] (int i)
{
   return(_pData[i]);
}

template <typename T>
void Vecteur<T>::ajout_fin(const T& x)
{
    T * temp;
    int i = 0;
        if(_index == _size)
    {
        cout << "agrandissement du vecteur" << endl;
        _size += _size/2 + 1;
        temp = new T[_size];
        for(i=0;i<_index;++i)
            temp[i]= _pData[i];
        delete[] _pData;
        _pData = temp;
    }
    _pData[_index++] = x;
}
