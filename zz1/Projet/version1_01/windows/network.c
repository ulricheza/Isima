/**
 * \file network.c
 * \brief rassemblement des fonctions developees pour le reseau
 * \author Maxime Escourbiac 
 * \version 1.01
 * \date Jeudi 2 septembre 2010
 *
 *
 */


#include "network.h"

void * accept_connect(var_game_t * var)
{
   socklen_t taille = sizeof(SOCKADDR_IN);
   /*attente de la connexion*/
   var->sock_client = accept(var->sock_serveur, (SOCKADDR*)&(var->sin_client), &taille );
   if( var->sock_client == -1) /*si echec de connexion*/
   {
      fprintf(var->log_erreur,"Erreur lors de la connexion\n");
      fin(var,0);
      exit(EXIT_FAILURE);
   }
   pthread_exit(NULL);
}

void * recept_rdy(var_game_t * var)
{
   long rdy = 0;
   /*attente de reception*/
   if(recv(var->sock_client, &rdy, sizeof(long),0) == -1)/*si echec de reception*/
   {
      fprintf(var->log_erreur,"Erreur lors de la reception du jeton ready\n");
      fin(var,0);
      exit(EXIT_FAILURE);
   }
   pthread_exit(NULL);
}

void envoi_coord(var_game_t * var)
{
   long envoi = htonl((long)var->z);
   /*envoie de la coordonnee en type long*/
   if( send(var->sock_client,&envoi,sizeof(long),0) == -1)/*si echec de l'envoi*/
   {
      fprintf(var->log_erreur,"Erreur lors de l'envoi des coordonnees\n");
      fin(var,0);
      exit(EXIT_FAILURE);
   }

}

void * recept_coord(var_game_t * var)
{
   long tir_cpu;
   long rep_tir;
   
   /*mise en attente du tir du joueur reseau*/
   if(recv(var->sock_client, &tir_cpu, sizeof(long),0) == -1)
   {
      fprintf(var->log_erreur,"Erreur reception coordonnes\n");
      fin(var,0);
      exit(EXIT_FAILURE);
   }
   else
   {
      tir_cpu = ntohl(tir_cpu);
      /*appel de la fonction de reponse a un tir du joueur reseau*/
      rep_tir = (long) reponse_tir((int) tir_cpu ,0,var);
      if(rep_tir == 2)
      {
         var->remain_bat_hum--;
         affich_score(var,0);
      }
      rep_tir = htonl(rep_tir);
      if(send(var->sock_client,&rep_tir,sizeof(long),0) == -1)
      {
         fprintf(var->log_erreur,"Erreur envoie reponse\n");
         fin(var,0);
         exit(EXIT_FAILURE);
      }
   }
   pthread_exit(NULL);
}

void * recept_rep(var_game_t * var )
{
   long rep_tir;
   int x,y;
   SDL_Rect position;
   
   /*mise en attente de la reception de la reponse*/
   if(recv(var->sock_client, &rep_tir, sizeof(long),0) == -1)
   {
      fprintf(var->log_erreur,"Erreur reception reponse\n");
      fin(var,0);
      exit(EXIT_FAILURE);
   }
   else
   {
      rep_tir = ntohl(rep_tir);
      trans1D_2D(var->z,&x,&y);
      position.x = 400 + 30*x;
      position.y = 25 + 30*y;
      
      /*MAJ de la matrice cible du joueur*/
      switch(var->mer_cible_hum[var->z] = (int)rep_tir)
      {
         case 0: message_box(var,"Votre tir a rate");
	         SDL_BlitSurface(var->rate,NULL,var->ecran,&position);
		 FSOUND_PlaySound(FSOUND_FREE,var->rate_sound);
                 break;
         case 1: message_box(var,"Votre tir a touche");
	         SDL_BlitSurface(var->touche,NULL,var->ecran,&position);
		 FSOUND_PlaySound(FSOUND_FREE,var->touche_sound);
                 break;
         case 2: var->remain_bat_cpu--;
	         affich_score(var,1);
	         message_box(var,"Votre tir a coule un bateau");
	         SDL_BlitSurface(var->touche,NULL,var->ecran,&position);
		 FSOUND_PlaySound(FSOUND_FREE,var->coule_sound);
                 break;
      }

   }
   SDL_Flip(var->ecran);
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
