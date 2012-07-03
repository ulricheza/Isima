/**
 * \file test.c

 * \brief fait un truc
 * \author ME
 * \version 0.1
 * \date 01-02-09
*/
/*declaration des bibliotheques*/

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* fin de declaration des bibliotheques*/

/*declaration de la structure*/
typedef struct cellule
{
    char * ligne;
    struct cellule * suivant;
}cellule_t; 
/*fin de declaration de la structure*/

/*declaration des fonctions*/
void adj_lch_fin(cellule_t ** tete, cellule_t ** queue); /*tete non fictive la classe =)*/
void affichage(cellule_t * tete);
/*fin de declaration des fonctions*/

/*commentaire a la viande*/
