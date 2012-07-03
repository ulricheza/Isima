#include <stdio.h>

/*1er tp de C pdt les semaines bloquees*/

/*test de la variable locale et globale*/

int b = 0; /*init de la variables globale*/

void v1();

int main()
{
   v1();
   b = 2;
   v1();
}

void v1()
{
   printf("la valeur de b ==%d\n",b);
}