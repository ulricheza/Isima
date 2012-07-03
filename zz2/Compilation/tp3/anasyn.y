%{
#include <stdio.h>

#include "files.h"
#include "global.h"
/* Pour l'affichage du parcours des regles lors de l'analyse 
   syntaxique                                                */
#undef DEBUG_S
#define DEBUG_S

/* prototype de la fonction d'erreur */
void yyerror(char *);

extern int yylineno;

%}

%union {
   int   val;
   int   v;
}


%start S

%token <val> ENTIER

%type <v> E
%type <v> T
%type <v> F




%%
S : E
  {
    printf("valeur: %d\n",$1);
  };
E : E '+' T
  {
    $$ = $1 + $3;
    printf("+ ");
  } 
| E '-' T
  {
    $$ = $1 - $3;
    printf("- ");
  }
| T 
  {
    $$ = $1;  
  };

T : T '*' F 
  {
    $$ = $1 * $3;
    printf("* ");
  }
| T '/' F
  {
    $$ = $1 / $3;
  printf("/ ");
  }
| F
  {
    $$ = $1;
  };

F : ENTIER 
  {
    $$ = $1;
    printf("%d ",$1);
  }
| '(' E ')'
  {
    $$ = $2;
  };

%%

/* Affiche le message d'erreur msg                                   */
void yyerror(char *msg)
{
 if(!msg || *msg=='\0')
  fprintf(stderr, "Erreur ligne %d\n vers le lexeme : %s", yylineno, yytext);
 else
  fprintf(stderr, "Erreur ligne %d : %s vers le lexeme : %s\n", yylineno, msg, yytext);
}

