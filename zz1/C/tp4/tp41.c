/*----------------------------------------------*/
/*Tp4: etude de la bibliotheque math.h          */
/*                                              */
/*lecture et calcul d'expression mathematiques  */
/*----------------------------------------------*/
/*utilisation de pointeur de fonction           */
/*et syntaxe du switch                          */
/*----------------------------------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h> /*indispensable sur un autre compilateur*/

int identification(char * fonc);
double eval(double a, int id);
void calcul(double a, double b , double delta , int id);

int main(int argc,char * argv[])
{
   int res;
   char chaine[10];
   double a,b,delta;
   scanf("%s",chaine);
   res = identification(chaine);
   /*seulement si la fonction est reconnue*/
   if(res!=-1)
   {
      printf("intervalle min\n");
      scanf("%lf",&a);
      printf("intervalle max\n");
      scanf("%lf",&b);
      printf("delta\n");
      scanf("%lf",&delta);
      calcul(a,b,delta,res);
   }
   else printf("erreur lors de la saisie de la fonction \n");
   return(EXIT_SUCCESS);
}

int identification(char * fonc)
{
    int i = 0;
    char tab[][7] = {"x","sin(x)","cos(x)","log(x)","exp(x)"};
    while(strcmp(fonc,tab[i])!=0 && i<5)
    {   
       i++;
    }
    if(i==5)i=-1;
    return i ;
}

/*--------------------------------------*/
/*fonction qui evalue la valeur d'une   */
/*fonction identifie par un entier donne*/
/*en parametre                          */
/*--------------------------------------*/

double eval(double a, int id)
{   
   double temp = a;   
   double(*fonction) (double); /*l'utilisation d'un pointeur de fonction est*/
   if(id !=0)                  /*interresante pour un tel cas               */ 
   {
      switch (id)
      {
         case 1 : fonction = sin ;
	          break;
         case 2 : fonction = cos ;
	          break;
         case 3 : fonction = log10 ;
	          break;
         case 4 : fonction = exp ;
	          break;
         
      }
      temp = fonction(a);
   }
   return temp;
} 

/*----------------------------------------*/
/*fonction qui evalue les valeurs d'une   */
/*fonction identifie par un entier donne  */
/*en parametre dans un intervalle [a,b]   */
/*----------------------------------------*/


void calcul(double a, double b , double delta , int id)
{
   while(a<b)
   {
       printf("f(%f)=%f \n",a,eval(a,id));
       a = a + delta;
   }
}
