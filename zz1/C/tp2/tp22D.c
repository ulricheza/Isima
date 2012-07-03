/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*Maxime Escourbiac                                                    13/10/2009 */
/*ZZ1                                                                             */
/*TP 2D : manipulation de pointeur                                                */
/*description:                                                                    */
/* essai & manipulation sur les pointeurs                                         */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
   unsigned int i = 0 ;
   double * cool = (double *)malloc(1000000*sizeof(double));
   if(cool!=NULL)
   {
       for(i=0;i<1000000;i++)
       {
          cool[i] =(double) i*i;
          printf("cool[%d] = %f \n",i,cool[i]);
       }
   }
   free(cool);
   return 0;
}
