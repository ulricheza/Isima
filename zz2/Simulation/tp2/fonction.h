/**
 * \file fonction.h
 * \brief Generation de nombres pseudo aleatoires suivant differentes ditributions
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \version 0.1
 * \date Jeudi 7 octobre 2010
 *
 * Tp2 de simulation
 *
 */


#ifndef __FONCTION_H_EJC__
#define __FONCTION_H_EJC__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define PI 3.141592653


/**
 * \fn float gene_rand()
 * \brief fonction qui genere un nombre aleatoire entre 0 et 1
 * \return valeur aleatoire reele entre 0 et 1
 *
 */
float gene_rand();

/**
 * \fn int infini(double value)
 * \brief verifie si une valeur est infini
 * \param value valeur a tester
 * \return 0 si valeur infini
 */
int infini();
 
/**
 * \fn int * test_histogramme_ABC()
 * \brief simule le recencement d'especes
 * \return le tableau d'entier contenant le nombre d'elements de chaque espece
 */

int * test_histogramme_ABC();

/**
 * \fn int * loi_uniforme(float a, float b)
 * \brief fonction qui effectue un tirage selon une loi uniforme entre a et b
 * \param a borne inferieure de la loi uniforme
 * \param b borne superieure de la loi uniforme
 * \return un tableau contenant le nombre de tirage effectue parmi des intervalles donnés
 *
 * Pour simuler ce fonctionnement, on utilise la forme explicite de la fonction inverse de la 
 * fonction de repartition.
 * ici F^1(x) = A+(B-A)*x;
 */

 int * loi_uniforme(double , double);

 /**
 * \fn  int * loi_exponentielle_neg(float moyenne,float max)
 * \brief fonction qui effectue un tirage selon une loi exponentielle negative de moyenne M  
 * \param moyenne moyenne de la loi exponentielle
 * \param max valeur maximale tolere
 * \return un tableau contenant le nombre de tirage effectue parmi des intervalles donnés
 *
 * Pour simuler ce fonctionnement, on utilise la forme explicite de la fonction inverse de la 
 * fonction de repartition.
 * ici F^1(x) = -Moyenne*ln(1-valeur_tiree);
 */

 int * loi_exponentielle_neg(double ,double );
 
 /**
 * \fn  int * loi_normale(float moyenne, float ecart_type,float min, float max)
 * \brief fonction qui effectue des tirages selon la loi normale utilise la methode de Box-Muller  
 * \param moyenne moyenne de la loi normale
 * \param ecart_type ecart type de la loi normale
 * \param min valeur min tolere
 * \param max valeur maximale tolere
 * \return un tableau contenant le nombre de tirage effectue parmi des intervalles donnés
 *
 * Pour simuler ce fonctionnement, on utilise la methode de Box-Muller:
 * T1=sqrt(-2*ln(u1))*cos(2*pi*u2)
 * T1=sqrt(-2*ln(u1))*sin(2*pi*u2)
 * X1 = moyenne + ecart_type*T1
 * X2 = moyenne + ecart_type*T2
 */
 
int * loi_normale(double, double, double ,double);

/**
 * \fn int gene_nombre_AB(int min, int max)
 * \brief retourne un nombre entre min et max
 * \param min valeur min possible
 * \param max valeur max possible
 */
 
int gene_nombre_AB(int, int);

/**
 *\fn int * histogramme_gene(int * data,int size, int effectif)
 *\brief fonction generale de distributions selon un histogramme donne
 *\param data tableau representant un l'effectif des classes
 *\param size nombre de classe
 *\param effectif nombre total d'element
 *\return tableau contenant le nombre de tirage par classe
 */
 
int * histogramme_gene(int *, int, int );

 /**
 * \fn  int * loi_normale_rejection(float moyenne, float ecart_type, float minX, float maxX)
 * \brief fonction qui effectue des tirages selon la loi normale utilise la methode de rejection
 * \param moyenne moyenne de la loi normale
 * \param ecart_type ecart type de la loi normale
 * \param min valeur min tolere
 * \param max valeur maximale tolere
 * \return un tableau contenant le nombre de tirage effectue parmi des intervalles donnés
 *
 * voir algo sujet
 */
int * loi_normale_rejection(double moyenne, double ecart_type, double minX, double maxX);

#endif