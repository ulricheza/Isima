/**
 * \file tp3.c 
 * \brief Programme de gestion d'arbres generaux
 * \author Maxime ESCOURBIAC Sebastien SAINT_MARTIN
 * \version 1.0
 * \date Mercredi 10 mars 2010
 *
 *  Programme qui gere la creation d'arbres generaux
 *
 */


#include "tp3.h"




int main(int argc, char * argv[])
{
   int erreur;
   char v,w;
   FILE * fic;
   cellule_t * tete = NULL;
   int choix = 1;

   if (argc == 2)
   {
      printf("Ouverture du fichier\n");
      fic = fopen(argv[1],"rt");
      if(fic) /*test si fichier present*/
      {
         erreur = creation_arbre(&tete, fic);
         if(erreur)
            printf("erreur de la creation de l'arbre\n");
	 else
	 {
            while(choix != -1)
            {
               printf("---------menu tp3 sdd-----------\n");
               printf("1) affichage post-fixee\n");
               printf("2) insertion fils\n");
               printf("3) affichage antecedant\n");
               scanf("%d",&choix);
               clean();
               switch(choix)
               {
	          case 1 : affic_post(tete);
                           break;
                  case 2 : printf("valeur du pere de la valeur a inserer?\n"); 
                           scanf("%c",&v);
                           clean();
                           printf("valeur du fils a inserer.\n");
                           scanf("%c",&w);
                           clean();
                           inser_fils(tete,v,w);
                           break;
		  case 3 : affic_pere(tete);
			   break;
                  default :
                           choix = -1;
               }
            }
         }
      }
      else
         fprintf(stderr,"probleme ouverture du fichier");
    }
    else
       fprintf(stderr,"souci avec l'argument\n");

    return(EXIT_SUCCESS);
}

void clean()
{
   char c;
   while ((c = fgetc(stdin)) != '\n' && c != EOF); /*vide le buffer du clavier*/
}

int creation_arbre(cellule_t ** tete, FILE * fic)
{
   /*on empilera le type long pour convertir les adresses des cellules                */
   /*car sur les architectures 64bits la valeur de l'adresse ne rentre pas sur un int */
   cellule_t ** cour = tete;
   cellule_t * new;
   long rest; /*nombre de frere restant*/
   long temp; /*entier temporaire utilise pour l'empilage/depilage de courant*/
   int fin = 0; /*booleen de fin*/
   int erreur = 0; /*booleen d'erreur 1 si erreur*/
   pile_t * pile;

   pile = init_pile(100);
   if(!pile)
   {
      fprintf(stderr,"erreur dans l'allocation de la pile \n");
      erreur = 1;
   }
   else
   {
      fscanf(fic,"%ld ",&rest);
      while(!fin)
      {
         if(!rest)
         {
            if(vide_pile(pile))
               fin = 1;
            else
            {
               depiler(pile, &rest);
               depiler(pile, &temp);
               cour = (cellule_t **) temp;
	       cour = &((*cour)->lh);
            }
         }
         else
         {
            --rest;
            new = (cellule_t *)malloc(sizeof(cellule_t));
            if(!new) /*test si malloc reussi*/
            {
               fprintf(stderr,"erreur dans l'allocation d'une cellule de l'arbre\n"); 
               erreur = 1;
               fin = 1;
            }
            else
            {
               fscanf(fic,"%c ",&(new->val));
               new->lh = NULL;
               new->lv = NULL;
               *cour = new;
               temp = (long) cour;
               if(!empiler(pile,temp))
               {
                  fprintf(stderr,"l'empilage a echoue \n");
                  erreur = 1;
                  fin = 1;
               }
               else
               {
                  if(!empiler(pile,rest))
                  {
                     fprintf(stderr,"l'empilage a echoue \n");
                     erreur = 1;
                     fin = 1;
                  }
                  cour = &(new->lv);
                  fscanf(fic,"%ld ",&rest);
                }
             }
          }
       }
    }
    detruire_pile(pile);
    return(erreur);
}

void affic_post(cellule_t * tete)
{
   /*l'algo utilise est l'algo de la page 15 du poly simplifie*/
   cellule_t * cour = tete;
   long temp;
   pile_t * pile ;

   pile = init_pile(100);
   if(!pile)
      fprintf(stderr,"erreur dans l'allocation de la pile \n");
   else
   {
      printf("lecture post-fixee de l'arbre:\n");
      while(!vide_pile(pile) || cour)
      {
         temp = (long) cour;
         if(!empiler(pile,temp))
         {
            fprintf(stderr,"l'empilage a echoue \n");
            exit(EXIT_FAILURE);
         }
         cour = cour->lv;

         while(!cour && !vide_pile(pile))
         {
            depiler(pile, &temp);
	    cour = (cellule_t *) temp;
            printf("%c ",cour->val);
	    cour = cour->lh;
         }
      }
      printf("\n");
      detruire_pile(pile);
   }
}

cellule_t * rech_elt(cellule_t * tete,char v, pile_t * pile)
{
   /*l'algo utilise une recherche en profondeur*/
   cellule_t * cour = tete;
   long temp;
   int fin = 0;
  
   
   if(!pile)
   {
      fprintf(stderr,"la pile n'a pas ete allouee \n");
      cour = NULL;
   }
   else
   {

      while((!vide_pile(pile) || cour) && !fin)
      {
         temp = (long) cour;
	 if(cour->val == v)
	    fin = 1;
	 else
	 {
            if(!empiler(pile,temp))
            {
               fprintf(stderr,"l'empilage a echoue \n");
               exit(EXIT_FAILURE);
            }
            cour = cour->lv;

            while(cour == NULL && vide_pile(pile) == 0)
            {
               depiler(pile, &temp);
	       cour = (cellule_t *) temp;
	       cour = cour->lh;
            }
         }
      }
   }
   return(cour);
}

void inser_fils(cellule_t * tete, char v , char w)
{
   cellule_t * cour;
   cellule_t ** prec;
   cellule_t * new;
   pile_t * pile;
   
   pile = init_pile(100);
   if(pile == NULL)
   {
      fprintf(stderr,"erreur dans l'allocation de la pile \n");
      cour = NULL;
   }

   cour = rech_elt(tete,v,pile);
   if(cour)    /*si element trouve */
   {
      prec = &(cour->lv);
      cour = cour->lv;
      while( cour && cour->val < w)
      {
         prec = &(cour->lh);
         cour = cour->lh;
      }
      new = (cellule_t *) malloc(sizeof(cellule_t));
      if(new)
      {
         new->val = w;
         new->lv = NULL;
         new->lh = *prec;
         *prec = new;
      }
      else
         fprintf(stderr,"allocation de la cellule a echoue \n");
   }
   else
      fprintf(stderr,"valeur non trouvee \n");
   detruire_pile(pile);
}

void affic_pere(cellule_t * tete)
{
   char val;
   long temp;
   pile_t * pile;
   cellule_t * cour = NULL;

   pile = init_pile(100);
   if(pile == NULL)   /*test si alloc pile reussi*/
   {
      fprintf(stderr,"erreur dans l'allocation de la pile \n");
      cour = NULL;
   }

   printf("quelle est la valeur a rechercher?\n");
   scanf("%c",&val);
   clean();
   if(rech_elt(tete,val,pile) != NULL)   /*test si valeur existante*/
   {
      printf("affichage des peres de la valeur : %c \n",val);
      while(!vide_pile(pile))
      {
         depiler(pile,&temp);
         cour = (cellule_t *)temp;
         printf("%c ",cour->val);
      }
      printf("\n");
   }
   else
      printf("valeur non trouve \n");

   detruire_pile(pile);
}

