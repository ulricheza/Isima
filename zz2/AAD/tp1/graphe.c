/**
 * \file graphe.c
 * \brief Programme de gestion de graphes
 * \author Maxime Escourbiac Jean Christophe Septier
 * \version 0.1
 * \date Vendredi 1er Octobre
 *
 * Programme de creation/gestion de graphes avec les listes d'adjacence
 *
 */

#include "graphe.h"

graphe_t * creation_arbre(char * nom_fic)
{
   int i,from,nb_arc_sommet,sommet_prec = 0;
   graphe_t * gr;
   FILE * fic;
   char ligne[100];
   char * test;
   fic = fopen(nom_fic,"rt");
   if(!fic)
   {
      fprintf(stderr,"erreur ouverture fichier de donnees \n");
      exit(EXIT_FAILURE);
   }
   gr = (graphe_t *) malloc(sizeof(graphe_t));
   if(!gr)
   {
      fprintf(stderr,"erreur allocation graphe_t\n");
      exit(EXIT_FAILURE);
   }
   /*lecture a blanc de la premiere ligne du fichier*/
   test = fgets(ligne,99,fic);
   /*lecture du nombre de sommet*/
   test = fgets(ligne,99,fic);
   sscanf(ligne,"%*s %*c %d",&(gr->nb_sommets));
   /*lecture du nombre d'arc*/
   test = fgets(ligne,99,fic);
   sscanf(ligne,"%*s %*c %d",&(gr->nb_arcs));
   
   /* allocation liste_sommet & liste_arc*/
   
   gr->sommets = (sommet_t *)malloc(gr->nb_sommets * sizeof(sommet_t));
   gr->arcs = (arc_t *)malloc(gr->nb_arcs * sizeof(arc_t));
   if(!gr->sommets || !gr->arcs)
   {
      fprintf(stderr,"erreur allocation liste sommets et liste arc \n");
      exit(EXIT_FAILURE);
   }
   /*lecture de la phrase de commentaires*/
   test = fgets(ligne,99,fic);
   /*lecture des nodes*/   
   for(i=0;i<gr->nb_sommets;i++)
   {
      test = fgets(ligne,99,fic);
      sscanf(ligne,"%*s %*c %d %*c %*c %*c %d %*c %*c %*c %d",&(gr->sommets[i].label),&(gr->sommets[i].x),&(gr->sommets[i].y));
   }
   test = fgets(ligne,99,fic);
   /*lecture de la partie arc*/
   /*lecture avant la boucle pour eviter un test dans if de la boucle*/
   test = fgets(ligne,99,fic);
   sscanf(ligne,"%*s %*c %*d %*c %*s %*c %d %*c %*s %*c %d %*c %*s %*c %f",&from,&(gr->arcs[0].destination),&(gr->arcs[0].distance));
   sommet_prec = from;
   gr->sommets[from -1].first_arc = 0;
   nb_arc_sommet = 1;
   for(i=1;i<gr->nb_arcs;i++)
   {
      test = fgets(ligne,99,fic);
      sscanf(ligne,"%*s %*c %*d %*c %*s %*c %d %*c %*s %*c %d %*c %*s %*c %f",&from,&(gr->arcs[i].destination),&(gr->arcs[i].distance));
      if(from != sommet_prec)
      {
          gr->sommets[sommet_prec-1].nb_arcs = nb_arc_sommet;
          gr->sommets[from-1].first_arc = i;
          sommet_prec = from;
          nb_arc_sommet = 1;
      }
      else
         nb_arc_sommet++;
   }
   gr->sommets[sommet_prec-1].nb_arcs = nb_arc_sommet;
   
   fclose(fic);
   return gr;
}