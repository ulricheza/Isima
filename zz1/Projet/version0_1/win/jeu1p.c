/**
 * \file jeu1p.c
 * \brief version 1 joueur de navy battle en texte
 * \author Maxime Escourbiac 
 * \version 1.0
 * \date Dimanche 7 mars 2010
 *
 * 
 */

#include "jeu1p.h"




int main(int argc, char * argv[])
{

   int rep_tir_cpu;
   int z,i,x,y;
   int * permit_tir;
   var_game_t * var;

   init_var(1,&var);

   permit_tir = (int *)malloc(100*sizeof(int));
   if(permit_tir == NULL)
   {
      fprintf(var->log_erreur,"erreur dans l'allocation de permit_tir\n");
      exit_err(var);
   }
   for(i=0;i<100;i++)
      permit_tir[i] = i;

   clear

   printf("-----------------------------------------------------\n");
   printf("Bienvenue sur la version 0.1 de Navy Battle \n");
   printf("Cette version sert de test pour le moteur du jeu\n");
   printf("attention les cases vont de 0 a 9               \n");
   printf("-----------------------------------------------------\n");
   printf("-----------------------------------------------------\n");
   printf("placement des bateaux CPU\n");
   placement_alea(var);
   printf("-----------------------------------------------------\n");
   printf("placement de vos bateaux\n");
   placement_hum(var);
   printf("-----------------------------------------------------\n");
   printf("DEBUT DU JEU\n");
   clear
   while(var->remain_bat_cpu != 0 && var->remain_bat_hum != 0)
   {
      printf("-----------------------------------------------------\n");
      printf("-----------------------------------------------------\n");
      printf("votre matrice cible \n");
      affic_mat(var->mer_cible_hum,0);
      printf("-----------------------------------------------------\n");
      printf("-----------------------------------------------------\n");
      printf("votre matrice home\n");
      affic_mat(var->mer_home_hum,1);
      printf("-----------------------------------------------------\n");
      printf("-----------------------------------------------------\n");
      printf("A vous de tirer !\n");
      z = tir_humain(var);
      clear
      var->mer_cible_hum[z] = reponse_tir(z,1,var);
      switch(var->mer_cible_hum[z])
      {
         case 0: printf("Votre tir a rate\n");
                 break;
         case 1: printf("Votre tir a touche un bateau\n");
                 break;
         case 2: printf("Votre tir a touche et coule un bateau\n");
                 var->remain_bat_cpu = var->remain_bat_cpu - 1;
                 break;
      }
      printf("Au CPU de tirer\n");
      z = tir_alea(permit_tir, &rep_tir_cpu, var);
      trans1D_2D(z,&x,&y);
      printf("le CPU a tire a la case %d %d \n",x,y);
      switch(rep_tir_cpu)
      {
         case 0: printf("Son tir a rate\n");
                 break;
         case 1: printf("Son tir a touche un de vos bateau\n");
                 break;
         case 2: printf("Son tir a touche et coule un de vos bateau\n");
                 break;
      }
   }
   if(var->remain_bat_cpu == 0)
      printf("Bravo vous avez gagne!!!\n");
   else
      printf("dommage vous avez perdu \n");

   free(var->mer_home_cpu);
   free(var->mer_home_hum);
   free(var->mer_cible_cpu);
   free(var->mer_cible_hum);
   free(permit_tir);
   fclose(var->log_erreur);
   free(var);
   return(EXIT_SUCCESS);
}

void affic_mat(int * mer,int type)
{
   int i,j;
   printf("  0 1 2 3 4 5 6 7 8 9\n");
   if(type == 0) /*mer cible*/
   {
      for(i=0;i<10;i++)
      {
         printf("%d ",i);
         for(j=0;j<10;j++)
         {
            switch(mer[10*i+j])
            {
               case -1: printf("  ");
                        break;
               case 0: printf("O ");
                       break;
               case 1:
               case 2: printf("X ");
                       break;
            }
         }
         printf("\n");
      }
   }
   else /*mer home*/
   {
      for(i=0;i<10;i++)
      {
         printf("%d ",i);
         for(j=0;j<10;j++)
         {
            switch(mer[10*i+j])
            {
               case -1: printf("  ");
                        break;
               case 0:
               case 1:
               case 2:
               case 3:
               case 4:
                       printf("X ");
                       break;
               case 5: printf("O ");
                       break;
               case 6: printf("# ");
            }
         }
         printf("\n");
      }
   }
}
