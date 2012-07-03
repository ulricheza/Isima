
#include <stdio.h>
#include "calcul.h"


void lecture( char * chaine, expr_t * teteexpr, ope_t  * teteop);
int identification_op(char op);
int identification_expr(char * fonc);
int test_expr(expr_t * tete);
int test_ope(ope_t * tete);
void eval_tot(double val, expr_t * tete);
void calcul_prio(expr_t * tete , ope_t * head);
void calcul_final(expr_t * tete , ope_t * head);



/**
 *\fn calcul(char * expr, int xmax, int ymax, int * tab)
 *\brief calcule les points a afficher
 *
 *\param expr
 *\param xmax
 *\param ymax
 *\param tab
 *\return 
 */

void calcul(char * expr, double xmax, double ymax, int * tab)
{
   double pas;
   double temp;
   int i;
   expr_t * teteexpr = NULL;
   ope_t  * teteop = NULL;

   teteexpr = (expr_t *)malloc(sizeof(expr_t));
   teteop   = (ope_t *)malloc(sizeof(ope_t));

   pas = xmax * 2.0 /400.0;
   
   for(i=0;i<400;i++)
   {
      lecture(expr,teteexpr,teteop);
      if( test_expr(teteexpr)== 0 || test_ope(teteop) == 0)
      {
         printf("erreur de saisie \n");
         exit(EXIT_FAILURE);
      }
      temp = -ymax + (double)i*pas, 
      eval_tot(temp,teteexpr);
      calcul_prio(teteexpr, teteop);
      calcul_final(teteexpr, teteop);
      temp = teteexpr->suivant->evaluation / ymax * 200.0;
      tab[i] = (int)temp;
      tab[i] = -(tab[i] - 200);
   }
      
      
  
}

void lecture( char * chaine, expr_t * teteexpr, ope_t  * teteop)
{
  int bool = 0;
  char temp[10];
  expr_t * cour1 = teteexpr;
  expr_t * nouv1;
  ope_t * cour2  = teteop ;
  ope_t * nouv2;
  FILE * fichier;
  fichier = fopen("temp.txt","w+");
  fprintf(fichier,"%s",chaine);
  fclose(fichier);
  fichier = fopen("temp.txt","r");
  while(!feof(fichier))
  {
    fscanf(fichier,"%s",temp);
    if(bool == 1)
    {
      /*alors on traite un operateur*/
        nouv2 = (ope_t *)malloc(sizeof(ope_t));
        cour2 -> suivant = nouv2;
        cour2= nouv2;
        cour2 -> id = identification_op(temp[0]);
        cour2 -> suivant = NULL;
        bool = 0;
    }
    else
    {
      /*alors on traite un expression*/


        nouv1 = (expr_t *)malloc(sizeof(expr_t));
        cour1 -> suivant = nouv1;
	cour1 = nouv1;
	cour1 -> id = identification_expr(temp);
        cour1 -> suivant = NULL;
	bool = 1;
    }
  }   
  system("rm temp.txt");
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

/*fonction qui permet d'identifier une expression*/

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

/*fonction de test de la liste chainee des expressions*/
int test_expr(expr_t * tete)
{
   int res = 1;
   expr_t * courant = tete -> suivant;
   while(courant != NULL)
   {
      if(courant -> id == -1)
	res = 0;
      courant = courant -> suivant;
   }
   return res;
}

/*fonction de test de la liste chainee des operandes*/
int test_ope(ope_t * tete)
{
   int res = 1;
   ope_t * courant = tete -> suivant;
   while(courant -> suivant != NULL) /*evite un begaiment*/
   {
      if(courant -> id == -1)
	res = 0;
      courant = courant -> suivant;
   }
   return res;
}

/*fonction qui evalue tous les elements*/

void eval_tot(double val, expr_t * tete)
{
   int i = 1;
   double temp;
   expr_t * courant = tete -> suivant;
   while(courant != NULL)
   {
      courant -> evaluation = eval(val,courant->id);
      courant = courant -> suivant ; 
   }
}

/*fonction qui effectue les calculs "prioritaire" */
void calcul_prio(expr_t * tete , ope_t * head)
{
   
   expr_t * cour1 = tete -> suivant;
   expr_t * suiv = cour1 -> suivant;
   ope_t  * cour2 = head -> suivant;
   ope_t * prec = head;
   

   while(suiv != NULL && cour2 != NULL)
   {
     
     if(cour2 -> id < 3)
     {
     /*operation prioritaire*/
        cour1 -> evaluation = eval_op (cour1 -> evaluation , suiv -> evaluation , cour2 -> id);
        cour1 -> suivant = suiv -> suivant;
        prec -> suivant = cour2 -> suivant;
        free(suiv);
        free(cour2);
        suiv = cour1 -> suivant;
        cour2 = prec-> suivant;
     }
     else
     {
        cour1 = cour1 -> suivant;
	suiv  = suiv -> suivant;
	cour2 = cour2 -> suivant;
	prec  = prec -> suivant;
     }
   }
}

/*fonction qui effectue le reste des calculs*/
void calcul_final(expr_t * tete , ope_t * head)
{
   
   expr_t * cour1 = tete -> suivant;
   expr_t * suiv = cour1 -> suivant;
   ope_t * cour2 = head -> suivant;
   while(suiv != NULL && cour2 != NULL)
   {
      cour1 -> evaluation = eval_op (cour1 -> evaluation , suiv -> evaluation , cour2 -> id);
      cour1 -> suivant = suiv -> suivant;
      head -> suivant = cour2 -> suivant;
      free(suiv);
      free(cour2);
      suiv = cour1 -> suivant;
      cour2 = head -> suivant;
   }
}
