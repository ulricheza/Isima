/*-------------------------------------*/
/*Utilisation du makefile              */
/*-------------------------------------*/

#include "entete.h"



int main(int argc, char * argv[])
{
  char test;
  int total_ligne = 0;
  int nombr_com = 0;
  FILE * lect;
  FILE * ecrit= fopen("commentaire.c","wt");
  
  if(argc!=2)
  {
      printf("souci avec l'argument\n");
      exit(EXIT_FAILURE);
  }
  lect = fopen(argv[1],"rt");
  printf("generation d'une entete dioxygen?\n");
  scanf("%c",&test);
  getc(stdin);
  if(tolower(test)=='o')
     adj_dio(ecrit);
  while(!feof(lect))
  {
     adj_lch_fin(lect,ecrit,&total_ligne,&nombr_com);
  }
  fclose(lect);
  fclose(ecrit);
  printf("nombre de lignes: %d \n",total_ligne);
  printf("nombre de lignes de commentaires: %d \n",nombr_com);
  printf("ratio en %% : %f\n",(float)nombr_com /(float)total_ligne*100.0 );
  system("kate commentaire.c");
  return(EXIT_SUCCESS);
}

void adj_lch_fin( FILE * lect, FILE * ecrit,int * ligne, int * comm)
{
   char * temp = (char *)malloc(81*sizeof(char));
   fgets(temp,79,lect);
   *ligne = *ligne +1;
   if(temp[0]=='/' && temp[1]=='*')
   {
      *comm = *comm +1;
      if(!strncmp(temp,"/*declaration",13))
      {
          while(strncmp(temp,"/*fin de declaration",20)!=0 && !feof(lect))
          {
	     *comm = *comm +1;
	     *ligne = *ligne +1;
             fprintf(ecrit,"%s",temp);
             fgets(temp,79,lect);
          }
          fprintf(ecrit,"%s\n",temp);
      }
      else
         fprintf(ecrit,"%s",temp);
   }
}

void adj_dio(FILE * fic)
{
  char temp[50];
  fprintf(fic,"/**\n");
  printf("saisie du nom \n");
  fgets(temp,49,stdin);
  fprintf(fic," * \\file %s\n",temp);
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
  fprintf(fic,"*/\n");
}
