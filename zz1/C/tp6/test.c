/*declaration des bibliotheques*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* fin de declaration des bibliotheques*/

/*declaration de la structure*/
typedef struct cellule
{
    char * ligne;
    struct cellule * suivant;
}cellule_t; 
/*fin de declaration de la structure*/

/*declaration des fonctions*/
void adj_lch_fin(cellule_t ** tete, cellule_t ** queue); /*tete non fictive la classe =)*/
void affichage(cellule_t * tete);
/*fin de declaration des fonctions*/


int main(int argc, char * argv[])
{
  cellule_t * tete = NULL;
  cellule_t * queue = NULL;
  char car = 'O';
  while(toupper(car)=='O')
  {
     adj_lch_fin(&tete,&queue);
     printf("saisir une autre chaine?\n");
     scanf("%c",&car);
     getc(stdin);
  }
  affichage(tete);
  return(EXIT_SUCCESS);
}

void affichage(cellule_t * tete)
{
   cellule_t * courant = tete;
   while(courant)
   {
      printf("------------------\n");
      printf("chaine = %s \n",courant -> ligne);
      courant = courant -> suivant;
   }
}
/*commentaire a la viande*/

void adj_lch_fin(cellule_t ** tete, cellule_t ** queue)
{
   cellule_t * nouveau;
   char * temp = (char *)malloc(50*sizeof(char));
   nouveau = (cellule_t *)malloc(sizeof(cellule_t));
   printf("rentrer ligne \n");
   fgets(temp,49,stdin);
   nouveau->ligne = temp;
   nouveau->suivant = NULL;
   if(*tete == NULL)
   {
      *tete  = nouveau;
      *queue = nouveau;
      
   }
   else
   {
      (*queue)->suivant = nouveau;
      *queue = nouveau;
   }
}