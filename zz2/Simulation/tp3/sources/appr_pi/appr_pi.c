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
#include "mt19937ar.h"

#define TIR_EXP 10000

double calcul_pi();

/**
 * \fn int main(int,char**)
 * \brief effectue une approximation de pi et effectue des calculs stats
 *
 */
int main(int argc, char** argv) {

    int i,nb_exp;
    double moy=0.0,intervalle=0.0,*tab,annexe;
    unsigned long init[4];
    
    srand(time(0));
    /*on se sert du generateur GNU seulement pour initialiser le Mersenne Twister*/
    init[0]= (unsigned long) rand();
    init[1]= (unsigned long) rand();
    init[2]= (unsigned long) rand();
    init[3]= (unsigned long) rand();
    init_by_array(init,4); /* initialisation du generateur mersenne twister */
    
    printf("approximateur de PI\n");
    printf("Saisir le nombre d'experience souhaitee?\n");
    scanf("%d",&nb_exp);
    tab = (double*)malloc(nb_exp*sizeof(double));
    if(!tab)
    {
        fprintf(stderr,"erreur allocation tableau \n");
        exit(EXIT_FAILURE);
    }
    printf("------------------------------------------\n");
    printf("------------------------------------------\n");
    for(i=0;i<nb_exp;++i)
    {
        printf("experience %d:\n",i);
        tab[i]=calcul_pi();
        printf("Evaluation de pi : %lf \n",tab[i]);
        moy += tab[i];
    }
    printf("------------------------------------------\n");
    printf("------------------------------------------\n");
    printf("exploitation des resultat\n");
    moy /= (double)nb_exp;
    printf("La moyenne est de : %lf \n",moy);
    for(i=0;i<nb_exp;++i)
    {
        intervalle += (tab[i] - moy)*(tab[i] - moy);
    }
    intervalle /= (double)(nb_exp -1);
    intervalle = sqrt(intervalle/(double)nb_exp);
    printf("veuillez saisir la valeur de t selon le nombre d'experience\n");
    scanf("%lf",&annexe);
    intervalle *= annexe;
    printf("Intervalle de confiance a 95percent %lf \n",intervalle);
    free(tab);
    return (EXIT_SUCCESS);
}

/**
 * \fn double calcul_pi()
 * \brief Effectue une experience sur la calcul de pi
 * \return valeur de pi approxime
 *
 */
double calcul_pi()
{
    int valide,i;
    double x,y;

    valide = 0;
    for(i=0;i<TIR_EXP;++i)
    {
        x = genrand_real2();
        y = genrand_real2();
        if(sqrt(x*x+y*y)<= 1.0)
           ++valide;
    }
    return(4.0*((double)valide/(double)TIR_EXP));
}
