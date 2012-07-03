/**
 * \file fibo.c
 * \brief Implemente la fonction de fibonacci
 * \author Maxime Escourbiac Jean Christophe Septier
 * \version 1.0
 * \date Mercredi 12 Novembre 2010
 * 
 *
 */

#include<stdio.h>
#include<stdlib.h>


int main(int argc, char ** argv)
{
   int nb_generation,temp,i;
   int u1 = 0;
   int u2 = 1;
   printf("combien de generation desirer vous ?\n");
   scanf("%d",&nb_generation);

   for(i=1;i<nb_generation;++i)
   {
      temp = u1+u2;
      u1 = u2;
      u2 = temp;
   }
   printf("resultat %d \n",u2);
   exit(EXIT_SUCCESS);
}      
   
   