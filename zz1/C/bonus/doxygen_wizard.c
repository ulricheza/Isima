/**
 * \file doxygen_wizard.c
 * \brief programme d'ecriture d'en-tete doxygen
 * \author Maxime ESCOURBIAC
 * \version 0.5
 * \date 20 novembre 2009
 *
 */

/*declaration des bibliotheques */

#include <stdio.h>
#include <stdlib.h>

/*fin de declaration des bibliotheque*/



/*declaration des fonctions */

void gene_fichier(FILE * fic);
void gene_fonction(FILE * fic);
void gene_struct(FILE * fic);

/*fin de declaration des fonctions */


int main(int argc, char * argv[])
{
   int choix = 1;
   FILE * fichier;
   fichier = fopen("doxygen_code.h","wt");
   fprintf(fichier,"/*Ce fichier a ete genere a l'aide de doxygen_wizard*/ \n");
   while(choix)
   {
      system("clear");
      printf("*-------doxygen wizard-------*\n");
      printf("* 1) en-tete de fichier      *\n");
      printf("* 2) en-tete de fonction     *\n");
      printf("* 3) en-tete de structure    *\n");
      printf("* 0) sortie                  *\n");
      printf("*----------------------------*\n");
      scanf("%d",&choix);
      getc(stdin);
      system("clear");
      switch (choix)
      {
         case (1): gene_fichier(fichier);
                   break;
         case (2): gene_fonction(fichier);
                   break;
         case (3): gene_struct(fichier);
                   break;
         default : choix = 0;
      }
    }
    fprintf(fichier,"\n /*commentaire generes par dioxygen_wizard */ \n");
    fclose(fichier);
    system("kate doxygen_code.h");
    exit(EXIT_SUCCESS);
}

/**
 * \fn void gene_fichier(FILE * fic)
 * \brief creation d'en-tete de fichier
 *
 * \param fic pointeur sur le fichier d'ecriture
 * \return rien
 */
void gene_fichier(FILE * fic)
{
   
  char temp[50];
  fprintf(fic,"/**\n");
  printf("saisie du nom \n");
  fgets(temp,49,stdin);
  fprintf(fic," * \\file %s",temp);
  printf("saisie de la fonction du programme\n");
  fgets(temp,49,stdin);
  fprintf(fic," * \\brief %s",temp);
  printf("saisie de l'auteur du programme\n");
  fgets(temp,49,stdin);
  fprintf(fic," * \\author %s",temp);
  printf("saisie de la version du programme\n");
  fgets(temp,49,stdin);
  fprintf(fic," * \\version %s",temp);
  printf("saisie de la date\n");
  fgets(temp,49,stdin);
  fprintf(fic," * \\date %s",temp);
  fprintf(fic,"*/\n\n\n");
}

/**
 * \fn void gene_fonction(FILE * fic)
 * \brief creation d'en-tete de fonction
 *
 * \param fic pointeur sur le fichier d'ecriture
 * \return rien
 */

void gene_fonction(FILE * fic)
{
  int i;
  int nbre_param;
  char temp[50];
  fprintf(fic,"/**\n");
  printf("saisie du prototype de fonction \n");
  fgets(temp,49,stdin);
  fprintf(fic," * \\fn %s",temp);
  printf("saisie du but de la fonction \n");
  fgets(temp,49,stdin);
  fprintf(fic," * \\brief %s",temp);
  fprintf(fic," *\n");
  printf("nombre de parametre? \n");
  scanf("%d",&nbre_param);
  getc(stdin);
  for(i=0;i<nbre_param;i++)
  {
     printf("<nom> <but>\n");
     fgets(temp,49,stdin);
     fprintf(fic," * \\param %s",temp);
  }
  printf("saisie du but du parametre de retour\n");
  fgets(temp,49,stdin);
  fprintf(fic," * \\return %s",temp);
  fprintf(fic,"*/\n\n\n");
}

/**
 * \fn void gene_struct(FILE * fic)
 * \brief creation d'en-tete de fonction
 *
 * \param fic pointeur sur le fichier d'ecriture
 * \return rien
 */
void gene_struct(FILE * fic)
{
  char temp[50];
  fprintf(fic,"/**\n");
  printf("saisie du nom de la structure \n");
  fgets(temp,49,stdin);
  fprintf(fic," * \\struct %s",temp);
  printf("saisie de la description de la structure \n");
  fgets(temp,49,stdin);
  fprintf(fic," * \\brief %s",temp);
  fprintf(fic,"*/\n\n\n");
}
