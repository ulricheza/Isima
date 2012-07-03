/**
 * \file back_to_future.c
 * \brief Retour vers le futur 
 * \author Maxime Escourbiac Jean Christophe Septier
 * \date Jeudi 11 novembre
 */

/*------------------------------------------------------------
  Le but de cette partie est de flouter l'image via des pipes
--------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "erreur.h"
#include "imaio.h"
#include <math.h>

/*declaration du tableau pour le pipe en variable globale*/
int tube[2];


void flou(PIXRVB **out, PIXRVB **in, int np, int nl, int rayon,int couleur)
{
   int i,j,k,l,nb;
   float rt;
   unsigned char buff[2];
   buff[0] = (unsigned char) couleur;
   
   close(tube[0]); /*fermeture du pipe en lecture*/
   for (i=0;i<nl;i++)
   {
      for (j=0;j<np;j++)
      {
         rt=0; nb=0;
         for (k=0;k<rayon;k++)
         {
            for (l=0;l<rayon;l++)
            {
               if (((i+k)<nl) && ((j+l)<np))         
               {
                  rt+=(float)in[i+k][j+l][couleur];
                  nb++;
               }
            }
          
          }
          buff[1] = (PIXEL)floor(rt/(float)nb);
          if(write(tube[1],buff,2) != 2)
          {
             fprintf(stderr,"erreur ecriture dans le pipe\n");
             exit(EXIT_FAILURE);
          }
       }          
   }       

}


int main(int argc , char ** argv)
{
  /*Declaration des variables*/
  pid_t fils[3];
  unsigned char buff[2];
  int lig_red=0,col_red=0,lig_ver=0,col_ver=0,lig_ble=0,col_ble=0,np,nl,rayon,i;
  PIXRVB **in,**out;
 
  if (argc<4)
      erreur(argv[0],"usage : flou image1 image2 rayon\n",100);

   in = charimarvb(argv[1],&np,&nl);
   rayon=atoi(argv[3]);
   MALLOCRVB(out,np,nl);
  
 
  /*creation du pipe*/
  if(pipe(tube) != 0)
  {
    fprintf(stderr,"erreur cretion du pipe\n");
    exit(EXIT_FAILURE);
  }

  /*creation des processus fils*/
  for(i=0;i<3;i++)
  {
      fils[i] = fork();
      switch(fils[i])
      {
         case -1: /*cas: erreur dans la creation du processus fils*/
                 fprintf(stderr,"erreur dans la creation du fork %d\n",i);
                 exit(EXIT_FAILURE);
                 break;
         case 0: /*cas processus fils*/
                 fprintf(stdout,"creation fork %d\n",i);
                 flou(out,in,np,nl,rayon,i);
                 return(EXIT_SUCCESS);
                 break;
         default:/*cas processus pere*/
                 /*on fait rien*/
                 break;
       }
   }
   
   close(tube[1]); /*fermeture du pipe en ecriture*/
   /*partie du programme pere de recuperation des donnees*/
   while(!(lig_red == nl && lig_ver == nl && lig_ble == nl))
   {
     if(read(tube[0],buff,2) != 2)
     {
       fprintf(stderr,"erreur de lecture dans le pipe\n");
       exit(EXIT_FAILURE);
     }
     switch(buff[0]) //selon le premier caractere
     {
        case 0:
           out[lig_red][col_red][0] += (PIXEL) buff[1];
           if(++col_red == np)
           {
             ++lig_red;
             col_red = 0;
           }
           break;
        case 1:
           out[lig_ver][col_ver][1] += (PIXEL) buff[1];
           if(++col_ver == np)
           {
             ++lig_ver;
             col_ver = 0;
           }          
           break;
        case 2:
           out[lig_ble][col_ble][2] += (PIXEL) buff[1];
           if(++col_ble == np)
           {
             ++lig_ble;
             col_ble = 0;
           }
           break;
        default:
           printf("erreur lecture\n");
           break;
     }
   }
   vidimarvb(argv[2], out, np,nl);
   exit(EXIT_SUCCESS);
}

  