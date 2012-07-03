/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*Maxime Escourbiac                                                    01/01/2009 */
/*ZZ1                                                                             */
/*TP 1 : C                                                                        */
/*description: 1er partie                                                         */
/*manipulation de chaines de caracteres                                          */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
   /*declaration des variables*/
   int i = 0;
   int j,k;
   char chaine ="Bonjour les zz1";
   char comp1 []="abc";
   char comp2 []="bcd";
   char comp3 []="cde";
   char testcpy [4];

   /*premiere question et deuxieme question*/
   printf("%s\n",chaine);
   printf("strlen(chaine) = %d\n",strlen(chaine));
   chaine[7] = '\0';
   printf("%s\n",chaine);
   printf("strlen(chaine) = %d\n",strlen(chaine));
   chaine[7] = ' ';
   printf("%s\n",chaine);
   printf("strlen(chaine) = %d\n",strlen(chaine));
   
   /*troisieme question*/ 
   printf(" A = %d et a = %d \n",'A','a');
   while(*(chaine + i))
   {   
       printf("%c  en decimal:%d en hexa: %x \n",*(chaine + i),*(chaine + i),*(chaine + i));
       i++;
   }

   /*quatrieme question*/
   i = strcmp(comp1,comp2);
   j = strcmp(comp3,comp2);
   k = strcmp(comp1,comp1);
   printf("valeur de retour si s1<s2 : %d\n",i);
   printf("valeur de retour si s1>s2 : %d\n",j);
   printf("valeur de retour si s1=s2 : %d\n",k);
   
   /*question bonus */
   printf("on verifie que strcpy est pas securisee\n");
   strcpy(testcpy,chaine);
   printf("%s\n",testcpy); /*mais par miracle ca marche !!!!*/
   return 0;
}
