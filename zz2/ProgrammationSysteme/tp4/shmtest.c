#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
# include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
   pid_t pere,fils,ret;
   key_t key;
   int shmid,i,n;
   char *buffer;
   struct shmid_ds garbage;

   printf("C'est partis !\n");

   /* on creer une shm */

   key=ftok("/etc/hosts",getpid());

   shmid=shmget(key, 1024*sizeof(char), 0660|IPC_CREAT);

   fils = fork();

   if 
      (fils==-1) fprintf(stderr, "erreur je sort");
   else
   {
      if (fils==0) /* c'est le fils */
      { 
         printf("%d: Je suis le fils de %d \n", getpid(), getppid());  
         for (;;)
	      {
	         if (buffer=shmat(shmid,NULL,0))
	         {
	            n=time(NULL);
		         sprintf(buffer,"fils PID:%d \t fils:%d \t time : %d\n",fils,getpid(),n);
		         sleep(2);
		      }
		      else
		         exit(1);
	       }
	       printf("%d: Je sort \n",getpid());  exit(20); }
	       else
	       {
             printf("%d: Je suis le p�re de %d \n", getpid(), fils);
	          if (buffer=shmat(shmid,NULL,0))
	             for (i=0;i<20;i++)
	             {
		             sleep(1);
		             printf(buffer);
		          }
		      kill(fils,15);
	         waitpid(fils, &ret, 0);
	         printf("%d: Le processus fils %d est sorti \n", getpid(), getppid());
		      for (i=0;i<20;i++)
		      {
               sleep(1); printf("."); fflush(stdout); }
		         shmdt(buffer); 
		         shmctl(shmid,IPC_RMID , &garbage);  
	         }
    } 
}
/* FIN du main */
