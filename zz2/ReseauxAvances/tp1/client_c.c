/**
 *\file client_c.c
 *\brief programme client
 *\date 9 fevrier
 *
*/



#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/wait.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

/* Define, qui nous serviront par la suite */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close (s)
#define PORT_C 61569
#define PORT_JAVA 6998
#define TAILLE_MESS_C 7
#define TAILLE_MESS_JAVA 255

/* De m�me */
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;



void demandeNombre(char * mess)
{
   int termin = 0 ;
   do
   {
      printf("Entrer votre nombre ( entre -99 999 et 99 999 ) ou end pour terminer la session \n");
      scanf("%s", mess );
      if( !strcmp( mess , "end" ) )
      {
         termin = 1;
      }
      else
      {
         if(!atoi(mess))
         {
            printf( "Attention, ce n'est pas un nombre \n" );
         }
         else
            termin = 1;
      }
   }while ( !termin );
}


int main(int argc, char ** argv)
{
   int choix, termin = 0;
   int port;
   char mess[TAILLE_MESS_C];
   char serv[255];
   char phrase_java[255];
   char reponse_java[255] = {0};
   SOCKET s_com;
   SOCKADDR_IN adr;
   struct hostent * entree;

   printf("-------Menu--------------------\n");
   printf("1) Connexion au serveur C \n");
   printf("2) Connexion au serveur JAVA\n");
   printf("-------------------------------\n");
   scanf("%d",&choix);

   switch(choix)
   {
      case 1:
         port = PORT_C;
         break;
      case 2:
         port = PORT_JAVA;
         break;
      default:
         exit(EXIT_SUCCESS);
         break;
   }

   if(argc == 1)
   {
      printf("Veuillez saisir un nom de serveur\n");
      scanf("%s",serv);
   }
   else
   {
      strcpy(serv,argv[1]);
   }

   /* creation de la socket client */
   s_com = socket ( AF_INET, SOCK_STREAM, 0 );
   if( s_com == INVALID_SOCKET)
   {
      fprintf(stderr,"Probleme de creation de socket\n");
      exit(EXIT_FAILURE);
   }


   /* configuration du descripteur de la socket	*/
   adr.sin_family = AF_INET;
   adr.sin_port = htons (port);
   do
   {
      entree = (struct hostent *) gethostbyname (serv);
      if(!entree)
      {
         printf("Serveur non valide \n veuillez en saisir un autre \n");
         scanf("%s",serv);
      }
   }while(!entree);

   bcopy ( (char *) (entree->h_addr),(char*)&(adr.sin_addr) ,entree->h_length );

   if(connect(s_com,(SOCKADDR *) &adr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
   {
      fprintf(stderr,"Probleme de connexion \n");
      exit(EXIT_FAILURE);
   }

   switch(choix)
   {
      case 1: /* corps de metier pour le serveur C */
         do
         {
            demandeNombre(mess);
            send(s_com, mess , TAILLE_MESS_C, 0);
            if(!strcmp( mess , "end" ))
            {
               termin = 1;
               recv(s_com,mess,TAILLE_MESS_C,0);
               printf("Valeur retourne du serveur\n%s", mess );
            }
         }while ( !termin );
         break;
      case 2: /* corps de metier JAVA */
         printf("Veuillez rentrer la phrase de calcul\n");
         scanf("%c",&serv[0]);
         fgets(phrase_java , TAILLE_MESS_JAVA - 1 , stdin);
         send(s_com, phrase_java , TAILLE_MESS_JAVA , 0);
         recv(s_com,reponse_java,TAILLE_MESS_JAVA,0);
         printf("Valeur retourne du serveur\n%s\n", reponse_java );
         break;
   }
   close(s_com);
   return(EXIT_SUCCESS);
}

