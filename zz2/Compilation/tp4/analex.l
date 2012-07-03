
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
static int ChercheIdent(char *);


%}

/* ------------------------------------------------------------------ */
/*  Description des caracteres constituant une expression               */
delim         [ \t\n]
blanc         {delim}+
let           let
in            in
tel           tel
lettre        [a-zA-Z]
ident         [a-zA-Z][a-zA-Z0-9_]*
entier        [0-9]+
affect        ":="
read          read
write         write
autre         .

%%
{blanc}       ;
{entier}      { fprintf(lexi, "entier lu %s\n", yytext);
                yylval.val = atol(yytext);
                return ENTIER;
                                }
let          { return LET;}
in		       { return IN;}
tel           {return TEL;}
read          {return READ;}
write         {return WRITE;}
{affect}      {return AFFECT;}
{ident}       { int j;
                                j=ChercheIdent(yytext);
                                yylval.no_ident=j;
                                fprintf(lexi,"AL ident  : %i %s\n",j,tab_symb[j]);
         
                return IDENT; /* IDENT defini comme token ds anasyn.y*/
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
static int ChercheIdent(char *mot) {
   int i=0;

   while (tab_symb[i]&&strcasecmp(tab_symb[i],mot)) i++;

   if (!tab_symb[i]) 
      tab_symb[i]=strdup(mot);
   return i;
}

