
%option yylineno


%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "y.tab.h"

#include "files.h"
#include "global.h"

#undef DEBUG_L
#define DEBUG_L


/* ------------------------------------------------------------------ */
/* Definition des prototypes de quelques methodes utiles.             */
extern void yyerror(char *); /* Definie dans anasyn.y */

%}

/* ------------------------------------------------------------------ */
/*  Description des caracteres constituant une expression               */
delim         [ \t\n]
blanc         {delim}+
entier        [0-9]+

autre         .

%%
{blanc}       ;
{entier}      { fprintf(lexi, "entier lu %s\n", yytext);
                yylval.val = atol(yytext);
                return ENTIER;
                                }
"+"           |
"*"           |
"("           |
"-"           |
"/"           |
"="			  |
")"           { 
                fprintf(lexi, "Symbole lu : %c \n", yytext[0]);
                return yytext[0]; }
{autre}       {
               char msg[40];

               sprintf(msg, "Caractere illegal %c (ASCII = %d)", yytext[0], (int)yytext[0]);
               yyerror(msg);
               exit(1);
              }

%%


