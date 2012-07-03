/**
 * \file tp3_2.c
 * \brief L'horloge suisse
 * \author Maxime Escourbiac Jean Christophe Septier
 * \date Lundi 25 Octobre 2010
 */

#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>


void a_cont(int id);
void affic(int id);
void raz(int id);
void faire_couic(int id);

pid_t seconde,minute,heure;

int val = 0;
int cont = 0;

int main()
{
   time_t  t1,t2;
   
   signal(SIGTERM,faire_couic);
   heure = fork();
   switch(heure)
   {
      case -1:
         fprintf(stderr,"erreur creation fork heure \n");
         exit(EXIT_FAILURE);
         break;
      case 0:
         signal(SIGCONT,a_cont);
         signal(SIGUSR1,affic);
         signal(SIGUSR2,raz);
         for(;;)
         {
            while(!cont)
               pause();
            cont = 0;
            ++val;   
         }
         break;
      default:
         minute = fork();
         switch(minute)
         {
            case -1:
               fprintf(stderr,"erreur creation fork heure \n");
               exit(EXIT_FAILURE);
               break;
            case 0:
               signal(SIGCONT,a_cont);
               signal(SIGUSR1,affic);
               signal(SIGUSR2,raz);
               for(;;)
               {
                  while(!cont)
                     pause();
                  cont = 0;
                  ++val;
                  if(val==60)
                  {
                     val = 0;
                     kill(heure,SIGCONT);
                  }
               }
               break;
            default:
               seconde = fork();
               switch(seconde)
               {
                  case -1:
                     fprintf(stderr,"erreur creation fork heure \n");
                     exit(EXIT_FAILURE);
                     break;
                  case 0:
                     signal(SIGCONT,a_cont);
                     signal(SIGUSR1,affic);
                     signal(SIGUSR2,raz);
                     for(;;)
                     {
                        while(!cont)
                           pause();
                        cont = 0;
                        ++val;
                        if(val == 60)
                        {
                           val = 0;
                           kill(minute,SIGCONT);
                        }
                     }
                     break;
                  default:
                     printf("Pid du pere : %d \n",getpid());
                     printf("Pid des secondes : %d \n",seconde);
                     printf("Pid des minutes : %d \n",minute);
                     printf("Pid des heures : %d \n",heure);
                     for(;;)
                     {
                        time(&t1);
                        do
                        {
                           time(&t2);
                        }while(difftime(t2,t1) < 1.0);
                        kill(seconde,SIGCONT);
                     }
                     break;
               }
               break;
         }
         break;
   }
   return(EXIT_SUCCESS);                  
}

void a_cont(int id)
{
   cont++;
}

void affic(int id)
{
   printf("%d \n",val);
}

void raz(int id)
{
   val = 0;
}

void faire_couic(int id)
{
   kill(seconde,SIGKILL);
   kill(minute,SIGKILL);
   kill(heure,SIGKILL);
   raise(SIGKILL);
}