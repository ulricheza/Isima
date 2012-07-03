/**
 * \file coucou.c
 * \brief fonction qui affiche la valeur de l'horloge suisse
 * \author Maxime Escourbiac Jean Christophe Septier
 * \date Lundi 25 Octobre 2010
 */



#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main(int argc,char ** argv)
{
   int pid_sec,pid_min,pid_heur;
   if(argc == 4)
   {
      pid_sec = atoi(argv[1]); /* pid seconde*/
      pid_min = atoi(argv[2]); /* pid minute*/
      pid_heur = atoi(argv[3]); /* pid heure*/
      kill(pid_sec,SIGUSR1);
      kill(pid_min,SIGUSR1);
      kill(pid_heur,SIGUSR1);
   }
   else
      fprintf(stderr,"erreur argument\n");
   return (EXIT_SUCCESS);
}
   