/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*Maxime Escourbiac                                                    01/01/2009 */
/*ZZ1                                                                             */
/*TP 5 : C                                                                        */
/*description: 2ieme partie                                                       */
/*manipulation sur les structures                                                 */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <crypt.h>

/*declaration de la structure login_t */

typedef struct login 
{
   char log[10];
   char pass[10];
   char machine[10];
   struct login * suivant;
}login_t;

/*declaration de fonction*/
void insertion(login_t * tete);
void affichage(login_t tete);
void supprimer (login_t * tete);
int verif_pass (char * pass);
int isupper_max (char c);
int ispunct_max (char c);
int isdigit_max (char c);
char * generer();
int main (int argc , char * argv[])
{
   login_t tete;
   int menu;
   int exit = 0;
   char pass[20];
   char MD5_key[]= "$1$ISIMA$";
   char DES_key[]= "ZZ";
   tete.suivant = NULL;
   FILE * fic;
   fic = fopen("generation.txt","w");
   fprintf(fic,"-----Generation de pass------\n\n");
   while(exit == 0)
   {
      printf("-----MENU-----\n");
      printf("1: Inserer    \n");
      printf("2: Afficher   \n");
      printf("3: Supprimer  \n");
      printf("4: verif_pass \n");
      printf("5: Generer    \n");
      printf("Other: Quit   \n");
      printf("--------------\n");
      scanf("%d",&menu);
      switch (menu)
      {
         case 1 : insertion(&tete);
                  system("clear");
                  break;
         case 2 : affichage(tete);
                  break;
         case 3 : supprimer(&tete);
                  break;
         case 4 : printf("pass a verifier\n");
                  scanf("%s",pass);
                  if(verif_pass(pass))
                     printf("pass est OK\n");
                  else
                     printf("pass pourri\n");
                  break;
	 case 5 : strcpy(pass,generer());
	          fprintf(fic,"mot de passe generer == %s \n",pass);
		  fprintf(fic,"generer en MD5 == %s \n",crypt(pass,MD5_key));
		  fprintf(fic,"generer en DES == %s \n",crypt(pass,DES_key));
		  break;

         default : system("clear");
                   exit = 1;
      }
   }
   fclose(fic);
   return(EXIT_SUCCESS);
}

void insertion(login_t * tete)
{
   login_t * nouveau = (login_t *)malloc(sizeof(login_t));
   nouveau -> suivant = tete -> suivant;
   tete -> suivant = nouveau;
   printf("log?\n");
   scanf("%s",nouveau -> log);
   printf("pass?\n");
   scanf("%s",nouveau -> pass);
   printf("machine?\n");
   scanf("%s",nouveau -> machine);
}

void affichage(login_t tete)
{
   login_t * courant = tete.suivant;
   while(courant)
   {
      printf("------------------\n");
      printf("login = %s \n",courant -> log);
      printf("pass = %s \n",courant -> pass);
      printf("machine = %s \n",courant -> machine);
      courant = courant -> suivant;
   }
}

void supprimer (login_t * tete)
{
   login_t * cour = tete -> suivant ;
   login_t * suiv;
   while(cour)
   {
      suiv =  cour -> suivant;
      free(cour);
      cour = suiv;
   }
   tete -> suivant = NULL;
   printf("suppression terminee \n");
}

int verif_pass (char * pass)
{
   int maj = 0;
   int special = 0;
   int result = 0;
   int i = 0;
   if(strlen(pass)>7)
   {
      for(i=0;i<strlen(pass);i++)
      {
         if(isupper_max(pass[i]))
            maj++;
         else 
         {
            if(isdigit_max(pass[i]) || ispunct_max(pass[i]))
               special++;
         }
      }
      if(maj>0 && special>0)
         result = 1;
   }
   return(result);
}

/*fonctions reecrites de la bibliotheques ctype.h*/
int isupper_max (char c)
{
   int res = 0;
   int temp = (int)c;
   if(64 < temp && temp < 91)
      res = 1;
   return(res);
}

int isdigit_max (char c)
{
   int res = 0;
   int temp = (int)c;
   if(47 < temp && temp < 58)
      res = 1;
   return(res);
}

int ispunct_max (char c)
{
   int res = 0;
   int temp = (int)c;
   if(!( (47<temp && temp<58) || (64<temp && temp<91) || (96<temp && temp<123)))
      res=1;
   return(res);
}

/*-----------------------------------------*/
/*fonction de generation de mots de passe  */
/*le mot de passe doit avoir 8 caractere   */
/*dont une majuscule et un caractere       */
/*different des lettres de l'alphabet      */
/*-----------------------------------------*/
/*Pour des raisons pratiques:              */
/*le caractere special sera entre 33 et 64 */
/*-----------------------------------------*/

char * generer()
{
   char temp[10];
   char * pass = (char *)malloc(8*sizeof(char));
   int i = 0;
   int j = 8;
   int k;
   srand(time(0));
   temp[0]=(char)(rand()%32 + 33); /*generation du caractere special*/
   temp[1]=(char)(rand()%26 + 65);/*generation du caractere majuscule*/
   for(i=2;i<8;i++)
     temp[i]=(char)(rand()%94 + 33);/*generation du reste du code*/
   /*melange des lettres obtenues*/
   for(i=0;i<8;i++)
   {
     k = rand()%j;
     pass[i]=temp[k];
     j--;
     temp[k]=temp[j];
   }
   pass[8]='\0';
   return(pass);
}
