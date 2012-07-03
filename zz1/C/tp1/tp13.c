/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*Maxime Escourbiac                                                    30/09/2009 */
/*ZZ1                                                                             */
/*TP 1 : 3                                                                        */
/*description:                                                                    */
/*les fonctions sur les chaines de caracteres                                     */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int longmax(char tab[]);
void catmax(char tab1[],char tab2[]);
void cpymax(char tab1[],char tab2[]);
int maxcmp(char tab1[],char tab2[]);

int main()
{
   char test1[]="salut all";
   char test2[255];
   char a1[]="abc";
   char a2[]="bcd";
   char a3[]="abcd";
   cpymax(test2,test1);
   printf("test2 = %s \n",test2);
   printf("long de test1 = %d \n",longmax(test1));
   printf("valeur de retour de ma cmp : %d \n", maxcmp(test1,test2));
   printf("valeur de retour de ma cmp : %d \n", maxcmp(a1,a2));
   printf("valeur de retour de ma cmp : %d \n", maxcmp(a2,a1));
   printf("valeur de retour de ma cmp : %d \n", maxcmp(a1,a3));
   printf("valeur de retour de ma cmp : %d \n", maxcmp(a3,a1));
   return 0;
}




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
   tab1[i]='\0';

}

/*fonction equivalente a strcmp*/
int maxcmp(char tab1[],char tab2[])
{  
   int i = 0;
   int retour = 0;
   while(tab1[i] && tab2[i] && !retour)
   {
      if(tab1[i] < tab2[i])
         retour = -1;
      else if(tab1[i] > tab2[i])
                retour = 1;
      i++;
   }
   if(tab1[i] || tab2[i])
   {
     if(tab1[i] < tab2[i])
        retour = -1;
     else 
        retour = 1;
   }
   return retour;
}
