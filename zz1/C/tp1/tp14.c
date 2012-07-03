/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*Maxime Escourbiac                                                    30/09/2009 */
/*ZZ1                                                                             */
/*TP 1 : 4                                                                        */
/*description:                                                                    */
/*passage par valeur, par adresse, masquage de variables                          */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void switch_val( int a , int b);
void switch_add ( int * a , int * b);
void masquage (int g);

/*variable globales */
int g;

int main()
{
   int a = 4;
   int b = 2;
   printf("a = %d b = %d \n",a,b);
   switch_val( a , b);
   printf("on switche par valeur\n");
   printf("a = %d b = %d \n",a,b);
   printf("on switche par adresse\n");
   switch_add( &a,&b);
   printf("a = %d b = %d \n",a,b);
   g = 3;
   printf("g = %d \n",g);
   masquage(g);
   printf("g = %d \n",g);
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

void masquage (int g)
{
   g = 4;
   printf("g= %d \n",g);
}

