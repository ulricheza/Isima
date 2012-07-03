/*----------------------------------------------*/
/*Tp4: etude de la bibliotheque math.h          */
/*                                              */
/*lecture et calcul d'expression mathematiques  */
/*----------------------------------------------*/
/*utilisation de pointeur de fonction           */
/*et syntaxe du switch                          */
/*----------------------------------------------*/

/*partie 2 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int identification_expr(char * fonc);
int identification_op(char op);
double eval(double a, int id);
double eval_op (double a, double b , int idop);

/* realisation des operations de base / * - +  sur deux expressions*/


int main( int argc, char * argv[])
{
  char temp[60];
  char expr1[10];
  char expr2[10];
  char op;
  int bool,id1,idop,id2;
  double a,b,delta;
  printf("Veuillez rentrer le type de l'expression \n"); /*initialisation et validation de la chaine*/
  fgets(temp,78,stdin);
  sscanf(temp,"%s %c %s",expr1,&op,expr2);
  id1 = identification_expr(expr1);
  id2 = identification_expr(expr2);
  idop = identification_op(op);
  
  if( id1 == -1 ||id2 == -1 || idop ==-1) /*test si l'expression est bonne*/
  {
     printf("erreur dans la saisie \n");
     exit(EXIT_FAILURE);
  }
  printf("choix?\n");                  /*pseudo-menu*/
  printf("1°/ une ligne \n");
  printf("2°/ une variation \n");
  scanf("%d",&bool);
  if(bool == 1)                      /*affichage sur une ligne*/
  {
     printf("1er valeur??\n");
     scanf("%lf",&a);
     printf("2ieme valeur??\n");
     scanf("%lf",&b);
     a = eval(a,id1);
     b = eval(b,id2);
     printf("valeur finale ::: %s = %f \n",temp,eval_op(a,b,idop));
  }
  else                             /*affichage sur un intervale*/
  {
    printf("valeur min?\n");
    scanf("%lf",&a);
    printf("valeur max?\n");
    scanf("%lf",&b);
    printf("delta?\n");
    scanf("%lf",&delta);
    while(a < b)
    {
       printf("pour x = %f ::: %s = %f \n",a,temp,eval_op(eval(a,id1),eval(a,id2),idop));
       a = a + delta;
    }
  }
  return(EXIT_SUCCESS);
}

int identification_expr(char * fonc)
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

/*fonction qui permet d'identifier l'operateur*/
int identification_op(char op)
{
    int i;
    switch (op)
    {
      case '/' : i = 1;
                 break;
      case '*' : i = 2;
                 break;
      case '-' : i = 3;
                 break;
      case '+' : i = 4;
                 break;
      default  : i = -1;
    }
    return i ;
}

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

/*evaluation de l'expression*/
/*ATTENTION : a et b sont pas evalué!!!*/
/*a effectuer lors de l'appel de la fonction avec eval*/
double eval_op (double a, double b , int idop)
{
  double res;
  switch (idop)
  {
     case 1 : res = a / b;
                break;
     case 2 : res = a * b;
                break;
     case 3 : res = a - b;
                break;
     case 4 : res = a + b;
                break;
  }
  return(res);
}
