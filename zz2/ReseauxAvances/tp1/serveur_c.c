/**
 * \file serveur_c.c
 * \brief programme serveur du tp 1 en C
 * \date 9 fevrier 2011
 * \author Maxime ESCOURBIAC
 *
 */



#define PORT 61569
#define TAILLE_MESS 7


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

/* Define, qui nous serviront par la suite */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close (s)

/* De m�me*/
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/wait.h>
#include <signal.h>

/* predeclaration des fonctions */
void couperserveur(int );

/*obligation de faire une variable globale afin de pouvoir l'eteindre proprement*/
SOCKET sock;  /*Socket serveur*/


/**
 * \fn int main(int argc, char ** argv)
 * \brief Fonction principale du serveur programme en C
 * \param argc nombre d'argument
 * \param argv liste des arguments lors du lancement du programme
 * \return EXIT_SUCCES si le programme se termine normalement , EXIT_FAILURE sinon
 *
 */

int main(int argc, char ** argv)
{
   pid_t fils;

   SOCKET csock; /*Socket client*/


   SOCKADDR_IN sin;  /*Descripteur de la socket serveur*/
   SOCKADDR_IN csin; /*Descripteur de la socket client*/

   socklen_t size = sizeof(SOCKADDR_IN);
   socklen_t csize;

   char message[TAILLE_MESS];
   int fin_mess = 0;
   int val;
   int somme = 0;
   int nb_element = 0;

   printf("PID du serveur: %d \n",getpid());
   signal(SIGTERM,couperserveur);


   sock = socket(AF_INET, SOCK_STREAM, 0);
   if(sock == INVALID_SOCKET)
   {
      fprintf(stderr,"Erreur dans la creation de socket\n");
      exit(EXIT_FAILURE);
   }

   printf("Creation de la socket serveur\n");

   /*parametrage de la socket serveur*/
   sin.sin_family = AF_INET;
   sin.sin_port = htons(PORT);
   sin.sin_addr.s_addr = INADDR_ANY;
   printf("parametrage de la socket serveur\n"); 

   /*bind de la socket serveur*/
   if( bind( sock, (SOCKADDR*) &sin,size) == SOCKET_ERROR)
   {
      fprintf(stderr,"Erreur dans le bind de la socket serveur\n");
      exit(EXIT_FAILURE);
   }

   /*Mise en ecoute de la socket serveur*/
   printf("Ecoute sur le port %d \n",PORT);
   if(listen(sock,20) == SOCKET_ERROR)
   {
      fprintf(stderr,"Erreur dans l'ecoute du serveur\n");
      exit(EXIT_FAILURE);
   }

   while(1)
   {
       printf("Attente d'un client\n");
       csock = accept(sock,(SOCKADDR*) &csin, &csize);
       fils = fork();
       switch(fils)
       {
          case -1: /*cas: erreur dans la creation du processus fils*/
             fprintf(stderr,"erreur dans la creation du fork\n");
             exit(EXIT_FAILURE);
             break;
          case 0: /*cas processus fils*/
             /*on recoit des chaines de caracteres representant des nombres*/
             while(fin_mess == 0)
             {
                printf("Attente du message: \n");
                recv(csock,message,TAILLE_MESS*sizeof(char),0);
                if( strcmp(message,"end") == 0) /*test si fin de saisie*/
                {
                    ++fin_mess;
                }
                else
                {
                   printf("message : %s \n",message);
                   /* les clients gerent normalement les erreurs de saisies
                      mais dans le cas contraire atoi en cas de chaine incorrecte
                      retournerait 0 donc pas de crash serveur mais une erreur de calcul.
                      l'utilisateur aurait pas du utiliser un autre client que le notre =) */
                   val = atoi(message);
                   somme += val;
                   ++nb_element;
                }
             }

             if(nb_element != 0)
                sprintf(message,"%d\n",somme/nb_element);
             else
                strcpy(message,"Err\n");

             printf("Envoie de la valeur au client: %s", message);
             send(csock,message,TAILLE_MESS*sizeof(char),0);
             /*coupure de la connection fils*/
             printf("Fermeture de la socket client\n");
             closesocket(csock);
             printf("Operation effectue\n");
             return(EXIT_SUCCESS);
             break;
          default:/*cas processus pere*/
             break;
       }
   }
   return(EXIT_SUCCESS);
}

/**
 * \fn void couperserveur(int id)
 * \brief Fonction qui arrete correctement le serveur via un signal SIGTERM
 * \param id parametre inutile mais necessaire pour la signature de la fonction
 *
 */

void couperserveur(int id)
{
   closesocket(sock);
   kill(getpid(),SIGKILL); /* <=> kill -9 sur lui meme*/
}
