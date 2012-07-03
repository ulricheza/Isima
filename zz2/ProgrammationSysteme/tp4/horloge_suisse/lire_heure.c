/**
 * \file lire_heure.c
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

int main(int argc, char ** argv)
{
  int sem_sec,sem_min,sem_heu;
  int sec,min,heu;
  time_t t1,t2;
  key_t key_sec,key_min,key_heu;
  
  
  /* gerer la fermeture proprement*/
  key_sec = ftok("./seconde", 2012);
  sem_sec = semget(key_sec, 1, 0660 | IPC_CREAT);
  key_min = ftok("./minute", 2012);
  sem_min = semget(key_min, 1, 0660 | IPC_CREAT);
  key_heu = ftok("./heure", 2012);
  sem_heu = semget(key_heu, 1, 0660 | IPC_CREAT);
  
  sec = semctl(sem_sec,0,GETVAL);
  min = semctl(sem_min,0,GETVAL);
  heu = semctl(sem_heu,0,GETVAL);
  printf(" %d : %d : %d \n",heu,min,sec);
  
}