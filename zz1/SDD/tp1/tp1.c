/**
 * \file news.c 
 * \brief Programme de gestion de news date a partir d'un fichier
 * \author Maxime ESCOURBIAC Sebastien SAINT_MARTIN
 * \version 1.0
 * \date Mercredi 10 mars 2010
 *  
 *  Programme qui gere un systeme de news avec un systeme de date 
 *  Les news seront ecrites dans un fichier qui sera passer en parametre
 *
 */



#include "tp1.h"



int main(int argc, char *argv[])
{
  char * mess_t; /*pointeur sur le message pour la creation de cellule*/
  int deb_t;     /*entier pour la creation de cellule, debut du message*/
  int fin_t;     /*entier pour la creation de cellule, fin de message*/
  int deb_anc;   /*entier pour chercher la date des messages a modifier*/
  int deb_new;   /*Nouvelle date de debut pour la modification de date */
  int choix,fin=0; /*booleen pour sortir du programme*/
  int erreur = 0;  /*booleen d'erreur lors de la creation de la liste chainee*/
  FILE * fic;      /*Pointeur sur le fichier de lecture*/
  news_t * cell;   /*pointeur sur la cellule news_t qui va etre insere*/
  news_t * tete = NULL; /*pointeur de tete de la listre chainee*/

  if (argc == 2)  /*test si il y a deux arguments*/
  {
     printf("Ouverture du fichier\n");
     fic = fopen(argv[1],"rt"); 
     if(fic!=NULL) /*test si fichier a ete ouvert*/
     {
        printf("Lecture dans le fichier\n");
        lect_fichier (fic, &deb_t, &fin_t, &mess_t); /*lecture de la premiere phrase*/
        while(!feof(fic) && erreur == 0)
        {
	   cell = creation_cell(deb_t, fin_t , mess_t); /*allocation de la cellule */
           free(mess_t); /*on libere au fur a mesure mess_t*/
           if (cell != NULL)
              insertion (cell, &tete); 
           else
           {
              printf("creation de la cellule impossible \n");
	      erreur = 1;  /*si il y a eu un probleme d'allocation de cellule*/
           }
           lect_fichier (fic, &deb_t, &fin_t, &mess_t);
        }
        free(mess_t);
	
	   
        
	   
        while(fin == 0)  /*menu */
        {
           printf("----------------------TP1SDD----------------------\n");
           printf("-----------------------MENU-----------------------\n");
           printf("1) modification des dates de debut dans un message\n");
           printf("2) affichage des news d'actualite\n");
           printf("3) suppression des news obsoletes\n");
           printf("4) recherche de news par motif\n");
           printf("5) sauvegarde de la liste chainee dans un fichier\n");
           printf("6) affichage de la liste chainee\n");
           printf("autre : sortie du programme\n");
           scanf("%d",&choix);

           switch(choix)
           {
              case 1:
                       printf("date du message a supprimer \n"); /*lecture de la nouvelle et ancienne date*/
                       scanf("%d",&deb_anc);
                       printf("nouvelle date de debut de message\n");
                       scanf("%d",&deb_new);
                       modif_date_deb(&tete,deb_anc,deb_new);
                       break;
              case 2:
                       printf("affichage des news d'actualite\n");
                       affic_ajour(tete);
                       break;
              case 3:
                       printf("Maintenant suppression des news obsoletes\n");
                       erase_obsolete(&tete);
                       break;
              case 4:
                       affic_motif(tete);
                       break;
              case 5:
                       printf("sauvegarde de la structure dans un fichier\n");
                       sauvegarde_fic(tete);
                       break;
              case 6:
                       affic(tete);
                       break;
              default:
                        fin = 1;  /*booleen de fin de programme*/
                        break;
           }
        }

        fclose(fic); /*fermeture du fichier*/
        erase_all(tete); 
     }
     else
        printf("ouverture du fichier impossible\n");
   }
   else
      printf("souci avec l'argument passe en parametre \n");

  return 0;
}


void lect_fichier (FILE * fic, int * deb, int * fin, char ** mess)
{
/*lecture de la phrase complete*/
   char temp[101]; /*chaine de caractere temporaire de taille max*/

   fscanf(fic,"%8d%8d",deb,fin); /*lecture de date de debut date de fin*/
   fgets(temp,101,fic);/*lecture du message*/
   temp[strlen(temp)-1]=0; /*on enleve le \n due au fgets*/
   *mess = (char *)malloc((strlen(temp)+1)*(sizeof(char)));
   strcpy(*mess,temp); 
}

news_t * creation_cell(int deb, int fin , char * mess)
{
   news_t * cellule = malloc(sizeof(news_t));  /*allocation de la cellule news*/
   /*test si cellule bien alloue*/
   if(cellule!=NULL)
   {
      /*mise en place des valeurs de la cellule*/
      cellule->deb = deb;
      cellule->fin = fin;
      cellule->mess= (char *)malloc((strlen(mess)+1)*(sizeof(char))); /*allocation dynamique*/
      strcpy(cellule->mess,mess);
   }
   else
      printf("allocation impossible\n");
   return cellule;
}


int rech_prec(int deb, news_t ** tete, news_t *** prec_t)
{
   int existe = 1; /*booleen d'existence d'un message de date de debut deb*/
   /*necessite de passer par un triple pointeur car prec dans la fonction */
   /*insertion est un double pointeur                                     */
   news_t * courant = *tete; /*pointeur de parcours*/
   *prec_t = tete;           /*pointeur precedent*/
   /*recherche du precedent*/
   while( courant != NULL && courant->deb < deb) /*recherche dans une liste chainee triee*/
   {
      *prec_t = &courant->suivant;
      courant = courant->suivant;
   }
   if(courant == NULL || courant->deb != deb) /*si la valeur existe*/
      existe = 0;
   
   return (existe);
}

void insertion (news_t * cellule, news_t ** tete)
{
   news_t ** prec; /*prec est un pointeur sur un pointeur de news_t*/
   rech_prec (cellule->deb, tete, &prec);
   cellule->suivant = *prec;  /*adjonction dans une liste chainee*/
   *prec = cellule;
   
}
void affic_cell(news_t * cell)
{
   /*fonction d'affichage d'une cellule */
   printf("date de debut: %d \n",cell->deb);
   printf("date de fin  : %d \n",cell->fin);
   printf("Message      : %s \n\n",cell->mess);
   printf("---------------------------------\n");
   printf("---------------------------------\n");
}

void affic(news_t * tete)
 {
      news_t * courant = tete;/*pointeur de parcours de la liste chainee*/
      while(courant)
      {
         affic_cell(courant);
         courant = courant->suivant; /*on passe a la case suivante*/
      }
 }      

void erase_all(news_t * tete)
{
   news_t * courant = tete; /*pointeur de parcours de la liste chainee*/
   news_t * temp; /*pointeur temporaire pour le free*/
   
   while(courant)
   {
      temp = courant; /*sauvegarde du pointeur*/
      courant = courant->suivant;
      free(temp->mess); /*liberation du message*/
      free(temp); /*liberation de la cellule*/
   }
}

void sauvegarde_fic(news_t * tete)
{
   news_t * courant = tete; /*pointeur de parcours*/
   FILE * fichier; /*pointeur sur le fichier ou on va sauvegarder la liste*/
   char name[20];  /*chaine de caractere pour stocker le nom du fichier a ouvrir*/
   printf("nom du fichier de sauvegarde de la structure\n");
   getc(stdin); /*lecture du nom du fichier*/
   fgets(name,20,stdin);
   name[strlen(name)-1]=0;
   fichier = fopen(name,"wt"); /*ouverture du fichier*/
   if(fichier) /*si le fichier a ete cree*/
   {
      while(courant) /*pour chaque cellule news*/
      {
         /*on ecrit la cellule dans le fichier comme dans le fichier d'entree*/
         fprintf(fichier,"%d%d%s\n",courant->deb,courant->fin,courant->mess);
         courant = courant->suivant;
      }
      fclose(fichier); /*on ferme le fichier de sauvegarde*/
   }
   else
      printf("creation fichier impossible\n");
}

void affic_ajour(news_t * tete)
{
   int today; /*date actuelle sous la forme aaaammjj*/
   news_t * courant = tete; /*pointeur de parcours*/

   today = date_act(); /*recuperation de la date actuelle*/
 
   while((courant != NULL) && (courant->deb < today))
   {
      if(courant->fin > today) /*si la date de fin est sup a celle actuelle*/
         affic_cell(courant);
      courant = courant-> suivant;
   } 

}

int date_act()
{
   int date = 0; /*entier de date*/
   struct tm * actual; /*structure pour la date humaine*/
   time_t actual_temp; /*variable de recuperation date systeme*/

   time(&actual_temp);
   actual = localtime(&actual_temp);
   /*transformation de la date*/
   date = actual->tm_mday + (actual->tm_mon * 100) + (1900 + actual->tm_year)*10000;
   return(date);
}

void erase_obsolete(news_t ** tete)
{
   int date; /*entier sur la date*/
   news_t ** prec = tete; /*pointeur sur le precedent*/
   news_t * cour = *tete; /*pointeur de parcours*/

   date = date_act();
   while((cour!= NULL) && (cour->deb < date))
   {

      if(cour->fin < date) /*si la date de fin est inf a la date actuelle*/
         suppr_date(cour,prec);
      else
         prec = &cour->suivant;

      cour = *prec;
   }
}

void suppr_date(news_t * cour, news_t ** prec)
{
   /*suppresion dans une liste chainee*/
   *prec = cour->suivant;
   free(cour->mess);
   free(cour);
}

void modif_date_deb(news_t ** tete, int date_deb_ancien, int date_deb_new)
{
   news_t * cour; /*pointeur de parcours*/
   news_t ** prec = tete; /*pointeur sur le precedent*/

   if(rech_prec(date_deb_ancien, tete, &prec)) /*test si la valeur existe*/
   {
      while( *prec != NULL && (*prec)->deb == date_deb_ancien) /*on modifie tous les messages*/
                                                               /*de la date recherche        */
      {
         cour = *prec;
         *prec = cour->suivant;
         cour->deb = date_deb_new;
         insertion(cour,tete);
      }
   }
   else
       printf("le message a la date %d n'existe pas \n",date_deb_ancien);
}

void affic_motif(news_t * tete)
{
   char motif[101]; /*chaine de caractere pour le modif*/
   news_t * courant = tete; /*pointeur de parcours*/
   printf("lecture du motif\n");
   getc(stdin);
   fgets(motif,101,stdin);
   motif[strlen(motif)-1]=0;
   /*la fonction strstr ne prend pas en compte les \0 mais prend en compte les \n      */
   /*donc dans ce cas la on est oblige de mettre un \0 a la fin de la chaine de motif  */
   while(courant)
   {
      if(strstr(courant->mess, motif) != NULL) /*si la chaine motif a ete trouve*/
         affic_cell(courant);
      courant = courant->suivant;
   }
}
