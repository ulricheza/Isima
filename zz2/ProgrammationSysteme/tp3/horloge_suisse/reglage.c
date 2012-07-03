/**
 * \file reglage.c
 * \brief fonction qui configure l'horloge suisse
 * \author Maxime Escourbiac Jean Christophe Septier
 * \date Mardi 26 Octobre 2010
 */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main(int argc,char ** argv)
{
   int pid_sec,pid_min,pid_heur,pid_pere,heu,min,sec,i;
   if(argc == 8)
   {
      pid_pere = atoi(argv[1]); /*pid pere*/
      pid_sec = atoi(argv[2]); /* pid seconde*/
      pid_min = atoi(argv[3]); /* pid minute*/
      pid_heur = atoi(argv[4]); /* pid heure*/
      heu = atoi(argv[5]);
      min = atoi(argv[6]);
      sec = atoi(argv[7]);
      
      kill(pid_pere,SIGSTOP);
      /*mise a zero des differentes valeurs*/
      kill(pid_sec,SIGUSR2);
      kill(pid_min,SIGUSR2);
      kill(pid_heur,SIGUSR2);
      
      for(i=0;i<sec;++i)
         kill(pid_sec,SIGCONT);
      
      for(i=0;i<min;++i)
         kill(pid_min,SIGCONT);
      
      for(i=0;i<heu;++i)
         kill(pid_heur,SIGCONT);
      
       kill(pid_pere,SIGCONT);
   }
   else
      fprintf(stderr,"erreur dans les arguments\n");
   return(EXIT_SUCCESS);
}