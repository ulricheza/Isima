#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*---------------------*/
/*Maxime Escourbiac    */
/*22/10/09             */
/* initiatiation au C  */
/*---------------------*/

/*------------------------------------------------------*/
/*dans ce tp nous allons voir les principales fonctions */
/*sur les chaines de caracteres                         */
/*et ensuite code un jeu mastermindesque                */
/*------------------------------------------------------*/


int main ()
{
  int res;
  int demande;
  int i = 0;
  int tent ;
  srand(time(0));
  res = rand()%100;
  /*printf("res == %d\n",res);*/
  printf("estimez votre nombre de tentative\n");
  scanf("%d",&tent);
  do
  {
     printf("veuillez tapez un nombre entre 0 et 100\n");
     scanf("%d",&demande);
     if(demande>res) printf("trop haut\n");
     else if(demande<res) printf("trop bas\n");
     i++;
  }while(demande != res && i != tent);
  if(demande == res && i == tent) printf("bravo vous avez gagne\n");
  else printf("vous avez echoue\n");
  return 0;
}
