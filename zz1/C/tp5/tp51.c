/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*Maxime Escourbiac                                                    01/01/2009 */
/*ZZ1                                                                             */
/*TP 5 : C                                                                        */
/*description: 1er partie                                                         */
/*manipulation sur les structures                                                 */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>

#define TAILLE 3
/*declaration de la structure login_t */

typedef struct login 
{
   char log[10];
   char pass[10];
   char machine[10];
   struct login * suivant;
}login_t;

/*declaration des fonctions*/
void saisie(login_t * tab);
void affichage(login_t * tab);

int main (int argc , char * argv[])
{
   
   login_t tab[TAILLE];
   saisie(tab);
   system("clear");
   affichage(tab);
   

   return(EXIT_SUCCESS);
}


/*saisie du tableau en statique*/
void saisie(login_t * tab)
{
   int i = 0;
   for(i=0;i<TAILLE;i++)
      {
         printf("log?\n");
         scanf("%s",tab[i].log);
         printf("pass?\n");
         scanf("%s",tab[i].pass);
         printf("machine?\n");
         scanf("%s",tab[i].machine);
      }
}

void affichage(login_t * tab)
{
   int i = 0;
   for(i=0;i<TAILLE;i++)
   {
      printf("------------------\n");
      printf("login = %s \n",tab[i].log);
      printf("pass = %s \n",tab[i].pass);
      printf("machine = %s \n",tab[i].machine);
   }
} 

