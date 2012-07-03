
%option yylineno

%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "y.tab.h"

#include "files.h"
/*------------------------------------------------------------------ */
/*  Inclusion du fichier contenant la definition du tableau pour la
   definition des la syntaxe des mots cles du langage. On peut ainsi
   gerer differents langages sources, comme par exemple le francais
   (synfr.h) et l'anglais (syngb.h).                                  */

#include "synfr.h"

/* Definition d'une constante pour valider ou inhiber les ecritures
  des lexemes reconnus dans un fichier d'extension ".fbll"             */
#undef DEBUG_L
#define DEBUG_L


/* ------------------------------------------------------------------ */
/* Definition des prototypes de quelques methodes utiles.             */
int ChercheMotRes(char *);
extern int ChercheIdent(char *);
extern char * tab_symb[];


%}

/* ------------------------------------------------------------------ */
/*  Description des caracteres constituant un programme               */
delim         [ \t\n]
blanc         {delim}+
lettre        [a-zA-Z]
chiffre       [0-9]
symbole       {lettre}|{chiffre}|"_"
ident         {lettre}{symbole}* 
entier        {chiffre}+
BadId         {entier}{ident}
comm           \{[^\}]*\}
dbquote        \"\"
str            \"([^\n\"]|{dbquote})*\"
autre         .

%%
{blanc}       ;

{ident}       { int i,j;
                i=ChercheMotRes(yytext);
                if (i==IDENT) {
                  j=ChercheIdent(yytext);
                  yylval.no_ident=j;
                 }
                 #ifdef DEBUG_L
                   if (i==IDENT)
                     fprintf(lexi,"AL ident  : %i %s\n",j,tab_symb[j]);
                   else
                      fprintf(lexi,"AL motcle : %i\n",i);
                 #endif
                return i;
              }


"<="              { return LE; }
">="          { return GE; }
"<>"          { return NE; }
":="          { return AFFECT; }


"-"           |
"+"           |
"*"           |
"/"           |
"="           |
"<"           |
">"           |
"("           |
")"           |
"["           |
"]"           |
"."           |
","           |
";"           |
":"           |
"@"           |
"^"           {
                #ifdef DEBUG_L
                   fprintf(lexi,"AL symb   : %c\n",yytext[0]); 
                #endif
                return yytext[0]; 
              }


{entier}      {
               yylval.entier = atol(yytext);
               #ifdef DEBUG_L
                 fprintf(lexi,"AL entier : %s\n",yytext);
               #endif
               return CSTE_ENTIERE;
              }



{comm}        { 
               #ifdef DEBUG_L
                 fprintf(lexi,"Commentaire : %s\nFin du commentaire\n",yytext);
               #endif
              }

{str}       { 
              #ifdef DEBUG_L
                 fprintf(lexi,"chaine de car : %s\n", yytext);
              #endif
                 yylval.chaine = strdup(yytext); /* On duplique la chaine */
                 return CSTE_CHAINE; } 



{autre}|{BadId}  {
            fprintf(stderr, "Ligne %d : motif illegal %s, 1er car (ASCII = %d)\n",
                     yylineno, yytext, (int)yytext[0]);
            //exit(1);
          }


%%

/* ------------------------------------------------------------------ */
/* Cherche si mot est un mot reserve.                                 
   Si c'est le cas, retourne son unite lexicale.                       
   Sinon retourne IDENT.
                         */
int ChercheMotRes(char *mot) {
   int i = 0, trouve = 0;

   while (!trouve && MotsRes[i].nom)
      trouve = !strcasecmp(MotsRes[i++].nom, mot);
   return (MotsRes[trouve?--i:i].unitlex);
}

