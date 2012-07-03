/* ------------------------------------------------------------------- */
/*  table.c                                                            */
/*                                                                     */
/*  Fonctions utilisant la table des symboles                          */
/*                                                                     */
/*  Fabrice BARAY - ISIMA - 1996-1997                                  */
/* ------------------------------------------------------------------- */


#include "table.h"
#include <stdlib.h>
#include <string.h>

/* Fonction d'initialisation de la table des symboles */
void init_table() {
   int i;

   for(i=0;i<MAX_LEX;tab_symb[i++]=NULL);
}

/* ------------------------------------------------------------------- */
// fonction ChercheIdent() 
int ChercheIdent(char *mot) {
   int i=0;

   while (tab_symb[i]&&strcasecmp(tab_symb[i],mot)) i++;

   if (!tab_symb[i]) 
      tab_symb[i]=strdup(mot);
   return i;
}

