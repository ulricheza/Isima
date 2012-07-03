#include <stdio.h>

/*initiation en C sur les tableaux*/

/* declaration du tableau en variable globale*/

int tab[10];


int main()
{
   int i = 0 ;
   int somme = 0;
   for(i;i<10;i++)
   {
      printf("tab[%d] == ?\n",i);
      scanf("%d",&tab[i]);
   }
   printf("affichage des elements du tableau");
   i = 0;
   for(i;i<10;i++)
   {
      printf("tab[%d] == %d\n",i,tab[i]);
      somme = somme + tab[i];
   }
   printf("la somme des elts du tableau == %d \n", somme);
}