/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*Maxime Escourbiac                                                    13/10/2009 */
/*ZZ1                                                                             */
/*TP 2B : manipulation de pointeur                                                */
/*description:                                                                    */
/* essai & manipulation sur les pointeurs                                         */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>


void switch_add ( char * a , char * b);

int main()
{
   int i,*ptri=&i;
   char c1, *ptrc1=&c1;
   char c2, *ptrc2=&c2;
   double d , *ptrd=&d;
   printf("ptri = %d ptrc1 = %d \n",ptri, ptrc1);
   printf("ptri = %x ptrc1 = %x \n",ptri, ptrc1);
   ptri++;
   ptrc1++;
   printf("ptri = %d ptrc1 = %d \n",ptri, ptrc1);
   printf("valeur pointee\n");
   printf("ptri = %d ptrc1 = %d ptrd= %d\n",*ptri,*ptrc1,*ptrd);
   printf("l'adresse contenue dans le pointeur\n"); 
   printf("ptri = %d ptrc1 = %d ptrd= %d\n",ptri,ptrc1,ptrd);
   printf("l'adresse du pointeur\n");
   printf("ptri = %d ptrc1 = %d ptrd= %d\n",&ptri,&ptrc1,&ptrd);
   ptrd = ptrd +2;
   printf("ptrd= %d\n",ptrd);
   c1 = '1';
   c2 = '2';
   printf("avant echange\n");
   printf("valeur pointee\n");
   printf("ptrc1 = %d ptrc2= %d\n",*ptrc1,*ptrc2);
   printf("l'adresse contenue dans le pointeur\n"); 
   printf("ptrc1 = %d ptrc2= %d\n",ptrc1,ptrc2);
   printf("l'adresse du pointeur\n");
   printf("ptrc1 = %d ptrc2= %d\n",&ptrc1,&ptrc2);
   switch_add(ptrc1,ptrc2);
   printf("apres echange\n");
   printf("valeur pointee\n");
   printf("ptrc1 = %d ptrc2= %d\n",*ptrc1,*ptrc2);
   printf("l'adresse contenue dans le pointeur\n"); 
   printf("ptrc1 = %d ptrc2= %d\n",ptrc1,ptrc2);
   printf("l'adresse du pointeur\n");
   printf("ptrc1 = %d ptrc2= %d\n",&ptrc1,&ptrc2);
}

void switch_add ( char * a , char * b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}