/**
 * \file serveur.c
 * \brief Utilisation d'un pipe nomme pour permettre de faire un chat
 * \author Maxime ESCOURBIAC Jean-Crhistophe SEPTIER
 * \date Vendredi 12 Novembre 2010
 */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>

#define CLIENT_MAX 100


int nb_client = 0;

void kill_serv(int id);

int main (int argc, char ** argv)
{
   /*declaration des variables*/
   int i,fd,temp_client;
   int * tab;
   FILE * reception;
   FILE * envoie;
   char type[10];
   char nom_client[10];
   char buff[255];
   char pipe_client[30];
   
   printf("PID du serv %d\n",getpid());
   
   tab = (int*)calloc(CLIENT_MAX,sizeof(int));
   
   if(signal(SIGTERM,kill_serv) == SIG_ERR)
      fprintf(stderr,"erreur armement de signal\n");
   
   /*ouverture du pipe nomme*/
   if(mkfifo("serveur",0644) != 0)
   {
      fprintf(stderr,"erreur creation tube\n");
      exit(EXIT_FAILURE);
   }
   fd = open("serveur", O_RDONLY|O_NONBLOCK);
   reception = fdopen(fd,"r");
   /*fin ouverture tube*/
   
   while(1)
   {
      printf("lecture du type \n");
      while(fgets(type,255,reception) == 0);
      type[1]='\0';
      switch(type[0])
      {
        case '0':
          printf("connexion d'un client \n");
          fgets(nom_client,255,reception);
          nom_client[strlen(nom_client)-1] = '\0';
          if(nb_client < CLIENT_MAX)
          {
            i = 0;
            while(tab[i] != 0)
               ++i;
            tab[i] = atoi(nom_client);
            ++nb_client;
          }
          break;
        case '1':
          printf("Envoie d'un message a tous le serveur\n");
          fgets(nom_client,255,reception);
          nom_client[strlen(nom_client)-1] = '\0';
          fgets(buff,255,reception);
          buff[strlen(buff)-1] = '\0';
          temp_client = 0;
          i = 0;
          while(temp_client < nb_client)
          {   
            while(tab[i] == 0 )
               ++i;
            sprintf(pipe_client,"%d\0",tab[i]);
            fd = open(pipe_client, O_WRONLY);
            envoie = fdopen(fd,"a");
            fprintf(envoie,"%s\n%s\n",nom_client,buff);
            fclose(envoie);
            ++i;
            ++temp_client;
          }
          break;
        case '2':
          printf("deconnexion d'un client \n");
          i = 0;
          fgets(nom_client,255,reception);
          nom_client[strlen(nom_client)-1] = '\0';
          while(tab[i]!= atoi(nom_client))
            ++i;
          tab[i] = 0;
          --nb_client;
          break;
      }
   }
}

void kill_serv(int id)
{
   int temp_client = 0;
   while(temp_client != nb_client)
   {
     ++temp_client;
   }
   unlink("serveur");
   exit(EXIT_SUCCESS);
}
      