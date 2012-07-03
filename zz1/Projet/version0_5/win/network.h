/**
 * \file network.h
 * \brief rassemblement des fonctions reseaux
 * \author Maxime Escourbiac 
 * \version 0.1
 * \date Jeudi 1 avril
 *
 *
 */
 
 #ifndef __NETWORK_H__
 #define __NETWORK_H__

 #include "core.h"

/**
 * \fn void * accept_connect(var_game_t * var )
 * \brief fonction qui attend la connection au serveur
 * \param var pointeur sur la structure des variables du jeu
 * \return NULL
*/

void * accept_connect(var_game_t * );

/**
 * \fn void * recept_rdy(var_game_t * var)
 * \brief permet de savoir si le joueur adverse a placer ses bateaux
 * \param var pointeur sur la structure des variables du jeu
 * \return NULL
 *
 * Cette fonction a pour but d'etre lancee via un threads afin de pas bloquer
 * le programme a la reception du jeton rdy
 *
 */

void * recept_rdy(var_game_t *);

/**
 * \fn void envoi_coord(var_game_t * var)
 * \brief permet de connaitre les coordonnees de tir de l'autre utilisateur
 * \param var pointeur sur la structure des variables du jeu
 *
 */


void envoi_coord(var_game_t *);

/**
 * \fn void * recept_coord(void * var)
 * \brief fonction qui recoit une coordonne, modifie les matrices et envoie une reponse au tir
 * \param var pointeur sur le tableau
 * \return NULL
*/

void * recept_coord(var_game_t * );

/**
 * \fn void * recept_rdy(var_game_t * var)
 * \brief permet de savoir si le joueur adverse a placer ses bateaux
 * \param var pointeur sur la structure des variables du jeu
 * \return NULL
 *
 * Cette fonction a pour but d'etre lancee via un threads afin de pas bloquer
 * le programme a la reception du jeton rdy
 *
 */

void * recept_rdy(var_game_t *);

/**
 * \fn void * recept_rep(var_game_t * var)
 * \brief fonction qui recoit la reponse du tir precedent et qui modifie la matrice mer corespondante
 * \param var pointeur sur la structure des variables du jeu
 * \return NULL
*/


void * recept_rep(var_game_t *);

/**
 * \fn void close_sock(var_game_t *, int serveur)
 * \brief fonction qui ferme la socket de transmission
 * \param var pointeur sur la structure des valeurs du jeu
 * \param serveur entier pour definir si on ferme cote serveur ou client 0: client 1: serveur
*/

void close_sock(var_game_t *, int);

#endif




