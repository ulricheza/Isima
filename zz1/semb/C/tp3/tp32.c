#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*---------------------*/
/*Maxime Escourbiac    */
/*22/10/09             */
/* initiatiation au C  */
/*---------------------*/

/*Dans ce tp etudions les fonctions sur les fonctions */
/*sur les chaines de caracteres                       */

/*declarations des fonctions*/
int longmax(char tab[]);
void catmax(char tab1[],char tab2[]);
void cpymax(char tab1[],char tab2[]);

int main()
{
   char prenom[255];
   char nom[255];
   int n;
   int i;
   char ensemble[510];
   char ensemble2 [600];
   printf("veuillez tapez votre prenom\n");
   scanf("%s",prenom);
   printf("veuillez taper votre nom\n");
   scanf("%s",nom);
   printf("choisir n\n");
   scanf("%d",&n);
   for(i=0;i<n;i++) 
   {
      printf("Merci %s\n",prenom);
   }
   printf(" nbre de lettre de prenom avec strlen %d et ma fonction %d \n",strlen(prenom),longmax(prenom));
   printf("nous allons concatener les chaines nom et prenom\n");
   strcpy(ensemble,prenom);
   strcat(ensemble," ");
   strcat(ensemble,nom);
   printf("ensemble == %s\n",ensemble);
   printf("verifions nos fonctions!\n");
   cpymax(ensemble2,prenom);
   catmax(ensemble2," ");
   catmax(ensemble2,nom);
   printf("ensemble2 == %s\n",ensemble2);
}


/* Pour les focntiosn suivante son utilisera pas de pointeur!!!!!!!*/
/*fonction equivalente a strlen*/
int longmax(char tab[])
{
   int i = 0;
   while(tab[i] != '\0')
   {
      i++;
   }
   return i;
}

/*fonctiosn equivalente strcat*/
void catmax(char tab1[],char tab2[])
{
   int i = strlen(tab1);
   int j = 0 ;
   while(tab2[j]!='\0')
   {
      tab1[i++]=tab2[j++];
   }
   tab1[++i]='\0';  
}

/*fonction equivalente a strcpy*/
void cpymax(char tab1[],char tab2[])
{
   int i = 0;
   while(tab2[i]!='\0')
   {
      tab1[i]=tab2[i++];
   }
   tab1[++i]='\0';
          
