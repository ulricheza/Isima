/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*Maxime Escourbiac                                                    13/10/2009 */
/*ZZ1                                                                             */
/*TP 2A : manipulation de pointeur                                                */
/*description:                                                                    */
/* essai & manipulation sur les pointeurs                                         */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

/*declaration des fonctions*/
void switch_add ( int * a , int *b);
void switch_val( int a , int b);
/*fin de declaration de fonction*/

int main()
{
   int a = 1;
   int b = 2;
   switch_val(a,b);
   printf("dans le main apres le switch par valeur\n");
   printf(" a = %d b = %d \n",a,b);
   switch_add(&a,&b); 
   printf("dans le mainapres le switch par adresse \n");
   printf(" a = %d b = %d \n",a,b);
   return 0;
}


void switch_val( int a , int b)
{
    int temp;
    temp = a;
    a = b ;
    b = temp;
    printf("dans switch_val \n");
    printf(" a = %d b = %d \n",a,b);
}

void switch_add ( int * a , int * b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
