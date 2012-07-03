/**
 * \file agenda.c
 * \brief Programme de gestion d'agenda
 * \author Maxime Escourbiac
 * \version 0.1
 * \date Mardi 12 janvier 2010
 *
 * Programme qui gere un agenda
 *
 */
 
 #include "agenda.h"

 
/*initialisation des variables externes*/
 extern void ** gPool ;
 extern int gPoolIndex ;
 extern int gPoolMax ;
 
 /**
 *\fn main(int argc, char argv[])
 *\brief fonction principale de gestion d'un agenda
 *\param argc nombre d'argument en entrée
 *\param argv pointeur sur les arguments 
 *
*/
  int main(int argc, char * argv[])
 {
     int a = 0;
     agenda_t * tete = NULL;
     creerGC();
     printf("gpoolmax: %d \n",gPoolMax);
     printf("adjonction\n");
     /*on effectue  adjonctions afind e simuler un depassement de memoire*/
     /*on aura ainsi une double allocation                               */
     while(a<7)
     {
        adj(&tete);
        a++;
     }
     printf("affichage de la liste chaine\n");
     affic(tete);
     printf("suppression\n");
     detruireGC();
     /*system("pause"); utiliser pour programmation windows =) */
     return(EXIT_SUCCESS);
}

/**
 *\fn void adj(agenda_t ** tete)
 *\brief fonction d'adjonction en tete d'uen liste chainee
 *\param tete pointeur de tete sur la liste chainee
 * on effectue des adjonctions en tete afin de faciliter la gestion de la liste
 * chainee, et ainsi de tester les fonctions de gestion de memoire 
 *
*/
 void adj(agenda_t ** tete)
 {
    agenda_t * nouveau = allouer(sizeof(agenda_t));
    if(nouveau != NULL)
    {
       printf("nom?\n");
       scanf("%s",nouveau->nom);
       printf("num?\n");
       scanf("%s",nouveau->num);
       nouveau->suiv = *tete;
       *tete = nouveau;
    }
    else
    {
       printf("probleme avec le retour\n");
    }
}

/**
 *\fn void affic(agenda_t * tete)
 *\brief fonction d'affichage d'une liste chainee
 *\param tete pointeur de tete sur la liste chainee
 *
*/
 void affic(agenda_t * tete)
 {
      agenda_t * courant = tete;
      while(courant)
      {
         printf("Nom: %s ,Num: %s \n",courant->nom,courant->num);
         courant = courant->suiv;
      }
 }
  

