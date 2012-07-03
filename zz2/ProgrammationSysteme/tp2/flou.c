/**
 * \file flou.c
 * \brief fichier flou.c du tp2 de programmation systeme
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date Lundi 18 octobre 2010
 * \version 1.0
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "erreur.h"
#include "imaio.h"
#include <pthread.h>
#include <unistd.h> /*rajoute par rapport au fichier original*/
#include <string.h> /*rajoute par rapport au fichier original*/

#define N 20 /*N = le nombre de bandes que l'on va creer*/
typedef struct param
{
   PIXRVB **out; 
   PIXRVB **in;
   /*ces 4 parametres sont necessaires pour le floutage par bandes*/
   int col_min;   
   int col_max;
   int ligne_min;
   int ligne_max;
   /*-------------------------------------------------------------*/
   int np;
   int nl;
   int rayon;
   int couleur;
}param_t;

/**
 *\fn void flou(void * par)
 *\brief fonction de floutage d'une couleur specifique
 * les parametres de ce blocs de commentaire sont ceux que l'on a ajouter au programme initial
 *\param par structure sur les parametres a utiliser
 *\return NULL 
 *Cette fonction a pour but d'etre lancee via un thread
 *
 */

void * flou(void * par)
{
   int i,j,k,l,nb;
   float rr;
   param_t * param = (param_t *) par;
   for (i=param->ligne_min;i<param->ligne_max;i++)
   {
      for (j=param->col_min;j<param->col_max;j++)
      {
         rr=0; nb=0;
         for (k=0;k<param->rayon;k++)
            for (l=0;l<param->rayon;l++)
               if(((i+k)<param->nl) && ((j+l)<param->np))
               {
                  rr+=(float)param->in[i+k][j+l][param->couleur];
                  nb++;
               }
         param->out[i][j][param->couleur] += (PIXEL)floor(rr/(float)nb);
      }
   }
   return NULL;
}

/**
 *\fn void flou_Q1(char ** argv)
 *\brief fonction de floutage par couleur
 *\param argc reprend les parametres du programme principal
 *\param argv reprend les parametres du programme principal
 *
 */
void flou_Q1(char ** argv)
{   
   int np,nl,rayon,i;
   PIXRVB **in,**out;
   pthread_t thread[3];
   param_t param[3];
   char nom_fichier[255];
   
   rayon=atoi(argv[3]);
   in = charimarvb(argv[1],&np,&nl);;
   MALLOCRVB(out,np,nl);



   for(i=0;i<3;i++)
   {
      param[i].in = in;
      param[i].out = out;
      param[i].np = np;
      param[i].nl = nl;
      param[i].couleur = i;
      param[i].rayon = rayon;
      param[i].ligne_min = 0;
      param[i].col_min = 0;
      param[i].ligne_max = nl;
      param[i].col_max = np;

      printf("Thread %d cree\n",i);
      if(pthread_create(&thread[i],NULL,flou,&param[i]))
      {
         fprintf(stderr,"erreur creation thread %d \n",i);
         exit(EXIT_FAILURE);
      }
   }
   
   for(i=0;i<3;i++)
   {
      printf("attente thread %d \n",i);
      if(pthread_join(thread[i],NULL))
      {
         fprintf(stderr,"erreur attente fin thread %d \n",i);
         exit(EXIT_FAILURE);
      }
   }
   
   printf("Generation image...\n");
   vidimarvb(argv[2],out,np,nl);
   
   printf("Affichage image floute\n");

   strcpy(nom_fichier,argv[2]);
   strcat(nom_fichier,".rvb");
   execlp("xv","xv",nom_fichier,NULL);
}

/**
 *\fn void flou_horizon(char ** argv)
 *\brief fonction de floutage par bande horizontale
 *\param argv reprend les parametres du programme principal
 *
 */

void flou_horizon(char ** argv)
{
   int np,nl,rayon,i,j;
   PIXRVB **in,**out;
   pthread_t thread[3*N];
   param_t param[3*N];
   char nom_fichier[255];
   
   rayon=atoi(argv[3]);
   in = charimarvb(argv[1],&np,&nl);;
   MALLOCRVB(out,np,nl);
   
   for(j=0;j<N;++j)
   {
      for(i=0;i<3;++i)
      {
         param[3*j+i].in = in;
         param[3*j+i].out = out;
         param[3*j+i].np = np;
         param[3*j+i].nl = nl;
         param[3*j+i].col_min = 0;
         param[3*j+i].col_max = np;
         param[3*j+i].ligne_min = nl/N*j;
	 param[3*j+i].ligne_max = (nl/N)*(j+1);
         param[3*j+i].couleur = i;
         param[3*j+i].rayon = rayon;

         printf("Thread %d cree\n",3*j+i);
         if(pthread_create(&thread[3*j+i],NULL,flou,&param[3*j+i]))
         {
            fprintf(stderr,"erreur creation thread %d \n",3*j+i);
            exit(EXIT_FAILURE);
         }
      }
   }
   
   for(i=0;i<3*N;i++)
   {
      printf("attente thread %d \n",i);
      if(pthread_join(thread[i],NULL))
      {
         fprintf(stderr,"erreur attente fin thread %d \n",i);
         exit(EXIT_FAILURE);
      }
   }
   
   printf("Generation image...\n");
   vidimarvb(argv[2],out,np,nl);
   
   printf("Affichage image floute\n");

   strcpy(nom_fichier,argv[2]);
   strcat(nom_fichier,".rvb");
   execlp("xv","xv",nom_fichier,NULL);
}
         
/**
 *\fn void flou_vertical(char ** argv)
 *\brief fonction de floutage par bande verticale
 *\param argv reprend les parametres du programme principal
 *
 */

void flou_vertical(char ** argv)
{
   int np,nl,rayon,i,j;
   PIXRVB **in,**out;
   pthread_t thread[3*N];
   param_t param[3*N];
   char nom_fichier[255];
   
   rayon=atoi(argv[3]);
   in = charimarvb(argv[1],&np,&nl);;
   MALLOCRVB(out,np,nl);
   
   for(j=0;j<N;++j)
   {
      for(i=0;i<3;++i)
      {
         param[3*j+i].in = in;
         param[3*j+i].out = out;
         param[3*j+i].np = np;
         param[3*j+i].nl = nl;
         param[3*j+i].col_min = (np/N)*j;
         param[3*j+i].col_max = (np/N)*(j+1);
         param[3*j+i].ligne_min = 0;
         param[3*j+i].ligne_max = nl;
         param[3*j+i].couleur = i;
         param[3*j+i].rayon = rayon;
         printf("Thread %d cree\n",3*j+i);
         if(pthread_create(&thread[3*j+i],NULL,flou,&param[3*j+i]))
         {
            fprintf(stderr,"erreur creation thread %d \n",3*j+i);
            exit(EXIT_FAILURE);
         }
      }
   }
   
   for(i=0;i<3*N;i++)
   {
      printf("attente thread %d \n",i);
      if(pthread_join(thread[i],NULL))
      {
         fprintf(stderr,"erreur attente fin thread %d \n",i);
         exit(EXIT_FAILURE);
      }
   }
   
   printf("Generation image...\n");
   vidimarvb(argv[2],out,np,nl);
   
   printf("Affichage image floute\n");

   strcpy(nom_fichier,argv[2]);
   strcat(nom_fichier,".rvb");
   execlp("xv","xv",nom_fichier,NULL);
}   
   
int main(int argc,char ** argv)
{
   int choix;
   
   if (argc<4)
      erreur(argv[0],"usage : flou image1 image2 rayon\n",100);
   
   printf("-----choix algo-------\n");
   printf("1) Question 1 \n");
   printf("2) Par bande horizontale \n");
   printf("3) Par bande verticale \n");
   printf("-----------------------\n");
   scanf("%d",&choix);
   
   system("clear");
   
   switch(choix)
   {
      case 1:
         flou_Q1(argv);
         break;
      case 2:
         flou_horizon(argv);
         break;
      case 3:
         flou_vertical(argv);
      default:
         printf("bye \n");
   }   
   return(EXIT_SUCCESS);
}
