/**
 * \file news.h 
 * \brief Programme de gestion de news date a partir d'un fichier
 * \author Maxime ESCOURBIAC Sebastien SAINT_MARTIN
 * \version 1.0
 * \date Mercredi 10 mars 2010
 *  
 *  Programme qui gere un systeme de news avec un systeme de date 
 *  Les news seront ecrites dans un fichier qui sera passer en parametre
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

 /**
 * \struct news_t
 * \brief Objet chaine de caracteres.
 *
 * News_t est un petit objet de gestion de chaines de news. 
 * 
 */

typedef struct news
{
   int deb;
   int fin;
   char * mess;
   struct news * suivant;
}news_t;


/**
  * \fn void lect_fichier (FILE * fic,int * deb, int * fin,char * mess)
  * \brief fonction de lecture de message dans un fichier
  * \param fic pointeur sur le fichier a lire
  * \param deb pointeur sur la date de debut de validite du message
  * \param fin pointeur sur la date de fin de validite du message
  * \param mess pointeur sur le message
  *
  * Algo de principe:
        lecture de la date de debut de validite dans FIC
        lecture de la date de fin de validite dans FIC
        lecture du message dans FIC
  *
*/

void lect_fichier (FILE *, int *, int *, char ** );

/**
  * \fn news_t * creation_cell(int  deb, int fin,char * mess)
  * \brief creation de la cellule news avec les parametres lues precedemments
  * \param deb  date de debut de validite du message
  * \param fin  date de fin de validite du message
  * \param mess pointeur sur le message.
  *
  * Algo de principe:
         allocation de la cellule
         si bien alloue
            mettre en place les valeurs lues precedemment
         sinon
            signifiez que la cellule a pas pu etre alloue
         fsi
         retourner(cellule)
  *
*/
news_t * creation_cell(int , int , char *);


/**
 * \fn int rech_prec (int deb, news_t ** tete, news_t ** prec)
  * \brief fonction de recherche du precedent de la cellule a inserer
  * \param deb date de debut de validite du message
  * \param tete pointeur sur la tete de la liste
  * \param prec pointeur sur la cellule precedente
  * \return existe booleen d existence de valeur
  *
  * Algo de principe:
         tant que non fin de liste et alors element non trouve faire
            parcourir la liste avec gestion d un precedent
         fait
         si liste entierement parcourue ou sinon element non trouvee alors
            non appartenance de l element a la liste 
         fsi
         retourner existe
  *
*/
int rech_prec(int, news_t ** ,news_t *** );

/**
  * \fn void insertion (news_t * cellule,news_t ** tete)
  * \brief fonction d insertion de la cellule
  * \param tete double pointeur sur la tete de liste
  * \param cellule pointeur sur la cellule a inserer
  *
  * Algo de principe:
         recherche du precedent
         faire pointer la cellule a inserer vers le suivant du precedent
         faire pointer le precedent vers la cellule a inserer
  *
*/

void insertion (news_t *, news_t **);

/**
 *\fn void affic_cell(news_t * cell)
 *\brief fonction d'affichage d'une cellule
 *\param cell pointeur sur la liste a afficher
 *
*/

 void affic_cell(news_t *);

/**
 *\fn void affic(news_t * tete)
 *\brief fonction d'affichage d'une liste chainee
 *\param tete pointeur de tete sur la liste chainee
 *
 * Algo de principe:
 * Recherche de prec
 * insertion de la cellule apres le prec trouve
*/


void affic(news_t *);

/**
 *\fn void erase_all(news_t * tete)
 *\brief fonction de liberation d'une liste chainee
 *\param tete pointeur de tete sur la liste chainee
 *
 * * Algo de principe
 * Tant que non fin de liste faire
 *    afficher les informations de la cellule
 *    passer a la cellule suivante
 * fait
*/

void erase_all(news_t * );

/**
 *\fn void sauvegarde_fic(news_t * tete)
 *\brief fonction de sauvegarde de la structure dans un fichier
 *\param tete pointeur de tete sur la liste chainee
 *
 *algo de principe:
 * Demande du nom pour la sauvegarde de la structure
 * ouverture du fichier en ecriture
 * tant que non fin de liste
 *    genererer la phrase de meme structure que dans le fichier initial
 *    inserer cette phrase dans le fichier ouvert en ecriture
 *    passer a la cellule suivante
 * fin tant que
 * fermer le fichier
 * fin fonction 
*/

void sauvegarde_fic(news_t *);

/**
 *\fn void affic_ajour(news_t * tete)
 *\brief fonction d'affichage des news en cours de validité
 *\param tete pointeur de tete sur la liste chainee
 *
 * Algo de principe:
 * appel de la fonction date_act
 * tant que non fin de liste && date debut < date_actuelle faire
 *    Si date fin > date_actuelle alors
 *       afficher le message associe a la structure
 *    fsi
 *    passer a la cellule suivante
 * fait
 * fin fonction
*/

void affic_ajour(news_t *);

/**
 *\fn int date_act()
 *\brief fonction de recuperation de la date systeme
 *\return date entier representant la date aaaammjj
 *
 * Algo de principe:
 * recuperation de la date systeme
 * convertion au format aaaammdd
*/

int date_act();


/**
 *\fn void erase_obsolete(news_t ** tete)
 *\brief fonction de suppression des nexs qui ne sont plus d'actualite
 *\param tete pointeur de pointeur de la tete sur la liste chainee
 *
 * Algo de principe:
 * appel de la fonction date_act
 * tant que non fin de liste && date debut < date_actuelle faire
 *    Si date fin < date_actuelle alors
 *       supprimer la news
 *    fsi
 *    passer a la cellule suivante
 * fait
 * fin fonction
*/
void erase_obsolete(news_t **);

/**
 *\fn void suppr_date(news_t * cour, news_t ** prec)
 *\brief fonction de suppression d'un bloc de news
 *\param cour pointeur sur la news a supprimer
 *\param prec pointeur sur le pointeur suivant du precedent 
 *
*/
void suppr_date(news_t *, news_t **);

/**
 *\fn void modif_date_deb(news_t ** tete, int date_deb_ancien, int dat_deb_new)
 *\brief fonction de de modification de date de debut
 *\param tete pointeur sur le pointeur de tete de la liste chainee
 *\param date_deb_ancien ancienne date du message
 *\param date_deb_new nouvelle date du message
 *
 * algo de principe:
 * Si le message a la date date_deb_ancien existe alors
 *    tant que le message est a la date demande faire
 *       supprimer virtuellement la news
 *       modifier la date
 *       inserer de nouveau
 *    fait
 *Sinon
 *   le message n'existe pas
*/
void modif_date_deb(news_t **, int, int);

/**
 *\fn void affic_motif(news_t * tete)
 *\brief affiche les news qui possede une chaine de caractere donnee dans leur message
 *\param tete pointeur sur le pointeur de tete de liste chainee
 *
 * algo de principe:
 * lecture du motif
 * Tant que non fin de liste faire 
 *    si motif trouve alors
 *       afficher le message 
 *    fsi
 *    passer a la cellule suivante
 * fait
 *
 */

void affic_motif(news_t *);