/*-----------------------------------*/
/*tp6.c                              */
/*liste chainee, guide de style et   */
/*documentation                      */
/*-----------------------------------*/
/*Partie 1 liste chainee             */
/*lecture dans un fichier            */
/*-----------------------------------*/


#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*declaration des fonctions */




/*declaration de la strcuture*/
typedef struct cellule
{
    char * ligne;
    struct cellule * suivant;
}cellule_t;

void affichage(cellule_t * tete);
void adj_lch_fin(cellule_t ** tete, cellule_t ** queue, FILE * fichier);


int main(int argc, char * argv[])
{
  cellule_t * tete = NULL;
  cellule_t * queue = NULL;
  FILE * fichier = fopen("lecture.txt","rt");
while(!feof(fichier))
{
  adj_lch_fin(&tete,&queue,fichier);
}
  affichage(tete);
  return(EXIT_SUCCESS);
}


void adj_lch_fin(cellule_t ** tete, cellule_t ** queue, FILE * fichier)
{
 
   cellule_t * nouveau;
   char * temp = (char *)malloc(50*sizeof(char));
   nouveau = (cellule_t *)malloc(sizeof(cellule_t));
   fgets(temp,49,fichier);
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

