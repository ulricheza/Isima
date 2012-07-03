/*----------------------------------------------*/
/*Tp4: etude de la bibliotheque math.h          */
/*                                              */
/*lecture et calcul d'expression mathematiques  */
/*----------------------------------------------*/
/*utilisation de pointeur de fonction           */
/*et syntaxe du switch                          */
/*----------------------------------------------*/

/*partie 3*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*definition de la liste chainée des expressions*/

typedef struct expr 
{
  double evaluation;
  int id;
  struct expr * suivant ;
}expr_t;

/*definition de la liste chainée des operande  */
typedef struct ope
{
  int id;
  struct ope * suivant ; 
}ope_t;

/*declaration des fonctions */
void lecture( char * chaine, expr_t * teteexpr, ope_t  * teteop);
int identification_op(char op);
int identification_expr(char * fonc);
int test_expr(expr_t * tete);
int test_ope(ope_t * tete);
void eval_tot(expr_t * tete);
void calcul_prio(expr_t * tete , ope_t * head);
void calcul_final(expr_t * tete , ope_t * head);

int main(int argc, char * argv[])
{
   double resultat;
   char chaine[80];
   expr_t * teteexpr = NULL;
   ope_t  * teteop = NULL;
   teteexpr = (expr_t *)malloc(sizeof(expr_t));
   teteop   = (ope_t *)malloc(sizeof(ope_t));
   printf("saisie de la chaine à evaluer\n");
   fgets(chaine,79,stdin);
   lecture(chaine,teteexpr,teteop);
   if( test_expr(teteexpr)== 0 || test_ope(teteop) == 0)
   {
      printf("erreur de saisie \n");
      exit(EXIT_FAILURE);
   }
   eval_tot(teteexpr);
   calcul_prio(teteexpr, teteop);
   calcul_final(teteexpr, teteop);
   printf("resultat == %f \n",teteexpr->suivant->evaluation);
   return(EXIT_SUCCESS);  
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

void eval_tot(expr_t * tete)
{
   int i = 1;
   double temp;
   expr_t * courant = tete -> suivant;
   while(courant != NULL)
   {
      printf(" rentrez l'element %d \n",i++);
      scanf("%lf",&temp);
      courant -> evaluation = eval(temp,courant->id);
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
