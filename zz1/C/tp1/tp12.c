/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*Maxime Escourbiac                                                    30/09/2009 */
/*ZZ1                                                                             */
/*TP 1 : 2                                                                        */
/*description:                                                                    */
/*codage de l'examen                                                              */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char * argv[])
{
   /*initialisation des variables*/
   int tab[200];
   int i = 0;
   int j ;
   int val;
   char name[]="occurence.txt";
   FILE * fic;
   FILE * fic2;
   int temp[26] = {0};
   int total[26] = {0};
   char word[255];
   char car;
   char temp2[255];
   char * t;
   /*question 1*/
   srand(time(0));
   for(i=0;i<200;i++)
   {
      tab[i]=rand()%101;
      printf("tab[%d] = %d \n",i,tab[i]);
   }
   printf("veuillez rentrer un nombre \n");
   scanf("%d",&val);
   for(i=0;i<200;i++)
   {
   	  if(tab[i] < val) tab[i] = -tab[i];
      printf("tab[%d] = %d \n",i,tab[i]);
   }
   
   /*question 2*/
   fic = fopen(name,"r");
   if (!fic) printf("probleme a l'ouverture\n");
   else
   {
   	  while(!feof(fic))
   	  {
   	     i = 0;
   	     fscanf(fic,"%s",word);
   	     while(word[i])
   	     {
   	     	word[i]=tolower(word[i]);
   	     	j = (int)word[i] - 97;
            temp[j]++;
            i++;
   	     }
   	     /*occurence dans le mot lu*/
   	     printf("%s\n",word);
   	     for(i=0;i<26;i++)
   	     {   
   	        printf("il y a %d de %c \n",temp[i],(char)(i + 97));
   	        total[i]= total[i] + temp[i];
   	        temp[i]=0;
   	     } 
   	  }
      printf("au total\n");
      for(i=0;i<26;i++)
         printf("il y a %d de %c \n",total[i],(char)(i + 97));
    
   }
   
   /*question3*/
      printf("veuillez rentrer une phrase\n");
      getc(stdin);
      gets(temp2);
   while(strcmp(temp2,"."))
   {
      i = 0;
      while(temp2[i])
      {
          car = tolower(temp2[i]);
          if(car > 96 && car < 123)
          {
              if(car < 110)
                 temp2[i] = temp2[i] + 13;
              else
                 temp2[i] = temp2[i] - 13;
          }
          i++;
      }
      printf("votre phrase codee\n");
      printf("%s\n",temp2);
      printf("veuillez rentrer une phrase\n");
      gets(temp2);
      
   }

   return 0;
}
