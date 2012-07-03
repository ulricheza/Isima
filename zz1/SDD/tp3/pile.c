/**
 * \file pile.c 
 * \brief Programme de gestion de piles
 * \author Maxime ESCOURBIAC Sebastien SAINT_MARTIN
 * \version 1.0
 * \date Vendredi 19 mars 2010
 *  
 * library de gestion de piles
 */


#include "pile.h"

pile_t * init_pile(int taille)
{
   pile_t * new = (pile_t *) malloc(sizeof(pile_t));
   if(new != NULL)
   {
      new->rang = -1;  /*init rang*/
      new->taille_max = taille;  /*init taille*/
      new->tableau = (type_t *) malloc(taille*sizeof(type_t)); /*init tableau*/
      if(new->tableau == NULL)
      {
         free(new); /*on libere la structure pour eviter du memory leaking*/
         new = NULL;
         fprintf(stderr,"Allocation tableau dans init pile");
      }
   }
   else 
      fprintf(stderr,"Allocation pile");
   return new;
}   


int vide_pile(pile_t * lifo)
{
   return(lifo->rang == -1);
}


int empiler(pile_t * lifo,type_t valeur)
{
   int realise = 0;
   if(pleine_pile(lifo)!= 1)
   {
      (lifo->rang)++; /*maj du rang*/
      lifo->tableau[lifo->rang] = valeur; /*affectation valeur*/
      realise = 1;
   }
   return realise;
}

int depiler(pile_t * lifo,type_t * valeur)
{
   int realise = 0;
   if(vide_pile(lifo) != 1)
   {
      *valeur= lifo->tableau[lifo->rang]; /*recuperation de la valeur*/
      (lifo->rang)--;                     /*MAJ rang*/
      realise = 1;
   }
   return realise;
}

int sommet_pile(pile_t * lifo,type_t * valeur)
{
   int realise = 0;
   if(vide_pile(lifo) != 1)
   {
      *valeur= lifo->tableau[lifo->rang]; /*recuperation de la valeur*/
      realise = 1;
   }
   return realise;
}

int pleine_pile(pile_t * lifo)
{
   return(lifo->rang == (lifo->taille_max- 1));                 
}

void detruire_pile(pile_t * lifo)
{
   free(lifo->tableau); /*liberation du tableau d'entier*/
   free(lifo);          /*liberation de la pile*/
}
