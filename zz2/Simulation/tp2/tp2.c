/**
 * \file tp2.c
 * \brief Generation de nombres pseudo aleatoires suivant differentes ditributions
 * \author Maxime Escourbiac Jean-Christophe Septier
 * \version 0.1
 * \date Jeudi 7 octobre 2010
 *
 * Tp2 de simulation
 *
 */

#include "tp2.h"


int main(int argc, char ** argv)
{
   int i;
   int * tab,val[5];
   float a,b;
   SDL_Surface * ecran;
   srand(time(0));
   
    val[0] = 15;
    val[1] = 25;
    val[2] = 30;
    val[3] = 10;
    val[4] = 20;
   
   SDL_Init(SDL_INIT_VIDEO);
   
   ecran = SDL_SetVideoMode(600, 600, 32, SDL_HWSURFACE);
   SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
   SDL_Flip(ecran);
   SDL_WM_SetCaption("Tp2 de simulation: Generation de nombres aleatoires", NULL);
   fprintf(stdout,"Cliquer pour passer a la simu suivante \n");  
   attendre();
   
   SDL_WM_SetCaption("---tableau resume de l'histogramme ABC---", NULL);
   printf("---tableau resume de l'histogramme ABC---\n");
   tab = test_histogramme_ABC();
   for(i=0;i<3;++i)
      fprintf(stdout,"tab[%d] = %f percent\n",i,(float)tab[i]/10.0);
   fprintf(stdout,"Cliquer pour passer a la simu suivante \n");
   tracer_graphe(ecran,tab,3,1000);
   free(tab);
   attendre();
   system("clear");
   
   SDL_WM_SetCaption("---tableau resume de l'histogramme quelquonque---", NULL);
   printf("---tableau resume de l'histogramme quelquonque---\n");
   tab = histogramme_gene(val,5,100);
   for(i=0;i<5;++i)
      fprintf(stdout,"tab[%d] = %f percent\n",i,(float)tab[i]/10.0);
   fprintf(stdout,"Cliquer pour passer a la simu suivante \n");
   tracer_graphe(ecran,tab,5,1000);
   free(tab);
   attendre();
   system("clear");
   
   a = 2.0; b=10.0;
   SDL_WM_SetCaption("---tableau montrant la repartition pour une loi uniforme entre 2 et 10---", NULL);
   printf("---tableau montrant la repartition pour une loi uniforme entre %f et %f---\n",a,b);
   tab = loi_uniforme(a,b);
   for(i=0;i<(int)(b-a);++i)
      fprintf(stdout," intervalle %f - %f = %d \n",(float)(i+a),(float)(i+a+1),tab[i]);   
   tracer_graphe(ecran,tab,8,250);
   fprintf(stdout,"Cliquer pour passer a la simu suivante \n");
   free(tab);
   attendre();
   system("clear");
   
   a = 10.0; b=100.0;
   SDL_WM_SetCaption("---tableau montrant la repartition pour une loi exponetielle de moyenne 10 et max 100---", NULL);
   printf("---tableau montrant la repartition pour une loi exponetielle de moyenne %f et max %f---\n",a,b);
   tab = loi_exponentielle_neg(a,b);
   for(i=0;i<(int)b;++i)
      fprintf(stdout," intervalle %f - %f = %d \n",(float)(i),(float)(i+1),tab[i]);
   tracer_graphe(ecran,tab,100,125);
   fprintf(stdout,"Cliquer pour passer a la simu suivante \n");
   free(tab);
   attendre();
   system("clear");
   
   SDL_WM_SetCaption("---tableau montrant la repartition pour une loi normale de moyenne 10 et d'ecart type 3---", NULL);
   fprintf(stdout,"---tableau montrant la repartition pour une loi normale de moyenne 10 et d'ecart type 3---\n");
   tab=loi_normale(10.0, 3.0, 0.0, 20.0);
   for(i=0;i<20;++i)
      fprintf(stdout," intervalle %f - %f = %d \n",(float)(i),(float)(i+1),tab[i]);
   tracer_graphe(ecran,tab,20,250);
   fprintf(stdout,"Cliquer pour passer a la simu suivante \n");
   free(tab);
   attendre();
   system("clear");
   
   SDL_WM_SetCaption("---tableau montrant la repartition pour une loi normale de moyenne 10 et d'ecart type 3---", NULL);
   fprintf(stdout,"---tableau montrant la repartition pour une loi normale de moyenne 10 et d'ecart type 3 (rejection)---\n");
   tab=loi_normale_rejection(10.0, 3.0, 0.0, 20.0);
   for(i=0;i<20;++i)
      fprintf(stdout," intervalle %f - %f = %d \n",(float)(i),(float)(i+1),tab[i]);
   tracer_graphe(ecran,tab,20,250);
   fprintf(stdout,"Cliquer pour passer a la simu suivante \n");
   free(tab);
   attendre();
   system("clear");
   SDL_Quit();
   return(EXIT_SUCCESS);
}

void tracer_graphe(SDL_Surface * ecran,int * tab, int nb_intervalle, int nb_tirage)
{
   SDL_Surface ** barre;
   SDL_Rect position;
   int i,largeur,hauteur;
   float rapport = 600.0/(float)nb_tirage;
   
   barre = (SDL_Surface **) malloc(nb_intervalle * sizeof(SDL_Surface*));
   if(!barre)
   {
      fprintf(stderr,"erreur alloc tableau de surface");
      exit(EXIT_FAILURE);
   }
   
   SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
   
   largeur = (int) (600.0/(float)nb_intervalle);
   for(i=0;i<nb_intervalle;++i)
   {
      hauteur = (int)((float)tab[i]*rapport);
      position.x = i*largeur;
      position.y = 600 - hauteur;
      barre[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, largeur, hauteur, 32, 0, 0, 0, 0);
      SDL_FillRect(barre[i], NULL, SDL_MapRGB(barre[i]->format, (i*50)%256,(i*40)%256 ,255));
      SDL_BlitSurface(barre[i], NULL, ecran, &position);
   }
   
   SDL_Flip(ecran);
   
   for(i=0;i<nb_intervalle;++i)
      SDL_FreeSurface(barre[i]);
   free(barre);
   
}

void attendre()
{
   int continuer = 0;
   SDL_Event event;
   
   while(!continuer)
   {
      SDL_WaitEvent(&event);
      switch(event.type)
      {
         case SDL_QUIT:
            exit(EXIT_SUCCESS);
            break;
         case SDL_MOUSEBUTTONDOWN:
            continuer = 1;
            break;
         default:
            break;
      }
   }
}