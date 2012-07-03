/**
 * \file vue.c
 * \brief floutage a base de shared memory 
 * \author Maxime Escourbiac Jean Christophe Septier
 * \date Lundi 29 novembre 2010
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <math.h>
#include "erreur.h"
#include "imaio.h"
/**
 *\fn void flou(PIXRVB **out, PIXRVB **in, int np, int nl, int rayon,int couleur,FILE * fichier)
 *\brief fonction de floutage d'une couleur specifique
 * les parametres de ce blocs de commentaire sont ceux que l'on a ajouter au programme initial
 *\param couleur 0= Rouge, 1=Vert, 2=Bleu
 */

void flou(PIXRVB **out, PIXRVB **in, int np, int nl, int rayon, int couleur)
{
   int i,j,k,l,nb;
   float rr;

   for (i=0;i<nl;i++)
   {
      for (j=0;j<np;j++)
      {
         rr=0; nb=0;
         for (k=0;k<rayon;k++)
            for (l=0;l<rayon;l++)
               if(((i+k)<nl) && ((j+l)<np))
	       {
                  rr+=(float)in[i+k][j+l][couleur];
                  nb++;
               }
         out[i][j][couleur] += (PIXEL)floor(rr/(float)nb);
      }
   }
}
/* FIN flou */


int main(int argc, char ** argv)
{
   int np,nl,rayon,i,shmid;
   PIXRVB **in,**out;
   pid_t fils[3],affic_image[2];
   char nom_fichier[255];
   key_t key_shm;

   if (argc<4)
      erreur(argv[0],"usage : flou image1 image2 rayon\n",100);

   key_shm = ftok("./shm_vue",2012);
   in = charimarvb(argv[1],&np,&nl);
   rayon=atoi(argv[3]);
   shmid = shmget(key_shm,nl*sizeof(PIXRVB*),0660 | IPC_CREAT);
   //MALLOCRVB(out,np,nl);
   out = (PIXRVB*)shmat(shmid,NULL,0);
   for(i=0;i<nl;++i) 					\
      out[i]=(PIXRVB *)malloc(np*sizeof(PIXRVB));
   
   
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
                 out = (PIXRVB*)shmat(shmid,NULL,0);
                 flou(out,in,np,nl,rayon,i);
                 return(EXIT_SUCCESS);
                 break;
         default:/*cas processus pere*/
	         /*on fait rien*/
	         break;
       }
   }
   out = (PIXRVB*)shmat(shmid,NULL,0);
   fprintf(stdout,"attente des processus fils...\n");
   for(i=0;i<3;i++)
   {
      if(waitpid(fils[i],NULL,0) < 0)
      {
         fprintf(stderr,"Erreur retour fork %d \n",i);
      }
   }

   fprintf(stdout,"reconstruction image...\n");
   vidimarvb(argv[2],out,np,nl);

   /*-----------------------------------------------------------------------------*/
   /*ouverture du programme xv en 2 fois pour afficher l'image initiale et floutee*/
   /*on a choisi execlp pour 2 raisons:                                           */
   /*-un seul argument ==> pas de necessite de passer un vecteur d'argument       */
   /*-on ne sait pas a priori ou le programme xv est situe, or execlp() prend en  */
   /* compte la variable PATH dans la recherche du binaire                        */
   /*-----------------------------------------------------------------------------*/
   /*Pour afficher les deux images avec xv, il est necessaire de creer un fork    */
   /*car la fonction execlp() ne retourne pas dans le programme appellant en cas  */
   /*de reussite du programme                                                     */
   /*-----------------------------------------------------------------------------*/
   fprintf(stdout,"affichage de l'image originale et floutee ...\n");
   for(i=0;i<2;i++)
   {
      affic_image[i] = fork();
      switch(affic_image[i])
      {
        case -1: /*erreur creation fork*/
               fprintf(stderr,"erreur dans la creation du fork pour afficher l'image");
               exit(EXIT_FAILURE);
	       break;
        case 0: /*cas processus fils = affichage image floutee*/
               strcpy(nom_fichier,argv[i+1]);
	       strcat(nom_fichier,".rvb");
               execlp("xv","xv",nom_fichier,NULL);
	       /*pas besoin de tester la valeur de retour car le programme xv s'executera a la*/
               /* suite de ce programme                                                       */
	       /*qu'en cas d'erreur du programme xv*/
	       fprintf(stderr,"erreur execution xv avec l'image %s\n",nom_fichier);
               exit(EXIT_FAILURE);

	       break;
        default:/*cas processus pere = affichage image originale*/

               break;
      }
   }
   return(EXIT_SUCCESS);
} /* FIN du main */
