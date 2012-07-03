/**
 * \file network.c
 * \brief rassemblement des fonctions devellopees pour le reseau
 * \author Maxime Escourbiac 
 * \version 1.0
 * \date Jeudi 1 avril 2010
 *
 *
 */


#include "network.h"



void * accept_connect(var_game_t * var)
{
   var = (var_game_t *) var;
   socklen_t taille = sizeof(SOCKADDR_IN);

   var->sock_client = accept(var->sock_serveur, (SOCKADDR*)&(var->sin_client), &taille );
   if( var->sock_client == INVALID_SOCKET)
   {
      fprintf(var->log_erreur,"Erreur lors de la connexion\n");
      fclose(var->log_erreur);
      exit(EXIT_FAILURE);
   }
   pthread_exit(NULL);
}


void * recept_rdy(var_game_t * var)
{
   long rdy = 0;

   if(recv(var->sock_client, &rdy, sizeof(long),0) == SOCKET_ERROR)
   {
      fprintf(var->log_erreur,"Erreur lors de la reception du jeton ready\n");
      fclose(var->log_erreur);
      exit(EXIT_FAILURE);
   }
   pthread_exit(NULL);
}

void envoi_coord(var_game_t * var)
{
   long envoi = htonl((long)var->z);

   if(send(var->sock_client,&envoi,sizeof(long),0)==-1)
   {
      fprintf(var->log_erreur,"Erreur lors de l'envoi des coordonnees\n");
      fclose(var->log_erreur);
      exit(EXIT_FAILURE);
   }

}

void * recept_coord(var_game_t * var)
{
   long tir_cpu;
   long rep_tir;
   int x,y;

   /*mise en attente du tir du joueur reseau*/
   if(recv(var->sock_client, &tir_cpu, sizeof(long),0) == SOCKET_ERROR)
   {
      fprintf(var->log_erreur,"Erreur reception coordonnes\n");
      fclose(var->log_erreur);
      exit(EXIT_FAILURE);
   }
   else
   {
      tir_cpu = ntohl(tir_cpu);
      /*appel de la fonction de reponse a un tir du joueur reseau*/
      rep_tir = (long) reponse_tir((int) tir_cpu ,0,var);
      if(rep_tir == 2)
         var->remain_bat_hum--;


      /*necessite d'utiliser une fonction SDL pour afficher le tir CPU dans la box*/
      /*pour la version texte on utilisera de simple printf*/
      trans1D_2D((int)tir_cpu, &x, &y);
      printf("le joueur a tire x: %d , y:%d \n",x,y);
      switch(rep_tir)
      {
         case 0: printf("son tir a rate\n");
                 break;
         case 1: printf("son tir a touche\n");
                 break;
         case 2: printf("son tir a coule un bateau \n");
                 break;
      }
      /*fin gestion temporaire*/
      rep_tir = htonl(rep_tir);
      if(send(var->sock_client,&rep_tir,sizeof(long),0) == SOCKET_ERROR)
      {
         fprintf(var->log_erreur,"Erreur envoie reponse\n");
         fclose(var->log_erreur);
         exit(EXIT_FAILURE);
      }
   }
   pthread_exit(NULL);
}


void * recept_rep(var_game_t * var )
{
   long rep_tir;

   /*mise en attente de la reception de la reponse*/
   if(recv(var->sock_client, &rep_tir, sizeof(long),0) == SOCKET_ERROR)
   {
      fprintf(var->log_erreur,"Erreur reception reponse\n");
      fclose(var->log_erreur);
      exit(EXIT_FAILURE);
   }
   else
   {
      rep_tir = ntohl(rep_tir);
      if(rep_tir == 2)
         var->remain_bat_cpu--;

      /*MAJ de la matrice cible du joueur*/
      var->mer_cible_hum[var->z] = (int)rep_tir;

      /*necessite d'utiliser une fonction SDL pour afficher le tir CPU dans la box*/
      /*pour la version texte on utilisera de simple printf*/

      switch(rep_tir)
      {
         case 0: printf("votre tir a rate\n");
                 break;
         case 1: printf("votre tir a touche\n");
                 break;
         case 2: printf("votre tir a coule un bateau \n");
                 break;
      }
      /*fin gestion temporaire*/

   }

   pthread_exit(NULL);
}


void close_sock(var_game_t * var, int serveur)
{
   /*fermeture de la transmission cote serveur*/
   if( serveur == 1)
   {
      shutdown(var->sock_client,2);
      closesocket(var->sock_serveur);
   }
   /*fermeture du socket*/
   closesocket(var->sock_client);

}
