/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*Maxime Escourbiac                                                    01/01/2009 */
/*ZZ1                                                                             */
/*TP3A:Manipulation de pointeurs, Allocation dynamique et manipulation de fichiers*/
/*description:                                                                    */
/* Produit scalaire, Produit Matrice Vecteur                                      */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>


/*declaration des fonctions */

float ** lect_vect(char * name, int * ordre, int * nombre);
void affichage_vect(int * ordre,int nombre, float ** vect);
float prod_scal(float * vect1,float * vect2,int ordre1, int ordre2);

int main(int argc, char * argv[])
{
   int nombre,ordre[10];
   float ** vect = NULL; /*un tableau a deux dimensions pour lire tous les vecteurs sur un fichiers*/
   if(argc !=2)
   {
       printf("manque un argument\n");
       exit(1);
   }
   vect = lect_vect(argv[1],ordre,&nombre);
   affichage_vect(ordre,nombre,vect);
   printf("produit scalaire de vect 1 et vect 3\n");
   printf("result: %f \n",prod_scal(vect[0],vect[2],ordre[0],ordre[2]));
   return 0;
}


/*----------------------------------------*/
/*lexique de fonction                     */
/*name: nom du fichier a lire             */
/*ordre: tableau d'entier qui contient les*/
/* tailles des vecteurs                   */
/*nombre: nombre de vecteur lues          */
/*----------------------------------------*/ 

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
       vecteur[*nombre] = (float *)malloc(*ordre*sizeof(float));
       for(i=0;i<ordre[*nombre];i++)
          fscanf(fic,"%f",&vecteur[*nombre][i]);
       *nombre=*nombre + 1;
    }
    return(vecteur);
}

void affichage_vect(int * ordre,int nombre, float ** vect)
{
   int i,j;
   for(j=0;j<nombre;j++)
   {
      for(i=0;i<ordre[j];i++)
         printf("%f ",vect[j][i]);
      printf("\n");
   }
}

float prod_scal(float * vect1,float * vect2,int ordre1, int ordre2)
{
   int i;
   float result = 0.0;
   if(ordre1==ordre2)
   {
       for(i=0;i<ordre1;i++)
          result = result + vect1[i]*vect2[i];
   }
   return(result);
}
