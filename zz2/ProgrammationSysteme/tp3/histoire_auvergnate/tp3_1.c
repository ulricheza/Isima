/**
 * \file tp3_1.c
 * \brief Une histoire d'auvergnat
 * \author Maxime Escourbiac Jean Christophe Septier
 * \date Vendredi 22 Octobre
 */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>


void sig_tueur(int );
void sig_jevaismourrir(int );
void sig_jevaistevenger(int );


pid_t fils_meurtrier, fils_vengeur;

int main()
{

   if(signal(SIGTERM,sig_jevaismourrir) == SIG_ERR)
      fprintf(stderr,"erreur armement de signal sig_jevaismourrir\n");
   
   if(signal(SIGUSR1,sig_tueur) == SIG_ERR)
      fprintf(stderr,"erreur armement de signal sig_tueur\n");
                   
    if(signal(SIGUSR2,sig_jevaistevenger) == SIG_ERR)
      fprintf(stderr,"erreur armement de signal sig_tueur\n");

   fprintf(stdout,"Creation fils meurtrier \n");
   fils_meurtrier = fork();

   switch(fils_meurtrier)
   {
      case -1: /*erreur dans la creation*/
         fprintf(stderr,"erreur creation fork fils_meurtrier \n");
         exit(EXIT_FAILURE);
         break;
      case 0:  /*cas processus fils*/
         fprintf(stdout,"attente de signal pour tuer le pere\n");
         for(;;);
         break;
      default:
         fprintf(stdout,"creation fork fils_vengeur\n");
         fils_vengeur = fork();
         switch(fils_vengeur)
         {
            case -1: /*erreur dans la creation*/
               fprintf(stderr,"erreur creation fork fils_meurtrier \n");
               exit(EXIT_FAILURE);
               break;
            case 0:  /*cas processus fils*/
               fprintf(stdout,"attente signal tuer frere\n");
               for(;;); 
               break;
            default:
               fprintf(stdout,"envoie signal au fils meurtrier\n");
               kill(fils_meurtrier,SIGUSR1);
               for(;;);
               break;
         }
         break;
    }

}

void sig_tueur(int sig)
{
   fprintf(stdout,"envoie signal tuer pere\n");
   kill(getppid(),SIGTERM);
}

void sig_jevaismourrir(int sig)
{
   fprintf(stdout,"envoie signal de vengence au fils vengeur\n");
   kill(fils_vengeur,SIGUSR2);
   exit(EXIT_FAILURE);
}

void sig_jevaistevenger(int sig)
{
   fprintf(stdout,"envoie du signal de meutre du fils patricide\n");
   kill(fils_meurtrier,SIGKILL);
   kill(fils_vengeur,SIGKILL);
}