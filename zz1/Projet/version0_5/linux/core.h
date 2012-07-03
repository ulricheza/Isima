/**
 * \file core.h
 * \brief rassemblement des fonctions developpees en 1er partie 
 * \author Maxime Escourbiac 
 * \version 1.0
 * \date Dimanche 7 mars 2010
 *
 * 
 */

#ifndef __CORE_H__
#define __CORE_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

#ifdef __WIN32__
    #include <winsock2.h>
    typedef int socklen_t;

#else

    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #define INVALID_SOCKET -1
    #define SOCKET_ERROR -1
    #define closesocket(s) close(s)
    typedef int SOCKET;
    typedef struct sockaddr_in SOCKADDR_IN;
    typedef struct sockaddr SOCKADDR;
#endif

/**
*\struct bateau_t
*\brief structure de modelisation de bateau
*
*/

typedef struct bateau {
   int vie;
   int taille;
   int x;
   int y;
   int sens;

}bateau_t;


/**
*\struct var_game_t
*\brief structure des variables du jeu
*
*/

typedef struct var_game
{
   int * mer_cible_hum;
   int * mer_home_hum;
   int * mer_cible_cpu;
   int * mer_home_cpu;
   bateau_t flotte_hum[5];
   bateau_t flotte_cpu[5];
   FILE * log_erreur;
   int remain_bat_cpu;
   int remain_bat_hum;
   int z;
   SOCKET sock_client;
   SOCKET sock_serveur;
   SOCKADDR_IN sin_client;
   SOCKADDR_IN sin_serveur;

}var_game_t;


 /**
 * \fn void placement_hum(var_game_t * )
 * \brief fonction de placement de bateau humain
 * \param var pointeur sur la structure des variables du jeu
 *
*/

void placement_hum(var_game_t * );

 /**
 * \fn void exit_err(var_game_t * )
 * \brief fonction de sortie du programme en cas d'erreur
 * \param var pointeur sur la structure des variables du jeu
 *
*/

void exit_err(var_game_t * );

 /**
 * \fn void init_fic_err(var_game_t * )
 * \brief fonction d'initialisation des differentes valeurs
 * \param var pointeur sur la structure de variables du jeu
*/


void init_fic_erreur(var_game_t *);

 /**
 * \fn void init_var(int cpu,var_game_t ** var)
 * \param cpu entier qui definit si on est en mode 1joueur
 * \param var adresse du pointeur sur la structure de variable du jeu
 * \brief fonction d'initialisation des differentes valeurs

*/

void init_var(int ,var_game_t ** );

 /**
 *\fn void placement_alea(var_game_t * var)
 *\brief fonction de placement aleatoire des bateau cpu
 *\param var pointeur sur la structure des variables du jeu
 *
*/

void placement_alea(var_game_t * );

 /**
 *\fn int choix_alea(int * permit, int max)
 *\brief fonction de choix aleatoire parmi les cases restantes
 *\param permit pointeur sur le tableau des cases possibles pour la tete
 *\param max nombre de cases encore possible
 *\return z coordonnes 1D de la tete choisie

*/

int choix_alea(int *,int );

 /**
 *\fn void suppr_point(int * permit, int * max, int x, int y) 
 *\brief fonction de suppression d'un point dans la matrice des possibles
 *\param permit pointeur sur le tableau des cases possibles pour la tete
 *\param max pointeur sur le nombre de cases possibles
 *\param x numero de lignes du point � supprimer 
 *\param y numero de colonnes du poitn a supprimer

*/

void suppr_point(int *, int *,int ,int );

 /**
 * \fn int placement_valide(int x, int y, int sens,int taille,var_game_t * var)
 * \brief verifie si le placement d'un bateau est valide
 * \param sens booleen sur le sens du bateau
 * \param x parametre sur la ligne
 * \param y parametre sur la colonne
 * \param var pointeur sur la structure de variable du jeu
 * \return valid booleen sur la valiite du bateau

*/


int placement_valide (int ,int ,int ,int ,var_game_t *);

 /**
 *\fn int trans2D_1D (int x, int y)
 *\brief transformation de coordonnes 2D vers 1D
 *\param x parametre sur la ligne 
 *\param y parametre sur la colonne
 *\return z coordonne 1D de la tete du bateau

*/

int trans2D_1D (int , int );

 /**
 *\fn void trans1D_2D (int z, int * x, int * y)
 *\brief transformation de coordonnes 2D vers 1D
 *\param x pointeur sur le parametre sur la ligne 
 *\param y pointeur sur le parametre sur la colonne
 *\param z coordonne 1D de la tete du bateau

*/

 void trans1D_2D (int , int * , int * );

 /**
 *\fn int reponse_tir(int coord ,int provenance,var_game_t * var)
 *\brief fonction de reponse a un tir
 *\param coord coordonnee 1D du tir
 *\param provenance booleen indiquant la provenance du tir 
 *\param var pointeur sur la structure contenant les variables du jeu
 *\return reponse retourne la valeur de la reponse au tir

*/

int reponse_tir(int ,int ,var_game_t *);

 /**
 *\fn int tir_alea(int * permit_tir,int * bat_rest_hum,var_game_t * var)
 *\brief fonction de tir aleatoire du cpu
 *\param permit_tir matrice de permitivite de tir du cpu
 *\param rep_tir reponse du tir comportement identique a reponse_tir
 *\param var pointeur sur la structure contenant les variables du jeu
 *\return z coordonne 1D du tir du cpu
*/

int tir_alea(int * , int * , var_game_t *);

 /**
 *\fn void suppr_touch(int * permit, int * max, int x, int y) 
 *\brief fonction de suppression des points diagonaux au point de tir
 *\param permit pointeur sur le tableau des cases possibles
 *\param max pointeur sur le nombre de cases possibles
 *\param x numero de lignes du point � supprimer 
 *\param y numero de colonnes du poitn a supprimer

*/

void suppr_touch(int * , int * ,int , int );

 /**
 *\fn int deja_tire(int x, int y, var_game_t * var)
 *\brief fonction de determination des cases possibles aux alentours du tir
 *\param x numero de lignes du point � supprimer 
 *\param y numero de colonnes du poitn a supprimer
 *\param var pointeur sur la structure des variables du jeu

*/

int deja_tire(int , int , var_game_t *);

 /**
 *\fn void suppr_bout(int * permit, int * max, int sens, int x, int y) 
 *\brief fonction de suppression des points aux bouts du bateau coule
 *\param permit pointeur sur le tableau des cases possibles
 *\param max pointeur sur le nombre de cases possibles
 *\param sens valeur caracteristique a un sens 
 *\param x numero de lignes du point � supprimer 
 *\param y numero de colonnes du poitn a supprimer

*/

void suppr_bout(int *, int *, int ,int , int );

 /**
 *\fn int tir_humain()
 *\brief Gestion du tir par le joueur
 *\param var pointeur sur la structure des variables du jeu
 *\return tir la coordonne 1D du tir Humain

*/

int tir_humain(var_game_t * );

#endif
