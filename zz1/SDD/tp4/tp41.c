/**
 * \file tp41.c
 * \brief Programme de tri par tas
 * \author Maxime ESCOURBIAC Sebastien SAINT_MARTIN
 * \version 1.0
 * \date Vendredi 04 juin 2010
 *
 *  Programme qui effectue un tri par tas sur des arbres binaires parfait
 *
 */

#include "tp41.h"


int main(int argc, char * argv[])
{
   int N,i=0;
   int * tas;
   FILE * fic;

   if (argc == 2)
   {
      printf("Ouverture du fichier\n");
      fic = fopen(argv[1],"rt");
      if(!fic)
      {
         fprintf(stderr,"erreur dans l'ouverture du fichier \n");
         exit(EXIT_FAILURE);
      }
      /*lecture du nombre d'element*/
      fscanf(fic,"%d",&N);

      /*allocation du tableau d'entier tas*/
      tas = (int*)malloc(N*sizeof(int));
      if(!tas) /*si mauvaise allocation de tas*/
      {
         fprintf(stderr,"erreur dans l'allocation du tas \n");
         exit(EXIT_FAILURE);
      }
      /*lecture de la liste de nombre*/
      while(!feof(fic))
         fscanf(fic,"%d",&tas[i++]);

      printf("affichage du tableau initial\n");
      affic_tab(tas,N);
      
      printf("operation de tri par tas\n");
      tripartas(tas,N);
      
      printf("liste triee:\n");
      affic_tab(tas,N);
      free(tas);
      fclose(fic);
   }
   else
      fprintf(stderr,"souci avec l'argument\n");

   return(EXIT_SUCCESS);
}

void tripartas(int * tas,int N)
{
   int i,temp;
   
   /*construction du tas initial*/
   construire_tas(tas,N);

   /*les N-1 descente de tas*/
   for(i=N-1;i>0;--i)
   {
      temp = tas[i];
      tas[i] = tas[0];
      tas[0] = temp;
      descendre_tas(tas,i,1);
   }
}

void construire_tas(int * tas,int N)
{
   int rang;
   for(rang = N/2;rang > 0;rang--)
      descendre_tas(tas,N,rang);
}

void descendre_tas(int * tas, int N,int rang)
{
   int ech = 1;
   int fils,temp;
   int k = rang;
   int val = tas[rang-1];
   while(k <= N/2 && ech == 1)
   {
      ech  = 0;
      fils = 2*k;
      if(fils < N )
         if(tas[fils-1] < tas[fils])
	    ++fils;

      if(val < tas[fils-1])
      {
	 temp = tas[k-1];
         tas[k-1] = tas[fils-1];
	 tas[fils-1] = temp;
         k = fils;
         ech = 1;
      }
   }
}

void affic_tab(int * tab,int N)
{
   int i;
   for(i=0;i<N;i++)
      printf("%d ",tab[i]);
   printf("\n");
}
