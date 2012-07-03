/**
 * \file flou.c
 * \brief Programme de floutage d'image
 * \author Maxime Escourbiac Jean Christophe Septier
 * \version 1.0
 * \date Vendredi 24 semptembre
 *
 * Programme de floutage d'image e, travaillant avec des forks
 * et en modifiant le programme initial de Sir Gouinaud
 *
 */

/****************************************************
*	BUT : Fabrique trois fichier Ima a partir   *
*		d'un rvb			    *
*****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "erreur.h"
#include "imaio.h"
#include <unistd.h> /*rajoute par rapport au fichier original*/
#include <sys/types.h> /*rajoute par rapport au fichier original*/
#include <sys/wait.h> /*rajoute par rapport au fichier original*/
#include <string.h> /*rajoute par rapport au fichier original*/

/**
 *\fn void flou(PIXRVB **out, PIXRVB **in, int np, int nl, int rayon,int couleur,FILE * fichier)
 *\brief fonction de floutage d'une couleur specifique
 * les parametres de ce blocs de commentaire sont ceux que l'on a ajouter au programme initial
 *\param couleur 0= Rouge, 1=Vert, 2=Bleu
 *\param fichier pointeur sur le fichier temporaire d'ecriture
 */

void flou(PIXRVB **out, PIXRVB **in, int np, int nl, int rayon, int couleur, FILE * fichier)
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
      fwrite(out[i],np,3,fichier); /*ecriture dans le fichier temporaire*/
   }
   rewind(fichier);
}
/* FIN flou */

/**
 *\fn void reconstruction_img(const char * fic_sortie, char ** fic_entree,PIXRVB **out)
 *\brief fonction de recomposition d'une image a partir des 3 fichier rouge vert bleu
 *\param fic_sortie nom que porteront les fichiers .rgb et .dim genere par le programme
 *\param fic_entree tableaux de FILE* contenant les fichiers temporaires rouge,vert,bleu
 *\param in tableau initialise dans le main qui sera utiliser pour la 'lecture' des fichiers temporaires
 *\param out tableau initialise dans le main, qui sera utilise pour la reconstruction de l'image
 *\param np parametre de dimension de l'image
 *\param nl parametre de dimension de l'image
 */

void reconstruction_img(char * fic_sortie, FILE * fic_entree[3],PIXRVB **in,PIXRVB **out,int np,int nl)
{
   int i,j,k;
   for(i=0;i<3;i++)
   {
      for(j=0;j<nl;j++)
      {
         fread(in[j],np,3,fic_entree[i]);
         for(k=0;k<np;k++)
	 {
            out[j][k][i] += in[j][k][i];
	 }
      }
   }
   vidimarvb(fic_sortie,out,np,nl);
}

int main(int argc,char ** argv)
{
   int np,nl,rayon,i;
   PIXRVB **in,**out;
   pid_t fils[3],affic_image[2];
   char nom_fichier[255];
   FILE * fichier[3];

   if (argc<4)
      erreur(argv[0],"usage : flou image1 image2 rayon\n",100);

   in = charimarvb(argv[1],&np,&nl);
   rayon=atoi(argv[3]);
   MALLOCRVB(out,np,nl);


   for(i=0;i<3;i++)
   {
      /*initialisation des fichiers temporaires*/
      fichier[i] = tmpfile();
      if(!fichier[i])
      {
         fprintf(stderr,"erreur tmpfile %d \n",i);
         exit(EXIT_FAILURE);
      }
      fils[i] = fork();
      switch(fils[i])
      {
	case -1: /*cas: erreur dans la creation du processus fils*/
                 fprintf(stderr,"erreur dans la creation du fork %d\n",i);
                 exit(EXIT_FAILURE);
                 break;
         case 0: /*cas processus fils*/
                 fprintf(stdout,"creation fork %d\n",i);
                 flou(out,in,np,nl,rayon,i,fichier[i]);
                 return(EXIT_SUCCESS);
                 break;
         default:/*cas processus pere*/
	         /*on fait rien*/
	         break;
       }
   }

   fprintf(stdout,"attente des processus fils...\n");
   for(i=0;i<3;i++)
   {
      if(waitpid(fils[i],NULL,0) < 0)
      {
         fprintf(stderr,"Erreur retour fork %d \n",i);
      }
   }

   fprintf(stdout,"reconstruction image...\n");
   reconstruction_img(argv[2],fichier,in,out,np,nl);

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


