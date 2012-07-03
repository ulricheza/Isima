/**
 * \file appr_pi.c
 * \brief Programme d'approximation de la valeur pi par la methode de monte_carlo
 * \author Maxime Escourbiac Jean Christophe Septier
 * \version 1.0
 * \date Mercredi 12 Novembre 2010
 *
 *  Programme d'approximation de la valeur pi par la methode de monte_carlo
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <unistd.h>
#include "mt19937ar.h"

float calcul_pi(int nb_tirage);

/**
 * \fn int main(int,char**)
 * \brief effectue une approximation de pi et effectue des calculs stats
 *
 * Le code est volotairement passe en float pour pouvoir comparer les performances
 * avec le m
 */
int main(int argc, char** argv) {

    int i,nb_exp,nb_tirage;
    float moy=0.0,pi_intermediate;

    //Variables servant pour le calcul de performance
    //Attention code fonctionnant que sur Linux/Unix.
    struct timeval tv1,tv2;
    long long tempsS,tempUS;

    /*initialisation du mersenne twister ( Exemple tire du code de matsumoto)
    On initialise de la meme facon pour comparer les resultats avec le code genere*/
    unsigned long inittab[4]={0x123, 0x234, 0x345, 0x456}, length=4;
    init_by_array(inittab, length);


    printf("approximateur de PI\n");
    printf("Saisir le nombre de point à tirer\n");
    scanf("%d",&nb_tirage);
    printf("Saisir le nombre de replications souhaitee\n");
    scanf("%d",&nb_exp);

    gettimeofday(&tv1,NULL);

    printf("------------------------------------------\n");
    printf("------------------------------------------\n");
    for(i=0;i<nb_exp;++i)
    {
        printf("experience %d:\n",i);
        pi_intermediate =calcul_pi(nb_tirage);
        printf("Evaluation de pi : %lf \n",pi_intermediate);
        moy += pi_intermediate;
    }
    printf("------------------------------------------\n");
    printf("------------------------------------------\n");
    printf("exploitation des resultat\n");
    moy /= (float)nb_exp;
    printf("La moyenne est de : %lf \n",moy);

    gettimeofday(&tv2,NULL);
    tempsS  =(tv2.tv_sec-tv1.tv_sec);
    tempUS =(tv2.tv_usec-tv1.tv_usec);
    printf("temps d'execution : %lld s %lld us \n", tempsS, tempUS);
    
    return (EXIT_SUCCESS);
}

/**
 * \fn float calcul_pi()
 * \brief Effectue une experience sur la calcul de pi
 * \return valeur de pi approxime
 *
 */
float calcul_pi(int nb_tirage)
{
    int valide,i;
    float x,y;

    valide = 0;
    for(i=0;i<nb_tirage;++i)
    {
        x = (float)genrand_real2();
        y = (float)genrand_real2();
        if(sqrt(x*x+y*y)<= 1.0)
           ++valide;
    }
    return(4.0*((float)valide/(float)nb_tirage));
}
