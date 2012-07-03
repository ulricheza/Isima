/**
 * \file core.c
 * \brief rassemblement des fonctiosn developpees en 1er partie 
 * \author Maxime Escourbiac 
 * \version 1.0
 * \date Jeudi 4 mars 2010
 *
 * 
 */


#include "core.h"


/*debut des fonctions*/

 void trans1D_2D (int z, int * x, int * y)
 {
     *x = z/10;
     *y = z - (*x)*10;
 }

  int trans2D_1D (int x, int y)
 {
    return (10*x+y);
 }

void init_fic_erreur(var_game_t * var)
{
   struct tm * actual;
   /*recuperation de la date actuelle*/
   time_t actual_temp;
   time(&actual_temp);
   actual = localtime(&actual_temp);

   /*ouverture du fichier d'erreur*/
   var->log_erreur = fopen("log_erreur.txt","a");

   if(var->log_erreur != NULL)
   {
      /*ecriture de l'en-tete du fichier d'erreur*/
      fprintf(var->log_erreur,"-----------------------------------\n");
      fprintf(var->log_erreur,"-----------------------------------\n");
      fprintf(var->log_erreur,"session du %d/ %d/ %d a %d h%d \n",actual->tm_mday, actual->tm_mon+1,(1900 + actual->tm_year),actual->tm_hour,actual->tm_min);
   }
   else 
      exit(EXIT_FAILURE);

}

void exit_err(var_game_t * var)
{
   fclose(var->log_erreur); /*fermeture du fichier log_erreur.txt*/
   exit(EXIT_FAILURE);
}

void init_var(int cpu,var_game_t ** var)
{
  int i;

  /*allocation de la structure de variable*/
   *var = (var_game_t *)malloc(sizeof(var_game_t));

   if(*var == NULL)
      exit(EXIT_FAILURE);

   /*affectation des valeurs aux variables de la structure*/
   (*var)->remain_bat_hum = 5;
   (*var)->remain_bat_cpu = 5;

   /*initialisation du fichier d'erreur*/
   init_fic_erreur(*var);

   (*var)->mer_cible_hum = (int *)malloc(100*sizeof(int));
   (*var)->mer_home_hum = (int *)malloc(100*sizeof(int));

   /*correctif 1.1*/
   if( (*var)->mer_cible_hum == NULL || (*var)->mer_home_hum == NULL)
   {
      fprintf((*var)->log_erreur,"Erreur dans l'allocation des mers hum \n");
      exit_err(*var);
   }
   /*fin correctif 1.1*/

   for(i=0;i<100;i++)
   {
      (*var)->mer_cible_hum[i] = -1;
      (*var)->mer_home_hum[i] = -1;
   }

   if(cpu == 1)
   {
      (*var)->mer_home_cpu = (int *)malloc(100*sizeof(int));
      (*var)->mer_cible_cpu = (int *)malloc(100*sizeof(int));
        /*correctif 1.1*/
      if( (*var)->mer_cible_cpu == NULL || (*var)->mer_home_cpu == NULL)
      {
         fprintf((*var)->log_erreur,"Erreur dans l'allocation des mers cpu\n");
         exit_err(*var);
      }
        /*fin correctif 1.1*/  
      for(i=0;i<100;i++)
      {
         (*var)->mer_cible_cpu[i] = -1;
         (*var)->mer_home_cpu[i] = -1;
      }
   }


   /*initialisation des flottes*/
   /*1er bateau*/
   (*var)->flotte_hum[0].vie = 2;
   (*var)->flotte_cpu[0].vie = 2;
   (*var)->flotte_hum[0].taille = 2;
   (*var)->flotte_cpu[0].taille = 2;

   /*2ieme bateau*/
   (*var)->flotte_hum[1].vie = 3;
   (*var)->flotte_cpu[1].vie = 3;
   (*var)->flotte_hum[1].taille = 3;
   (*var)->flotte_cpu[1].taille = 3;

   /*3ieme bateau*/
   (*var)->flotte_hum[2].vie = 3;
   (*var)->flotte_cpu[2].vie = 3;
   (*var)->flotte_hum[2].taille = 3;
   (*var)->flotte_cpu[2].taille = 3;

   /*4ieme bateau*/
   (*var)->flotte_hum[3].vie = 4;
   (*var)->flotte_cpu[3].vie = 4;
   (*var)->flotte_hum[3].taille = 4;
   (*var)->flotte_cpu[3].taille = 4;

   /*5ieme bateau*/
   (*var)->flotte_hum[4].vie = 6;
   (*var)->flotte_cpu[4].vie = 6;
   (*var)->flotte_hum[4].taille = 6;
   (*var)->flotte_cpu[4].taille = 6;


}


void placement_alea(var_game_t * var)
{
   int * permit_h = (int*) malloc(90*sizeof(int));
   int * permit_v = (int*) malloc(90*sizeof(int));

   int libre_h = 90;
   int libre_v = 90;

   int x,y,i,j,k,z,bateau;

   srand(time(NULL));

   /*correctif 1.2*/
   if( permit_h == NULL || permit_v == NULL)
   {
      fprintf(var->log_erreur,"Erreur dans l'allocation des matrices de permitivite lors du placement alea\n");
      exit_err(var);
   }
   /*fin correctif 1.2*/

   /*initialisation des matrices de permitivite*/
   for(i=0;i<90;i++)      /*init permit_v*/
   {
      permit_v[i]= i ;
   }

   x=0;
   y=0;

   for(i=0;i<90;i++)     /*init permit_h*/
   {
      if(y == 9)
      {
         x++;
         y = 0;
      }
      permit_h[i]= x*10 + y;
      y++;
   }
   /*fin initialisation*/


   for(bateau=0;bateau<5;bateau++)
   {
      /*debut placement bateau*/
      /*correctif version 1.1 */

      if(libre_h == 0 || libre_v == 0)
      {
         if(libre_h == 0)
           var->flotte_cpu[bateau].sens=1;
         else
           var->flotte_cpu[bateau].sens=0;
      }
      else
         var->flotte_cpu[bateau].sens = rand()%2;
      /*fin correctif*/

      if(var->flotte_cpu[bateau].sens == 0) /*si sens horizontal*/
      {
         z= choix_alea(permit_h,libre_h);
         trans1D_2D(z,&x,&y);
         var->flotte_cpu[bateau].x = x;
         var->flotte_cpu[bateau].y = y;

         /*positionnement du bateau*/
         for(i=0;i<var->flotte_cpu[bateau].taille;i++)
            var->mer_home_cpu[z+i] = bateau;

         /*mise a jour de la matrice de permitivite */
         /* a cause du placement du bateau          */
         for(i=-1;i<=1;i++)
         {
            for(j=-1;j<=var->flotte_cpu[bateau].taille;j++)
            {
               suppr_point(permit_h,&libre_h,i+x,j+y);
               suppr_point(permit_v,&libre_v,i+x,j+y);
            }
         }
      }
      else /*si sens vertical*/
      {
         z= choix_alea(permit_v,libre_v);
         trans1D_2D(z,&x,&y);
         var->flotte_cpu[bateau].x = x;
         var->flotte_cpu[bateau].y = y;

         /*positionnement du bateau*/
         for(i=0;i<var->flotte_cpu[bateau].taille;i++)
            var->mer_home_cpu[z+10*i] = bateau;

         /*mise a jour de la matrice de permitivite */
         /* a cause du placement du bateau          */
         for(i=-1;i<=1;i++)
         {
            for(j=-1;j<=var->flotte_cpu[bateau].taille;j++)
            {
               suppr_point(permit_h,&libre_h,j+x,i+y);
               suppr_point(permit_v,&libre_v,j+x,i+y);
            }
         }
      }
      /*fin placement bateau*/

      /*debut maj des matrices de permitivites */
      if(bateau != 4)
      {
         /*on supprime les points selon la taille du bateau suivant*/
         /* pour la matrice horizontale*/
         for(j=1;j<var->flotte_cpu[bateau+1].taille;j++)
         {
            for(i=0;i<10;i++)
               suppr_point(permit_h,&libre_h,i,10-j);
         }

         /*pour la matrice verticale*/
         for(i=1;i<var->flotte_cpu[bateau+1].taille;i++)
         {
            for(j=0;j<10;j++)
               suppr_point(permit_v,&libre_v,10-i,j);
         }

         /*MAJ matrices selon les bateaux precedent*/
         for(k=bateau;k>=0;k--)
         {
            if(var->flotte_cpu[k].sens == 0) /*cas bateau horizontal*/
            {
               /*pour la partie horizontale*/
               for(j=2;j<=var->flotte_cpu[bateau+1].taille;j++)
               {
                  for(i=-1;i<=1;i++)
                     suppr_point(permit_h,&libre_h,i+var->flotte_cpu[k].x,var->flotte_cpu[k].y -j);
               }
               /*pour la partie verticale*/
               for(j=-1;j<=var->flotte_cpu[k].taille;j++)
               {
                  for(i=2;i<=var->flotte_cpu[bateau+1].taille;i++)
                     suppr_point(permit_v,&libre_v,var->flotte_cpu[k].x -i,var->flotte_cpu[k].y +j);
               }
            }
            else /*cas bateau vertical*/
            {
               /*pour la partie horizontale*/
               for(j=2;j<=var->flotte_cpu[bateau+1].taille;j++)
               {
                  for(i=-1;i<=var->flotte_cpu[k].taille;i++)
                     suppr_point(permit_h,&libre_h,i+var->flotte_cpu[k].x,var->flotte_cpu[k].y -j);
               }
               /*pour la partie verticale*/
               for(j=-1;j<=1;j++)
               {
                  for(i=2;i<=var->flotte_cpu[bateau+1].taille;i++)
                     suppr_point(permit_v,&libre_v,var->flotte_cpu[k].x -i,var->flotte_cpu[k].y +j);
               }
             }
         } 
       }
   }
   free(permit_v);
   free(permit_h);

}


int choix_alea(int * permit, int max)
{
   int z;
   static int init = 0;
   if(init==0)
   {
      srand(time(NULL));
      init = 1;
   }
   z = rand()%max;
   z= permit[z];

   return z;
}

void suppr_point(int * permit, int * max, int x, int y)
{
   int i,z;

   if( (x>=0) && (x<10) && (y>=0) && (y<10) )
   {
      z= trans2D_1D(x,y);
      i = 0;
      while(i<*max && permit[i]!=z)
         i++;

      if(i<*max)
      {
         permit[i]=permit[*max-1];
         *max = *max - 1;
      }
   }
}

int placement_valide (int x, int y, int sens,int taille,var_game_t * var)
{
   int valid = 1;
   int i,j,z;
   if(x>=0 && x<10 && y>=0 && y<10) /*test appartenance tete dans grille */ 
   {
       if(sens == 0) 
       {
          if((taille+y)>10) /*test si le bateau rentre dabns la grille*/
             valid=0;
          for(i=-1;i<=1;i++)
          {
             for(j=-1;j<=taille;j++) /*double boucle pour tester ls collisions*/
             {
                if((x+i)>=0 && (x+i)<10 && (y+j)>=0 && (y+j)<10)
                {
                   z= trans2D_1D((x+i),(y+j));
                   if(var->mer_home_hum[z]!= -1)
                      valid=0;
                }
             }
          }
       }
       else
       {
          if((taille+x)>10) /*test si le bateau rentre dabns la grille*/
             valid=0;
          for(j=-1;j<=1;j++)
          {
             for(i=-1;i<=taille;i++) /*double boucle pour tester ls collisions*/
             {
                if((x+i)>=0 && (x+i)<10 && (y+j)>=0 && (y+j)<10)
                {
                   z= trans2D_1D((x+i),(y+j));
                   if(var->mer_home_hum[z]!=-1)
                      valid=0;
                }
             }
          }
       }
   }
   else
      valid = 0;

   return valid;
}

int reponse_tir(int coord ,int provenance,var_game_t * var)
{
   int reponse = 1;
   int temp ;

   if(provenance == 0)
   {
      /*cas tir procenant du cpu ou joueur en reseau*/
      temp = var->mer_home_hum[coord];
      switch (temp)
      {
         case -1 : reponse = 0;              /*tir rate*/
                   var->mer_home_hum[coord]=5;
                   break;
         case 0:
         case 1:
         case 2:
         case 3:
         case 4:  var->mer_home_hum[coord]=6;    /*tir touche*/
                  var->flotte_hum[temp].vie = var->flotte_hum[temp].vie -1;
                  if(var->flotte_hum[temp].vie == 0)  /*test si coule*/
                     reponse = 2;
                  break;
      }
   }
   else
   {
       /*cas tir provenant joueur humain*/
       temp = var->mer_home_cpu[coord];
       switch (temp)
       {
         case -1 : reponse = 0;
                   var->mer_home_cpu[coord]=5;
                   break;
         case 0:
         case 1:
         case 2:
         case 3: 
         case 4:  var->mer_home_cpu[coord]=6;
                  var->flotte_cpu[temp].vie = var->flotte_cpu[temp].vie -1;
                  if(var->flotte_cpu[temp].vie == 0)
                     reponse = 2;
                  break;
       }
   }

   return reponse;
}

int tir_humain(var_game_t * var)
{
   int x,y,z;
   int valide = 0;
   /*cette partie devra prendre en compte la gestion des evenements*/
   /*realise a l'aide de la bibliotheque SDL                       */
   /*pour l'instant on se limitera a une demande en texte          */
   printf("-----------------------------------\n");
   printf("Sequence de tir active\n");

   while(valide == 0)
   {
      printf("ligne?\n");
      scanf("%d",&x);
      printf("colonne?\n");
      scanf("%d",&y);
      z = trans2D_1D(x,y);
      /*fin de la gestion temporaire*/
      if(var->mer_cible_hum[z] != -1)
         printf("case deja tire!!!\n");
      else
      valide = 1;
   }
   printf("projectile tire !!!\n");

   return z;
}

int tir_alea(int * permit_tir, int * rep_tir, var_game_t * var)
{
   /*declaration des variables*/
   static int phase = 1;
   static int x1,x2,y1,y2;
   static int poss_p2[4];
   static int rest_p2 = 0;
   static int libre_tir = 100;
   static int first = 1;
   static int sens;

   int z,temp;

   srand(time(NULL));

   switch(phase)
   {
      case 1 :  /*phase 1 : full aleatoire*/
                z = choix_alea(permit_tir,libre_tir);
                trans1D_2D(z,&x1,&y1);
                *rep_tir = reponse_tir(z,0,var);
                var->mer_cible_cpu[z]=*rep_tir;

                if(*rep_tir == 1)
                {
                   phase++;
                   suppr_touch(permit_tir,&libre_tir,x1,y1);
                }

                suppr_point(permit_tir,&libre_tir,x1,y1);

                break;

      case 2:   /*phase 2: Recherche du sens*/
                if(first == 1)
                {
                   if(deja_tire(x1-1,y1,var) == 0)
                   {
                      z = trans2D_1D(x1-1,y1);
                      poss_p2[rest_p2]=z;
                      rest_p2++;
                   }
                   if(deja_tire(x1,y1+1,var) == 0)
                   {
                      z = trans2D_1D(x1,y1+1);
                      poss_p2[rest_p2]=z;
                      rest_p2++;
                   }
                   if(deja_tire(x1+1,y1,var) == 0)
                   {
                      z = trans2D_1D(x1+1,y1);
                      poss_p2[rest_p2]=z;
                      rest_p2++;
                   }
                   if(deja_tire(x1,y1-1,var) == 0)
                   {
                      z = trans2D_1D(x1,y1-1);
                      poss_p2[rest_p2]=z;
                      rest_p2++;
                   }
                   first = 0;
                }

                temp = rand()%rest_p2;
                z = poss_p2[temp];
                trans1D_2D(z,&x2,&y2);
                *rep_tir = reponse_tir(z,0,var);
                var->mer_cible_cpu[z]=*rep_tir;
                rest_p2--;
                poss_p2[temp]=poss_p2[rest_p2];

                if(*rep_tir != 0) /*cas du bateau touche ou coule*/
                {
                   if(x1 == x2)   /*calcul de sens*/
                   {
                      if(y2 == y1+1)
                         sens = 1;
                      else
                         sens = 3;
                   }
                   else
                   {
                      if(x2 == x1+1)
                         sens = 2;
                      else
                         sens = 0;
                   }

                   suppr_touch(permit_tir,&libre_tir,x2,y2);

                   if(*rep_tir == 1)
                      phase++;
                   else
                   {
                      phase = 1;
                      suppr_bout(permit_tir,&libre_tir,sens,x2,y2);
                      sens = (sens+2)%4 ;
                      suppr_bout(permit_tir,&libre_tir,sens,x1,y1);
                      var->remain_bat_hum = var->remain_bat_hum - 1;
                   }

                   first = 1;
                   rest_p2 = 0;
                 }

                 suppr_point(permit_tir,&libre_tir,x2,y2);
                 break;

      case 3:
                switch(sens)
                {
                   case 0:
                            x2--;
                            break;
                   case 1:
                            y2++;
                            break;
                   case 2:
                            x2++;
                            break;
                   case 3:
                            y2--;
                            break;
                }
                if(x2>=0 && x2<10 && y2>=0 && y2<10)/*verification de la validit� du point*/
                {
                    z = trans2D_1D(x2,y2);
                    *rep_tir = reponse_tir(z,0,var);
                    var->mer_cible_cpu[z]=*rep_tir;
                    if(*rep_tir == 2) /*coule*/
                    {
                       suppr_touch(permit_tir,&libre_tir,x2,y2);
                       suppr_bout(permit_tir,&libre_tir,sens,x2,y2);
                       suppr_bout(permit_tir,&libre_tir,sens,x1,y1);
                       phase = 1;
                       var->remain_bat_hum = var->remain_bat_hum - 1;
                    }
                    else 
                    {
                         if(*rep_tir == 0) /*rate on change de sens*/
                         {
                            sens = (sens+2)%4;
                            phase++;
                         }
                         else
                            suppr_touch(permit_tir,&libre_tir,x2,y2);
                    }
                    suppr_point(permit_tir,&libre_tir,x2,y2);
                 }
                 else /*on se situe a un bord de la mer*/
                 {
                    sens = (sens+2)%4;

                    switch(sens)
                    {
                       case 0:
                               x1--;
                               break;
                       case 1:
                               y1++;
                               break;
                       case 2:
                               x1++;
                               break;
                       case 3:
                               y1--;
                               break;
                     }

                     z= trans2D_1D(x1,y1);
                     *rep_tir = reponse_tir(z,0,var);
                     var->mer_cible_cpu[z]=*rep_tir;

                     if(*rep_tir == 2)
                     {
                        suppr_bout(permit_tir,&libre_tir,sens,x1,y1);
                        phase = 1;
                        var->remain_bat_hum = var->remain_bat_hum - 1;
                     }
                     else
                        phase++;

                     suppr_touch(permit_tir,&libre_tir,x1,y1);
                     suppr_point(permit_tir,&libre_tir,x1,y1);
                 }

                 break;

      case 4:
                switch(sens)
                {
                   case 0:
                            x1--;
                            break;
                   case 1:
                            y1++;
                            break;
                   case 2:
                            x1++;
                            break;
                   case 3:
                            y1--;
                            break;
                }

                z = trans2D_1D(x1,y1);
                *rep_tir = reponse_tir(z,0,var);
                var->mer_cible_cpu[z]=*rep_tir;

                if(*rep_tir == 2)
                {
                   suppr_bout(permit_tir,&libre_tir,sens,x1,y1);
                   phase = 1;
                   var->remain_bat_hum = var->remain_bat_hum - 1;
                }

                suppr_touch(permit_tir,&libre_tir,x1,y1);
                suppr_point(permit_tir,&libre_tir,x1,y1);

                break;
   }

   return z;
}

void suppr_touch(int * permit, int * max,int x, int y)
{
   suppr_point(permit, max, x+1, y+1);
   suppr_point(permit, max, x-1, y+1);
   suppr_point(permit, max, x+1, y-1);
   suppr_point(permit, max, x-1, y-1);
}

int deja_tire(int x, int y, var_game_t * var)
{
   /*on regarde si la case a deja ete tiree*/
   int rep = 1;
   int z = trans2D_1D(x,y);
   if(var->mer_cible_cpu[z] == -1)
      rep = 0;
   return rep;
}

void suppr_bout(int * permit, int * max, int sens,int x, int y)
{
   switch(sens)
   {
      case 0:
               x--;
               break;
      case 1:
               y++;
               break;
      case 2:
               x++;
               break;
      case 3:
               y--;
               break;
   }
   suppr_point(permit, max, x, y);

}

void placement_hum(var_game_t * var)
{
   int bateau,i,z;

   printf("le sens sera indique a l'aide de la valeur 1 pour vertical et 0 pour horizontal \n");
   printf("la valeur des lignes et colonne doit etre entre 0 et 9\n");

   for(bateau=0;bateau<5;bateau++)
   {

      do
      {
         /*cette partie devra prendre en compte la gestion des evenements*/
         /*realise a l'aide de la bibliotheque SDL                       */
         /*pour l'instant on se limitera a une demande en texte          */
         do
         {
            printf("sens du bateau ?\n");
            scanf("%d",&(var->flotte_hum[bateau].sens));
         }while(var->flotte_hum[bateau].sens != 0  && var->flotte_hum[bateau].sens != 1);
         printf("ligne de la premiere case?\n");
         scanf("%d",&(var->flotte_hum[bateau].x));
         printf("colonne de la premiere case?\n");
         scanf("%d",&(var->flotte_hum[bateau].y));
         /*fin de la gestion temporaire*/

      }while(!placement_valide (var->flotte_hum[bateau].x,var->flotte_hum[bateau].y, var->flotte_hum[bateau].sens,var->flotte_hum[bateau].taille,var));

      /*remplissage de la matrice*/
      z = trans2D_1D(var->flotte_hum[bateau].x,var->flotte_hum[bateau].y);
      if(var->flotte_hum[bateau].sens == 0)
      {
         for(i=0;i<var->flotte_hum[bateau].taille;i++)
            var->mer_home_hum[z+i] = bateau;
      }
      else
      {
         for(i=0;i<var->flotte_hum[bateau].taille;i++)
            var->mer_home_hum[z+10*i] = bateau;
      }
   }
}

