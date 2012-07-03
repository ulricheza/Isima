/**
 * \file file.c 
 * \brief Programme de gestion de piles
 * \author Maxime ESCOURBIAC Sebastien SAINT_MARTIN
 * \version 1.0
 * \date Vendredi 19 mars 2010
 *  
 * library de gestion de piles
 */


#include "file.h"


file_t * init_file(int taille)
{
   file_t * new = (file_t *) malloc(sizeof(file_t));
   if(new != NULL)
   {
      new->taille_max = taille;/*init variable*/
      new->cpt = 0;
      new->deb = 0;
      new->fin = taille - 1;
      new->tableau =(type_t *) malloc(taille*sizeof(type_t));
      if(new->tableau == NULL)
      {
         fprintf(stderr,"Erreur dans l'allocataion du tableau\n");
         free(new);
         new = NULL;
      }
    }
    else
       fprintf(stderr,"Erreur dans l'allocataion de la structure de la file\n");

   return new;
}

int sommet_file(file_t * fifo, type_t * valeur)
{
   int realise = 0;
   if(!vide_file(fifo))
   {
      *valeur = fifo->tableau[fifo->deb]; /*recuperation de la 1er valeur*/ 
      realise = 1;
   }
   return realise;
}

void detruire_file(file_t * fifo)
{
   free(fifo->tableau); /*liberation du tableau d'entier*/
   free(fifo);          /*liberation de la file*/
}

int pleine_file(file_t * fifo)
{
   return(fifo->cpt == (fifo->taille_max));
}

int vide_file(file_t * fifo)
{
   return(fifo->cpt == 0);
}

int enfiler(file_t * fifo, type_t valeur)
{
   int realise = 0;
   if(!pleine_file(fifo))
   {
      (fifo->cpt)++; /*MAJ du compteur*/
      fifo->fin = (fifo->fin +1)%(fifo->taille_max); /*on modifie l'indice de fin*/
      fifo->tableau[fifo->fin] = valeur; 
      realise = 1;
   }
   return realise;
}

int defiler(file_t * fifo, type_t * valeur)
{
   int realise = 0;
   if(!vide_file(fifo))
   {
      (fifo->cpt)--; /* MAJ du compteur*/
      *valeur = fifo->tableau[fifo->deb]; /*on extrait la valeur*/
      fifo->deb = (fifo->deb +1)%(fifo->taille_max);
      realise = 1;
   }
   return realise;
}
