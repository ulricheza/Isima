/**
 * \file tp3.h
 * \brief Programme de gestion d'arbres generaux
 * \author Maxime ESCOURBIAC Sebastien SAINT_MARTIN
 * \version 1.0
 * \date Mercredi 10 mars 2010
 *
 *  Programme qui gere la creation d'arbres generaux
 *
 */

#include "pile.h"


/**
*\struct cellule_t
*\brief structure d'une cellule de l'arbre
*
*/ 

typedef struct cellule
{
   char val;
   struct cellule * lv;
   struct cellule * lh;
}cellule_t;

/**
 * \fn void clean();
 * \brief fonction qui purge le stdin
 *
 */

void clean();

/**
 * \fn int creation_arbre(cellule_t ** tete, FILE * fic);
 * \brief cree un arbre general a partir d'un fichier passe en parametre
 * \param tete pointeur sur le pointeur de tete de l'arbre
 * \param fic fichier de lecture des donnees de l arborescence
 * \return erreur booleen pour savoir si l arbre a ete cree sans probleme
 *
 * algo de principe:
 *   init pile
 *   cour = tete
 *   Si pile != NULL alors
 *      lire rest
 *      Tant que non fin faire
 *         Si rest == 0 alors
 *            Si pile vide alors
 *               fin = 1;
 *            Sinon
 *               depiler rest;
 *               depiler cour;
 *               cour = cour->lh;
 *            Fsi;
 *         Sinon
 *            rest--;
 *            new = alloc(3);
 *            lecture valeur
 *            *cour = new;
 *            empiler cour;
 *            empiler rest;
 *            cour = &new->lv;
 *            lire rest;
 *         Fsi;
 *      Fait
 *      detruire pile;
 *   Fsi;
*/

int creation_arbre(cellule_t ** , FILE *);


/**
 * \fn void affic_post(cellule_t * tete);
 * \brief affiche l'ordre post-fixee de l'arbre dont la tete est passee en parametre
 * \param tete pointeur de tete de l'arbre
 *
 * algo de principe:
 *   init pile;
 *   cour = tete;
 *   Si pile != NULL alors
 *      Tant que pile non vide ou cour!=NULL faire
 *         epiler cour;
 *         cour = cour->lv;
 *         Tant que cour==NULL et pile non vide faire
 *            depiler cour;
 *            afficher cour->val;
 *            cour=cour->lh;
 *         Fait
 *      Fait
 *      Detruire pile
 *   Fsi
 */

void affic_post(cellule_t * );

/**
 * \fn cellule_t * rech_elt(cellule_t * tete,char v,pile_t * pile)
 * \brief recherche de cellule dans l'arbre de valeur v
 * \param tete pointeur de tete de l'arbre
 * \param v valeur que l'on cherche
 * \param pile pile que l'on va utiliser pour la fonction
 *
 * algo de principe:
 *   cour = tete;
 *   fin = 0;
 *   Si pile != NULL alors
 *      Tant que pile (non vide ou cour!=NULL) et fin == 0 faire
 *         epiler cour;
 *         afficher cour->val;
 *         Si cour->val == v alors
 *            fin = 1;
 *         fsi;
 *         cour = cour->lv;
 *         Tant que cour==NULL et pile non vide faire
 *            depiler cour;
 *            cour=cour->lh;
 *         Fait
 *      Fait
 *   Fsi
 */

cellule_t * rech_elt(cellule_t * ,char, pile_t *);

/**
 * \fn inser_fils(cellule_t * tete , char v , char w );
 * \brief insertion d'un fils de valeur w a un pere de valeur v
 * \param tete pointeur de tete de l'arbre
 * \param v valeur du pere
 * \param w valeur du fils que l'on va inserer
 *
 * algo de principe:
 * init pile
 * Si pile == NULL
 *    exit(EXIT_FAILLURE)
 * fsi
 * si pere trouve alors
 *   tant que cour != null et alors cour->valeur < w faire
 *      prec = &(cour->lh)
 *      cour = cour ->lh
 *   fait
 *   new = alloc(cellule_t);
 *   si new != NULL alors 
 *      new->lh = *prec
 *      *prec = new
 *   fsi
 *   detruire pile
 * fsi
 *
 */
 
void inser_fils(cellule_t * , char , char );

/**
 * \fn void affic_pere(cellule_t * tete)
 * \brief affiche les peres d'une valeur cherchee
 * \param tete pointeur de tete de l'arbre
 *
 * Algo de principe:
 *   Init pile;
 *   Si pile != NULL alors
 *      demande valeur a chercher
 *      Si valeur trouve alors
 *         Tant que pile non vide faire
 *            depiler valeur
 *            afficher valeur
 *         fait
 *      Sinon
 *         afficher valeur non trouve
 *      fsi
 *   fsi
 *   detruire pile
 */

void affic_pere(cellule_t * );
