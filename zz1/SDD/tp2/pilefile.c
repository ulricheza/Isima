/**
 * \file pilefile.c 
 * \brief Programme de test des piles et des files
 * \author Maxime ESCOURBIAC Sebastien SAINT_MARTIN
 * \version 1.0
 * \date Vendredi 19 mars 2010
 *
 * programme de test des fonctions de pile et de file
 */


#include "pilefile.h"


int main(int argc, char * argv[])
{
   int choix = 0;
   while(choix != -1)
   {
      printf("--------MENU TP2 SDD--------\n");
      printf("1) test sur les piles       \n");
      printf("2) test sur les files       \n");
      printf("3) Question de l'examen     \n");
      printf("autre: sortie du programme  \n");

      scanf("%d",&choix);
      switch(choix)
      {
         case 1 : test_pile();
                  break;
         case 2 : test_file();
                  break;
         case 3 : exo_exam();
                  break;
         default: choix = -1;
      }

   }
   return 0;
}



void test_pile()
{
   int choix = 0;
   int valeur;
   int bool;
   pile_t * lifo = NULL;

   while(choix != -1)
   {
      printf("Fonctions de test de la pile\n");
      printf("1) Initialisation de la pile\n");
      printf("2) test si pile vide \n");
      printf("3) test si pile pleine\n");
      printf("4) empiler une valeur\n");
      printf("5) depiler une valeur\n");
      printf("6) valeur du sommet\n");
      printf("autre: retour au menu\n");

      scanf("%d",&choix);

      switch(choix)
      {
         case 1:
                  printf("taille maximale souhaitee? \n");
                  scanf("%d",&valeur);
                  lifo = init_pile(valeur);
                  break;
         case 2:
                  bool = vide_pile(lifo);
                  if(bool)
                     printf("pile vide\n");
                  else
                     printf("pile non vide\n");
                  break;
         case 3:
                  bool = pleine_pile(lifo);
                  if(bool)
                     printf("pile pleine\n");
                  else
                     printf("pile non pleine\n");
                  break;
         case 4:
                  printf("la valeur a empiler?\n");
                  scanf("%d",&valeur);
                  bool = empiler(lifo,valeur);
                  if(bool)
                     printf("empilation reussi\n");
                  else
                     printf("empilation rate\n");
                  break;
         case 5:
                  bool = depiler(lifo,&valeur);
                  if(bool)
                     printf("valeur depile : %d\n", valeur);
                  else
                     printf("depilation rate\n");
                  break;
         case 6:
                  bool = sommet_pile(lifo,&valeur);
                  if(bool)
                     printf("valeur du sommet : %d\n", valeur);
                  else
                     printf("sommet non atteignable\n");
                  break;

         default :
                         printf("destruction de la pile\n");
                         detruire_pile(lifo);
                         choix = -1;
       }
   }
}

void test_file()
{
   int choix = 0;
   int valeur;
   int bool;
   file_t * fifo = NULL;

   while(choix != -1)
   {
      printf("Fonctions de test de la file\n");
      printf("1) Initialisation de la file\n");
      printf("2) test si file vide \n");
      printf("3) test si file pleine\n");
      printf("4) enfiler une valeur\n");
      printf("5) defiler une valeur\n");
      printf("6) valeur du sommet\n");
      printf("autre: retour au menu\n");

      scanf("%d",&choix);

      switch(choix)
      {
         case 1:
                  printf("taille maximale souhaitee? \n");
                  scanf("%d",&valeur);
                  fifo = init_file(valeur);
                  break;
         case 2:
                  bool = vide_file(fifo);
                  if(bool)
                     printf("file vide\n");
                  else
                     printf("file non vide\n");
                  break;
         case 3:
                  bool = pleine_file(fifo);
                  if(bool)
                     printf("file pleine\n");
                  else
                     printf("file non pleine\n");
                  break;
         case 4:
                  printf("la valeur a enfiler?\n");
                  scanf("%d",&valeur);
                  bool = enfiler(fifo,valeur);
                  if(bool)
                     printf("enfilage reussi\n");
                  else
                     printf("enfilage rate\n");
                  break;
         case 5:
                  bool = defiler(fifo,&valeur);
                  if(bool)
                     printf("valeur defile : %d\n", valeur);
                  else
                     printf("defilation rate\n");
                  break;
         case 6:
                  bool = sommet_file(fifo,&valeur);
                  if(bool)
                     printf("valeur du sommet : %d\n", valeur);
                  else
                     printf("sommet non atteignable\n");
                  break;

         default :
                         printf("destruction de la file\n");
                         detruire_file(fifo);
                         choix = -1;
       }
   }
}


void exo_exam()
{
   pile_t * lifo = NULL;
   file_t * fifo = NULL;
   int taille_temp;
   int valeur;

   printf("Combien d'element doit contenir la pile initiale \n");
   scanf("%d",&taille_temp);
   printf("initialisation des piles\n");
   lifo = init_pile(taille_temp);
   fifo = init_file(taille_temp);
   printf("remplissage de la pile d'origine\n");
   while(!pleine_pile(lifo))
   {
      printf("valeur?\n");
      scanf("%d",&valeur);
      empiler(lifo,valeur);
   }
   printf("on depile dans la file\n");
   while(!vide_pile(lifo) && !pleine_file(fifo))
   {
      depiler(lifo,&valeur);
      enfiler(fifo,valeur);
   }
   printf("on defile dans la pile \n");
   while(!vide_file(fifo) && !pleine_pile(lifo))
   {
      defiler(fifo,&valeur);
      empiler(lifo,valeur);
   }
   printf("on depile toute la pile \n");
   while(!vide_pile(lifo))
   {
       depiler(lifo,&valeur);
       printf(" %d  ",valeur);
   }
   printf("\n");
   printf("destruction des files et des piles\n");
   detruire_pile(lifo);
   detruire_file(fifo);

}
