#include <stdio.h>

/*initiation au C */
/* tableaux et fonctions!!!*/



int tab[50];


/*declaration des fonctions*/
void affichage ();
int min ();
int max();
float moyenne();

int main()
{
   int mini;
   int maxi;
   float moye;
   int i;
   for(i=0;i<50;i++) 
   {
      tab[i]=100;
   }
   printf("on va ajouter l'indice a tous les elements d'indice pair\n");
   
   for(i=0;i<50;i=i+2)
   {
      tab[i] = tab[i] + i;
   }
   printf("on va enlever l'indice a tous les elements d'indice impair\n");
   for(i=1;i<50;i=i+2)
   {
      tab[i] = tab[i] - i;
   }
   affichage();
   mini = min();
   maxi = max();
   moye = moyenne();
   printf(" min == %d , max ==%d , moy ==%f\n",mini,maxi,moye);
}

void affichage ()
{
  int i;
  for(i=0;i<50;i++)
  {
     printf("tab[%d]==%d\n",i,tab[i]);
  }
}

int min ()
{
   int i = 0 ;
   int mini = tab[0];
   for(i=0;i<50;i++)
   {
      if(tab[i] < mini) mini = tab[i];
   }
   return(mini);
}

int max()
{
   int i = 0 ;
   int maxi = tab[0];
   for(i=0;i<50;i++)
   {
      if(tab[i] > maxi) maxi = tab[i];
   }
   return(maxi);
}

float moyenne ()
{
   float somme = 0;
   int i = 0;
   for(i;i<50;i++) somme = somme + (float)tab[i];
   return(somme / 50);
}
