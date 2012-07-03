/**
 * \file tp42.c
 * \brief Programme de tri par interclassement
 * \author Maxime ESCOURBIAC Sebastien SAINT_MARTIN
 * \version 1.0
 * \date Mardi 08 juin 2010
 *
 *  Programme qui effectue un tri par interclassement
 *
 */

#include "tp42.h"

int main(int argc, char * argv[])
{
   int N,i=0;
   int * tab;
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
      /*allocation du tableau d'entier*/
      tab = (int*)malloc(N*sizeof(int));
      if(!tab) /*si mauvaise allocation de tab*/
      {
         fprintf(stderr,"erreur dans l'allocation du tableau \n");
         exit(EXIT_FAILURE);
      }
      /*lecture de la liste de nombre*/
      while(!feof(fic))
         fscanf(fic,"%d",&tab[i++]);

      printf("affichage du tableau initial\n");
      affic_tab(tab,N);
      printf("procedure de tri\n");
      tab = tri(tab,N);
      printf("affichage liste triee\n");
      affic_tab(tab,N);
      free(tab);
      fclose(fic);
   }
   return(EXIT_SUCCESS);
}

void affic_tab(int * tab,int N)
{
   int i;
   for(i=0;i<N;i++)
      printf("%d ",tab[i]);
   printf("\n");
}

void interclass(int * t1, int * t2,int debl1,int finl1,int debl2, int finl2)
{
   int i,j = debl2,k = debl1;

   for(i=debl1;i<=finl1;i++)
   {
      while( j < finl2 && t1[i]>=t1[j])
         t2[k++] = t1[j++];
      t2[k++] = t1[i];
   }
   while( j < finl2)
      t2[k++] = t1[j++];
}

int * tri(int * liste,int N)
{
   int * listeT,* temp,m,l;

   listeT = (int *)malloc(N*sizeof(int));
   if(!listeT)
   {
      fprintf(stderr,"probleme allocation memoire \n");
      exit(EXIT_FAILURE);
   }
   for(l=1;l<N;l<<=1) /*l<<=1 <=> l = l*2 */
   {
      for(m=0;m<N;m+=2*l)
         interclass(liste,listeT,m,m+l-1,m+l,min(m+2*l,N));
      temp = liste;
      liste = listeT;
      listeT = temp;
   }
   free(listeT);
   return(liste);
}
