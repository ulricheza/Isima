/**
 * \file client.c
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
#include <pthread.h>

char nom_client[20];

/**
 * \fn void * affic_mess(void * par)
 * \brief thread pour l'affichage des messages
 * \param par useless
 */
void * affic_mess_thread(void * par)
{
   int fd,fin_recept = 1;
   FILE * reception;
   FILE * fic;
   char buff[255];


   printf("Client connecte\n");

   while(1)
   {
      fd = open(nom_client, O_RDONLY);
      reception = fdopen(fd,"r");
      fgets(buff,255,reception);
      buff[strlen(buff) - 1] = '\0';
      if(strcmp(buff,"-1") != 0)
      {
         printf("message de %s ::\n",buff);
         fgets(buff,255,reception);
         buff[strlen(buff) - 1] = '\0';
         printf("%s\n",buff);
         fclose(reception);
      }
      else
      {
         printf("reception de fichier\n");
         fic = fopen("recu.dat","w");
         if(fic != NULL)
         {
            while(fin_recept != 0)
            {
              fin_recept = fread(buff,1,1,reception);
              if(fin_recept != 0)
                 fwrite(buff,1,1,fic);
            }
            fclose(fic);
         }
         else
            fprintf(stderr,"probleme avec fichier de reception\n");     
      }
   }
   pthread_exit(NULL);
}

/*----------------explication--------------------------------*/
/* Explications sur le protocole utilise:                    */
/* Chaque message est caracterise par un type                */
/* 0 : connexions au serveur                                 */
/* 1 : envoyer un message a tous les gens connectes          */
/* 2 : se deconnecteur du serveur                            */
/* 3 : envoyer un message prive                              */
/* 4 : envoyer un fichier                                    */
/*-----------------------------------------------------------*/


int main(int argc, char ** argv)
{
  int fs,fpm,adress_valid,fin = 0,fin_recept = 1;
  FILE * envoie;
  FILE * mess_prive;
  FILE * fichier;
  char buff[255];
  char type[10];
  char adress_client_pm[10];
  char fic_to_send[20];
  char buff_fic;
  pthread_t affic_mess;

  sprintf(nom_client,"%d\0",getpid());

  if(mkfifo(nom_client,0644) != 0)
  {
     fprintf(stderr,"erreur creation du pipe\n");
     exit(EXIT_FAILURE);
  }

  fs=open("serveur", O_WRONLY);
  if(fs<0)
  {
     fprintf(stderr,"erreur dans la lecture du serveur\n");
     exit(EXIT_FAILURE);
  }

  envoie = fdopen(fs,"a");
  fprintf(envoie,"0\n%s\n",nom_client);
  fclose(envoie);
  pthread_create(&affic_mess,NULL,affic_mess_thread,NULL);

  while(!fin)
  {
      /*----------------explication--------------------------------*/
      /*on est oblige d'ouvrir et de fermer le fichier d'ecriture  */
      /*car tant qu'on a pas fait de fclose(envoie), ce qu'on ecrit*/
      /*n'apparait pas dans le fichier serveur                     */
      /*-----------------------------------------------------------*/
      fs=open("serveur", O_WRONLY);
      if(fs<0)
      {
         fprintf(stderr,"Le serveur s'est deconnecte\n");
         exit(EXIT_FAILURE);
      }
      envoie = fdopen(fs,"a");
      printf("type:\n");
      fgets(type,10,stdin);
      type[1]='\0';
      if(type[0] == '1') /*envoie un message a tout le chat*/
      {
         printf("message:\n");
         fgets(buff,255,stdin);
         buff[strlen(buff)-1] == '\0';
         fprintf(envoie,"%s\n%s\n%s\n",type,nom_client,buff);
      }
      else
      {
        if(type[0] == '2') /*envoie un message de type deconnexion*/
        {
           fprintf(envoie,"%s\n%s\n%s",type,nom_client,"deconnexion");
           fin = 1;
        }
        else
        {
           if(type[0] == '3') /* envoie un message prive*/
           {
              adress_valid = 0;
              do
              {
                 printf("Destinataire du message prive\n");
                 fgets(adress_client_pm,10,stdin);
                 adress_client_pm[strlen(adress_client_pm)-1] = '\0';
                 fpm=open(adress_client_pm,O_WRONLY);
                 if(fpm<0)
                    fprintf(stdout,"erreur dans la lecture du serveur\n");
                 else
                    adress_valid = 1;
              }while(!adress_valid);
              printf("message:\n");
              fgets(buff,255,stdin);
              buff[strlen(buff)-1] == '\0';
              mess_prive = fdopen(fpm,"a");
              fprintf(mess_prive,"%s\n%s\n",nom_client,buff);
              fclose(mess_prive);
           }
           else /*envoie un fichier*/
           {
              adress_valid = 0;
              do
              {
                 printf("Destinataire du fichier\n");
                 fgets(adress_client_pm,10,stdin);
                 adress_client_pm[strlen(adress_client_pm)-1] = '\0';
                 fpm=open(adress_client_pm,O_WRONLY);
                 if(fpm<0)
                    fprintf(stdout,"erreur dans la lecture du serveur\n");
                 else
                    adress_valid = 1;
              }while(!adress_valid);
              printf("Nom du fichier a envoye:\n");
              fgets(fic_to_send,20,stdin);
              fic_to_send[strlen(fic_to_send)-1] = '\0';
              mess_prive = fdopen(fpm,"a");
              
              fichier = fopen(fic_to_send,"r");
              if(fichier != NULL)
              {
                 fprintf(mess_prive,"-1\n");
                 while(fin_recept != 0)
                 {
                   fin_recept = fread(&buff_fic,1,1,fichier);
                   if(fin_recept != 0)
                      fwrite(&buff_fic,1,1,mess_prive);
                 }
                 fclose(fichier);
              }
              else
                 printf("le fichier a envoyer n'existe pas \n");
              fclose(mess_prive);
           }
        }
      }
      fclose(envoie);
  }
  pthread_cancel(affic_mess);
  unlink(nom_client);
  return EXIT_SUCCESS;
}
      
   