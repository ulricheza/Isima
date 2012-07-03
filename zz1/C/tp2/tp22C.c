/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*Maxime Escourbiac                                                    13/10/2009 */
/*ZZ1                                                                             */
/*TP 2C : manipulation de pointeur                                                */
/*description:                                                                    */
/* essai & manipulation sur les pointeurs                                         */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
   char * chaine = (char *)malloc(100*sizeof(char));
   if(chaine!=NULL)
   {
      printf("entre une chaine de caractere\n");
      scanf("%s",chaine);
      if(!strcmp(chaine,"benny")) printf("2 chaine identique\n");
   }
   free(chaine);
   return 0;
}
