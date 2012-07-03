/**
 * \file couic.c
 * \brief fonction qui couic l'horloge suisse
 * \author Maxime Escourbiac Jean Christophe Septier
 * \date Mardi 26 Octobre 2010
 */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>

int main(int argc, char ** argv)
{
   int pid;
   if( argc == 2 )
   {
      pid = atoi(argv[1]);
      kill(pid,SIGTERM);
   }
   else
      fprintf(stderr,"souci avec l'argument \n");
   return (EXIT_SUCCESS);
}