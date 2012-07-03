/**
 * \file graphisme.h
 * \brief version 1.0 des fonctions graphique du jeu
 * \author Maxime Escourbiac 
 * \version 1.0
 * \date 14 juin 2010
 *
 */

 #ifndef __GRAPHISME_H__
 #define __GRAPHISME_H__
 
 #include "core.h"

/**
 * \fn int transpix_1D(int x, int y)
 * \brief Fonction qui convertit la position en pixel en 1 dimension 
 * \param x position horizontale du curseur
 * \param y position verticale du curseur
 * \return z indice du tableau correpondant a la position du curseur
*/
  
int transpix_1D(int ,int);

/**
 * \fn void affich_score(var_game_t * var, int cpu)
 * \brief Fonction qui met a jour le score 
 * \param var structure contenant les variables du jeu
 * \param cpu variable de maj du score 1: si score adverse 0:sinon
 *
*/
 
void affich_score(var_game_t *, int );

/**
 * \fn void message_box(var_game_t * var, char * chaine)
 * \brief Fonction qui met a jour l'affichage de la message box 
 * \param var structure contenant les variables du jeu
 * \param chaine message ecrit sur la box
 *
*/

void message_box(var_game_t *, char *);

/**
 * \fn char * read_adress(var_game_t * var)
 * \brief Fonction qui lit a l'ecran l'adress ip du serveur local
 * \param var structure contenant les variables du jeu
 * \return adresse_ip chaine de caractere contenant l'adresse ip
 *
 */

char * read_adress(var_game_t * );

/**
 * \fn void sound_enable(var_game_t * var)
 * \brief fonction qui met/enleve le son du jeu
 * \param var structure de variables du jeu
 *
*/

void sound_enable(var_game_t * );

/**
 * \fn int conv_placement(int x, int y)
 * \brief Fonction qui convertit la position en pixel en 1 dimension 
 * \param x position horizontale du curseur
 * \param y position verticale du curseur
 * \return z indice du tableau correpondant a la position du curseur
*/
 
int conv_placement(int , int );

#endif