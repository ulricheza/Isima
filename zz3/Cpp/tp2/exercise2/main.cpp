/* 
 * File:   main.cpp
 * Author: Maxime
 *
 * Created on 25 octobre 2011, 20:06
 */

#include <iostream>

using namespace std;

/*
 * Calcul des factorielles en patron de conception
 */
template < unsigned long N >
struct fact{
    static const unsigned long valeur = N * fact<N-1>::valeur;
};

template <>
struct fact<0> {
    static const unsigned long valeur = 1;
};

/*
 * Calcul de puissance entiere
 */
template <long N>
inline double puiss (double x)
{
    return (x * puiss<N-1>(x));
}

template<>
inline double puiss<0> (double x)
{
    return 1.0;
}


/*
 * Calcul de la serie de taylor de l'exponentielle
 */
template < unsigned long N >
inline double expT (double x)
{
    return ( puiss<N>(x)/fact<N>::valeur + expT<N-1>(x));
}

template<>
inline double expT<0> (double x)
{
    return ( 1.0 );
}

/*
 * Calcul de la serie de taylor du cosinus
 */
template < unsigned long N >
inline double cosT (double x)
{
    return ( puiss<N>(-1.0)*(puiss<2*N>(x)/fact<2*N>::valeur) + cosT<N-1>(x));
}

template<>
inline double cosT<0> (double x)
{
    return ( 1.0 );
}

/*
 * Calcul de la serie de taylor du sinus
 */
template < unsigned long N >
inline double sinT (double x)
{
    return ( puiss<N>(-1.0)*(puiss<2*N + 1>(x)/fact<2*N + 1>::valeur) + sinT<N-1>(x));
}

template<>
inline double sinT<0> (double x)
{
    return ( 1.0 );
}

/**
 *
 * @param argc
 * @param argv
 * @return
 */

int main(int argc, char** argv) {
    cout << "fact de 10 = " << fact<10>::valeur << endl;
    cout << "Taylor degre 5 :: exp(3) = " << expT<5>(3.0) << endl;
    cout << "Taylor degre 5 :: cos(3) = " << cosT<5>(3.0) << endl;
    cout << "Taylor degre 5 :: sin(3) = " << sinT<5>(3.0) << endl;
    return 0;
}

