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
/*changemen de regles: annonce du nombre de tentatives!!*/

int main ()
{
  int res;
  int demande;
  int i = 0;
  srand(time(0));
  res = rand()%100;
  /*printf("res == %d\n",res);*/
  do
  {
     printf("veuillez tapez un nombre entre 0 et 100\n");
     scanf("%d",&demande);
     if(demande>res) printf("trop haut\n");
     else if(demande<res) printf("trop bas\n");
     i++;
  }while(demande != res);
  printf("bravo vous avez trouvé en %d tentatives\n",i);
  return 0;
}
