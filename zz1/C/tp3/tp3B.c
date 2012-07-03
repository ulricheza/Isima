/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*Maxime Escourbiac                                                    01/01/2009 */
/*ZZ1                                                                             */
/*TP3B:Manipulation de pointeurs, Allocation dynamique et manipulation de fichiers*/
/*description:                                                                    */
/* Produit scalaire, Produit Matrice Vecteur                                      */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*declaration de fonctions*/

float ** lect_vect(char * name, int * ordre, int * nombre);
float *** lect_mat(char * name, int * ordre, int * nombre);
void affiche_mat(float *** tab,int * ordre ,int nombre);
float * mat_prod(float * vect,int ordrevect, float ** mat ,int ordremat);
void affichage_vect(int ordre,float *vect);

int main(int argc, char * argv[])
{

   int ordrevect[10];
   int ordremat[10]; 
   int nombrevect,nombremat;
   float *** matrice;
   float ** vecteur;
   float * result;
     if(argc !=3)
   {
       printf("manque des arguments\n");
       exit(1);
   }
   vecteur = lect_vect(argv[1],ordrevect,&nombrevect);
   matrice = lect_mat(argv[2],ordremat,&nombremat);
   affiche_mat(matrice,ordremat,nombremat);
   result  = mat_prod(vecteur[0],ordrevect[0],matrice[0] ,ordremat[0]);
   affichage_vect(ordrevect[0],result);
   return 0;
}


/*fonctions de lecture de vecteur*/

float ** lect_vect(char * name, int * ordre, int * nombre)
{
    FILE * fic;
    int i;
    float ** vecteur= (float **)malloc(10*sizeof(float *)); /*10 vecteur max*/
    *nombre = 0;
    fic = fopen(name,"r");
    if(!fic) exit(1);
    while(*nombre<10 && !feof(fic))
    {  
       fscanf(fic,"%d",&ordre[*nombre]);
       vecteur[*nombre] = (float *)malloc(ordre[*nombre]*sizeof(float));
       for(i=0;i<ordre[*nombre];i++)
          fscanf(fic,"%f",&vecteur[*nombre][i]);
       *nombre=*nombre + 1;
    }
    return(vecteur);
}

/*fonctions de lecture de matrice*/

float *** lect_mat(char * name, int * ordre, int * nombre)
{
   FILE * fic;
   int i,j;
   float *** mat = (float ***)malloc(10*sizeof(float**)); /* 10 matrice max*/
   *nombre = 0;
   fic = fopen(name,"r");
   if(!fic) exit(1);
   while(*nombre<10 && !feof(fic))
   {
      fscanf(fic,"%d",&ordre[*nombre]);
      /*allocation de la matrice[j] en memoire*/
      mat[*nombre]=(float **)malloc(ordre[*nombre]*sizeof(float*));
      for(i=0;i<ordre[*nombre];i++)
         mat[*nombre][i]= (float*)malloc(ordre[*nombre]*sizeof(float));
      /*fin de l'alloc*/
      i=0;
      j=0;
      while(i<ordre[*nombre])
      {
         while(j<ordre[*nombre])
         {
            fscanf(fic,"%f",&mat[*nombre][i][j]);
            j++;
         }
         j=0;
         i++;
      }
      *nombre = *nombre + 1;
    }
    return(mat);
}

/*fonction de test pour afficher les matrices*/

void affiche_mat(float *** tab,int * ordre ,int nombre)
{
   int i,j,k;
   for(i=0;i<nombre;i++)
   {
       printf("Matrice %d :::\n\n",i);
       for(j=0;j<ordre[i];j++)
       {
          for(k=0;k<ordre[i];k++)
             printf("%f  ",tab[i][j][k]);
          printf("\n");
       }
       printf("\n");
   }
}

/*fonction qui effectue le produit matrice vecteur*/

float * mat_prod(float * vect,int ordrevect, float ** mat ,int ordremat)
{
   int i,j;
   float * result;
   if(ordremat!=ordrevect)
   {
      printf("souci d'ordre\n");
      exit(1);
   }
   result = (float *)malloc(ordrevect*sizeof(float));
   for(i=0;i<ordrevect;i++)
   {
      result[i]=0;
      for(j=0;j<ordrevect;j++)
      {
          result[i]=result[i] + mat[i][j] * vect[j];
      }
      j=0;
   }
   return result;
}

/*fonction qui affiche un vecteur*/

void affichage_vect(int ordre,float *vect)
{
   int i;
   for(i=0;i<ordre;i++)
   {
      printf("result[%d] = %f ",i,vect[i]);
      printf("\n");
   }
}
