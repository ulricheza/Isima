/**
 * \file file.h 
 * \brief Programme de gestion de files
 * \author Maxime ESCOURBIAC Sebastien SAINT_MARTIN
 * \version 1.0
 * \date Vendredi 19 mars 2010
 *
 * library de gestion de files
 */

 #ifndef __FILE_H__
 #define __FILE_H__

 #include <stdio.h>
 #include <stdlib.h>

 #define type_t int 


/**
*\struct file_t
*\brief structure d'en-tete de file
*
*/

typedef struct file
{
   int taille_max;
   int cpt;
   int deb;
   int fin;
   type_t * tableau;
}file_t;

/**
 * \fn file_t * init_file(int taille)
 * \brief fonction d'initialisation de la pile
 * \param taille entier qui definit la taille max de la pile
 * \return fifo pointeur sur la file qui vient d'etre cree
 *
 * algo de principe:
 *    allocation de la structure de file
 *    si non nul
 *       init valeurs taille_max,cpt,deb,fin
 *       allocation du tableau d'entier
 *       si tableau == NULL
 *          on libere la structure
 *       fsi
 *    fsi
 */

file_t * init_file(int );

/**
 * \fn int sommet_file(file_t * fifo,type_t * valeur)
 * \brief renvoie la valeur de sommet sans la supprimer
 * \param fifo file ou on va chercher la valeur
 * \param valeur pointeur sur la valeur ou on va mettre la valeur du sommet    
 * \return realise booleen pour savoir si ca a rendu la valeur du sommet
 *
 * algo de principe:
 *    si file non vide
 *       affection de la valeur a defiler dans valeur
 *       realise == VRAI
 *    fsi
*/   

int sommet_file(file_t * ,type_t * );

/**
 * \fn void detruire_file(file_t * fifo)
 * \brief libere une file ainsi que son contenu
 * \param fifo file a detuire
 *
 * algo de principe:
 *    liberation du tableau d'entier
 *    liberation de la structure file
 */
 
void detruire_file(file_t *);


/**
 * \fn int pleine_file(file_t * fifo)
 * \brief teste si une file est pleine
 * \param fifo file a tester
 * \return 1 si pleine 0 sinon
 *
 * algo de principe:
 *    return(fifo->cpt == (fifo->taille_max))
*/
 
int pleine_file(file_t *);

/**
 * \fn int vide_file(file_t * fifo)
 * \brief teste si une file est vide
 * \param fifo file a tester
 * \return 1 si vide 0 sinon
 *
 * algo de principe:
 *    return(fifo->rang == -1)
*/

int vide_file(file_t *);

/**
 * \fn int enfiler(file_t * fifo, type_t valeur)
 * \brief fonction d'enfilage d'une valeur
 * \param fifo file ou on va enfiler
 * \param valeur valeur que l'on veut enpiler
 * \return realise boolen pour savoir si on a enfiler
 * 
 * algo de principe:
 *   si file non pleine
 *      MAJ cpt,fin
 *      rajout de la valeur dans le tableau
 *   fsi
 *   retourner realise
 *
 */

 int enfiler(file_t *, type_t);

/**
 * \fn int defiler(file_t * fifo, type_t * valeur)
 * \brief fonction de defilage d'une valeur
 * \param fifo file ou on va defiler
 * \param valeur pointeur sur valeur ou on va depiler
 * \return realise boolen pour savoir si on a defiler
 * 
 * algo de principe:
 *   si file non vide
 *      MAJ cpt,fin
 *      recuperation de la valeur dans le tableau
 *   fsi
 *   retourner realise
 *
 */
 int defiler(file_t * , type_t *);


#endif
