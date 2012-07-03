%{
#include <stdio.h>

#include "files.h"

#include "Bop.hpp"
#include "Expr.hpp"
#include "VisitorExprCalc.hpp"


extern Expr *racine;
/* Pour l'affichage du parcours des regles lors de l'analyse 
   syntaxique                                                */
#undef DEBUG_S
#define DEBUG_S

/* prototype de la fonction d'erreur */
void yyerror(char *);

extern int yylineno;
extern int yylex();
extern char * tab_symb[];

VisitorExprCalc * visitor = new VisitorExprCalc();

%}
%union {
   int   no_ident;
   int   val;
   /* valeur pour les non terminaux */
   class Expr    *e;
}


%start S



%token <no_ident> IDENT
%token <val> ENTIER
%token LET
%token IN
%token TEL
%token AFFECT
%token READ
%token WRITE

%type <e> E
%type <e> T
%type <e> F


%%
S : LI';'
{
  
};

E : E '+' T 
{  printf("+");
#ifdef DEBUG_S
		   fprintf(synt, "reduction r1\n");
		   fprintf(synt, "   creation noeud d'addition\n");
#endif
		   $$ = new ExprBop(yylineno, $1, plus, $3);
         } 
    |E '-' T 
     { printf("-");
#ifdef DEBUG_S
		   fprintf(synt, "reduction r2\n");
		   fprintf(synt, "   creation noeud de soustraction\n");
#endif
		   $$ = new ExprBop(yylineno, $1, minus, $3);
	 } 

	| T
	 {
#ifdef DEBUG_S
		   fprintf(synt, "reduction r3\n");
		   fprintf(synt, "   transfert du terme vers l'expression\n");
#endif
		   $$ = $1;
	 }
 ;
 

T : T '*' F 
     {printf("*");
#ifdef DEBUG_S
            fprintf(synt, "reduction r4\n");
		    fprintf(synt, "   creation noeud de multiplication\n");
#endif
			$$ = new ExprBop(yylineno, $1, mult, $3);
	 }
   |T '/' F 
        {printf("/");
#ifdef DEBUG_S
              fprintf(synt, "reduction r5\n");
			  fprintf(synt, "   creation noeud de division\n");
#endif
               $$ = new ExprBop(yylineno, $1, divi, $3);
         } 
   | F
  {
#ifdef DEBUG_S
     fprintf(synt, "reduction r6\n");
     fprintf(synt, "   transfert du facteur vers le terme\n");
#endif
     $$ = $1;
  } 
;


F : ENTIER 
	{printf(" %d ", $1);
#ifdef DEBUG_S
		  fprintf(synt, "reduction r7\n");
		  fprintf(synt, "   creation du noeud pour la valeur %d\n", $1);
#endif
		  $$ = new ExprN(yylineno, $1);
	}
 | IDENT 
	{printf(" %s ", tab_symb[$1]);
#ifdef DEBUG_S
		  fprintf(synt, "reduction r8\n");
		  fprintf(synt, "   creation du noeud pour l'ident nr %d, de nom : %s\n",$1, tab_symb[$1]);
		#endif
		  $$ = new ExprI(yylineno, $1);
	}
| '(' E ')'
	{
#ifdef DEBUG_S
		  fprintf(synt, "reduction r9\n");
		  fprintf(synt, "   transfert l'arbre expression sur facteur, sans parentheses\n");
#endif
		  $$ = $2;
	}
  | LET IDENT AFFECT E IN E TEL
  {
#ifdef DEBUG_S
    fprintf(synt, "reduction r10\n");
#endif
  $$ = new ExprAff(yylineno, $2,$4,$6);
  
  };

LI: I
  {
    
  }
  | LI ';' I
{
};
  
I: IDENT AFFECT E
{
    $3->Accepter(visitor);
    
    
}
  |WRITE '(' IDENT ')'
{
    printf("ident: %d\n",$3);
}
  |READ '(' IDENT ')'
{
    printf("Entrez une valeur pour %s \n",$3);
    scanf("%d",$3);
};


%%

/* Affiche le message d'erreur msg                                   */
void yyerror(char *msg)
{
 if(!msg || *msg=='\0')
  fprintf(stderr, "Erreur ligne %d\n", yylineno);
 else
  fprintf(stderr, "Erreur ligne %d : %s\n", yylineno, msg);
}

