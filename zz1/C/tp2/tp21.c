/*--------------------------------------------------------------------------------*/
/*                                                                                */
/*Maxime Escourbiac                                                    13/10/2009 */
/*ZZ1                                                                             */
/*TP 2 : tableau statique a 2 dimensions                                          */
/*description:                                                                    */
/* creation du moteur de jeu d'un SUDOKU                                          */
/*                                                                                */
/*--------------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 9



int initialiser(int **tab);
void afficher(int **tab);
void saisir ( int ** tab,int * rempl);
int verif_ligne(int **grille, int choix , int atest);
int verif_grille(int ** grille);
int verif_region(int **grille, int a , int b);
void generer(int ** tab,int * remp);

int main(int argc, char * argv[])
{
/*declaration des variables*/   
   int i;
   int ** grille = (int**)malloc(N*sizeof(int *));
 /*int ** reservation = (int**)malloc(N*sizeof(int *));*/
   int * remplissage = (int*)malloc(sizeof(int));
   int temp;
   int res = 0;
/* fin des declarations*/
   *remplissage = 0;
   for(i=0;i<N;i++)
      grille[i]=(int *)malloc(N*sizeof(int));
   printf("*****SUDOKU*****\n");
   temp = initialiser(grille);
 /*temp = initialiser(reservation);*/
   generer(grille,remplissage);
   printf("remp=%d\n",*remplissage);
   afficher(grille);
   while(res==0)
   {
      saisir(grille,remplissage);
      afficher(grille);
      printf("remp=%d\n",*remplissage);
      if(*remplissage == 81)
         res=verif_grille(grille);
   }
   printf("Bravo,reussi\n");
   return 0;
}


/*-----------------------------------*/
/*fonction initialiser : entréee tab */
/*initialise tous les elements du tab*/
/*a 0 et retourne un entier = a 0    */
/*-----------------------------------*/

int initialiser(int **tab)
{
   int i,j;
   for(i=0;i<N;i++)
   {
       for(j=0;j<N;j++)
          tab[i][j] = 0;
   }
   return 0;
}

/*-----------------------------------*/
/*fonction initialiser : entréee tab */
/*affiche tous les elts de la grille */
/*-----------------------------------*/

void afficher(int **tab)
{
   int i,j;
   for(i=0;i<N;i++)
   {
       for(j=0;j<N;j++)
          printf("%d  ",tab[i][j]);
       printf("\n");
   }
   printf("\n");
}

/*------------------------------------*/
/*fonction saisir                     */
/*saisie d'un element + verification  */
/*------------------------------------*/
/*on apportera une solution a la      */
/*question bonus dans                      */
/*------------------------------------*/

void saisir ( int ** tab,int * rempl/*,int**reservation*/)
{
   int i   = N +1;
   int j = i;
   int val ;
   char reponse[10];
   /*do*/ 
   i  = N +1;
   j = i;
   val = j;
   while(i>N || i < 1)
   {
       printf("Entrez le numero de ligne\n");
       scanf("%d",&i);
   }
   while(j>N || j < 1)
   {
       printf("Entrez le numero de colonne\n");
       scanf("%d",&j);
   }
   while(val>N || val < 1)
   {
       printf("Entrez la valeur\n");
       scanf("%d",&val);
   }
   if(tab[i-1][j-1])
   {
      printf("Voulez vous remplacer la valeur\n");
      scanf("%s",reponse);
      if(!strcmp(reponse,"oui"))
         tab[i-1][j-1] = val;
   }
   /*while(reservation[i][j])*/
   else
   {
      tab[i-1][j-1]=val;
      *rempl=*rempl + 1;
   }
}

/*------------------------------------*/
/*fonction generer: genere la matrice */
/*de base du sudoku,                  */
/*------------------------------------*/
/*on va lire les valeurs dans un file */

void generer(int ** tab,int * remp)
{
   FILE * fic;
   char name[]="saisie.txt";
   int temp;
   int i = 0;
   int j = 0;
   fic=fopen(name,"r");
   while(i<9 && !feof(fic))
   {
       while(j<9 && !feof(fic))
       {
          fscanf(fic,"%d",&temp);
          tab[i][j]=temp;
          if(temp!=0)
           *remp=*remp +1;
          j++;
       }
       i++;
       j=0;
   }
}



/*------------------------------------*/
/*fonction:verif_ligne                */
/*verifie l'integrité d'une ligne ou  */
/*colonne                             */
/*------------------------------------*/

int verif_ligne(int **grille, int choix , int atest)
{
   int i=0;
   int temp[N]={0};
   int res = 1;
   int a;
   if(choix==1) /*test sur une ligne*/
   {
      while(i<N && res == 1)
      {
          a = grille[atest][i];
          if(temp[a-1]!=0) res=0;
          temp[a-1]=1;
          i++;
      }
   }
   else
   {
      while(i<N && res == 1)/*test sur la colonne*/
      {
          a = grille[i][atest];
          if(temp[a-1]!=0) res=0;
          temp[a-1]=1;
          i++;
      }
   }
   return (res);
}
/*------------------------------------*/
/*fonction:verif_ligne                */
/*verifie l'integrité d'une ligne ou  */
/*colonne                             */
/*------------------------------------*/

int verif_region(int **grille, int a , int b)
{
   int temp[N]={0};
   int i,j,k;
   int res = 1;
   i = 3*a;
   j = 3*b;
   while(i<(3*a+3) && res==1)
   {
      while(j<(3*b+3) && res == 1)
      {   
         k=grille[i][j];
         if(temp[k-1])res=0;
         temp[k-1]=1;
         j++;
      }
      i++;
      j = 3*b;
   }
   return res;
}

/*-------------------------------------*/
/*fonction:verif_grille                */
/*verifie l'integrite de la grille     */
/*-------------------------------------*/

int verif_grille(int ** grille)
{
  int i=0;
  int j=0;
  int horiz=1;
  int res = 1;
  /*verification de chaque ligne*/
  while(i<9 && res==1)
  {
      res = verif_ligne(grille,horiz ,i);
      i++;
  }
  i = 0;
  horiz=0;
  /*verification de chaque colonne*/
  while(i<9 && res==1)
  {
      res = verif_ligne(grille,horiz ,i);
      i++;
  }
  /*verification de chaque zone*/
  i = 0;
  while(i<3 && res ==1)
  {
      while(j<3 && res==1)
      {
          res=verif_region(grille,i ,j);
          j++;
      }
      i++;
      j=0;
   }
   return(res);
}



/*----------------------------------------------------------------------*/
/*Question bonus                                                        */
/*la reecriture des elements genere a la creation de la grille          */
/*Pour y remedier: une matrice N*N si grille[i][j] est un elt reserve   */
/*alors reservation[i][j]=1 0 sinon                                     */
/*la modification des fonctions saisies est en commentaire              */
/*----------------------------------------------------------------------*/
