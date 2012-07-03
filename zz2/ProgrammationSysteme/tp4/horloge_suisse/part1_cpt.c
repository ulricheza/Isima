/**
 * \file part2_cpt.c
 * \brief L'horloge suisse a base d'IPC 
 * \author Maxime Escourbiac
 * \date Sam 27 Novembre
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>

pid_t fils_sec,fils_min,fils_heu;

int sem_sec,sem_min,sem_heu;

void a_fermer(int id);

int main(int argc, char ** argv)
{

  time_t t1,t2;
  struct sembuf op_inc;
  struct sembuf op_dec;
  key_t key_sec,key_min,key_heu;
  
  
  /* gerer la fermeture proprement*/
  signal(SIGTERM,a_fermer);
  key_sec = ftok("./seconde",2012);
  sem_sec = semget(key_sec, 1, 0660 | IPC_CREAT);
  key_min = ftok("./minute", 2012);
  sem_min = semget(key_min, 1, 0660 | IPC_CREAT);
  key_heu = ftok("./heure", 2012);
  sem_heu = semget(key_heu, 1, 0660 | IPC_CREAT);
  
  op_inc.sem_num = 0;
  op_inc.sem_op = 1;
  op_inc.sem_flg = 0;
  op_dec.sem_num = 0;
  op_dec.sem_op = -60;
  op_dec.sem_flg = 0;
  
  fils_sec = fork();
  if(fils_sec == -1)
  {
    fprintf(stderr,"erreur creation fork fils_sec\n");
    exit(EXIT_FAILURE);
  }
  else
  {
    if(fils_sec==0)
    {
      /*-----------------------------------------------------*/
      /*Gestion IPC seconde                                  */
      /*-----------------------------------------------------*/

      semctl(sem_sec,0,SETVAL,0);      
      for(;;)
      {
         time(&t1);
         do
         {
            time(&t2);
         }while(difftime(t2,t1) < 1.0);
         /*operation sur le semaphore*/
         semop(sem_sec,&op_inc,1);
         printf("incrementation du semaphore seconde \n");
      }
    }
    else
    {
      fils_min = fork();
      if(fils_min == -1)
      {
        fprintf(stderr,"erreur creation fork fils_min\n");
        exit(EXIT_FAILURE);
      }
      else
      {
        if(fils_min == 0)
        {  
           semctl(sem_min,0,SETVAL,0);   
           for(;;)
           {
             semop(sem_sec,&op_dec,1);
             printf("incrementation du semaphore minute \n");
             semop(sem_min,&op_inc,1);
           }
        }
        else
        {
          fils_heu = fork();
          if(fils_heu == -1)
          {
            fprintf(stderr,"erreur creation fork fils_heu \n");
            exit(EXIT_FAILURE);
          }
          else
          {
            if(fils_heu == 0)
            {
               semctl(sem_heu,0,SETVAL,0);
               for(;;)
               {
                  semop(sem_min,&op_dec,1);
                  printf("incrementation du semaphore heure \n");
                  semop(sem_heu,&op_inc,1);
               }
            }
            else
              for(;;)
                sleep(1);
          }
        }
      }
    }
  }
  return(EXIT_SUCCESS);
}

void a_fermer(int id)
{
   kill(fils_sec,SIGKILL);
   kill(fils_min,SIGKILL);
   kill(fils_heu,SIGKILL);
   semctl(sem_sec,0,IPC_RMID,0);
   semctl(sem_min,0,IPC_RMID,0);
   semctl(sem_heu,0,IPC_RMID,0);
   exit(EXIT_SUCCESS);
}      
        
    