/**
 * \file jeu2p.c
 * \brief version 0.5 de navy battle en texte
 * \author Maxime Escourbiac 
 * \version 1.0
 * \date Jeudi 1 avril 2010
 *
 * 
 */


#include "jeu2p.h"

/*declaration des variables externe*/


int main(int argc, char ** argv)
{
   int choix1 = 0;
   int choix2 = 0;

   clear
   while(choix1 != -1)
   {
      printf("-----------------------------------------------------\n");
      printf("Bienvenue sur la version 0.5 de Navy Battle \n");
      printf("Cette version sert de test pour le moteur du jeu & le mode reseau_local\n");
      printf("-----------------------------------------------------\n");
      printf("1) Mode solo \n");
      printf("2) Mode multi local \n");
      printf("autre: Quittez le programme \n");
      printf("-----------------------------------------------------\n");
      scanf("%d",&choix1);

      switch(choix1)
      {
         case 1:
                  mode_solo();
                  break;
         case 2:
                  printf("1) Mode serveur\n");
                  printf("2) Mode client \n");
                  scanf("%d",&choix2);
                  if(choix2 == 2)
                    mode_local_client();
                  else
                    mode_local_serveur();
                  break;
         default:
                  choix1=-1;
      }
   }
   return 0;
}



int mode_solo()
{
   int rep_tir_cpu;
   int i,x,y;
   int * permit_tir;
   var_game_t * var;

   init_var(1,&var);

   permit_tir = (int *)malloc(100*sizeof(int));
   if(permit_tir == NULL)
   {
      fprintf(var->log_erreur,"erreur dans l'allocation de permit_tir\n");
      exit_err(var);
   }
   for(i=0;i<100;i++)
      permit_tir[i] = i;

   clear
   printf("-----------------------------------------------------\n");
   printf("Bienvenue sur la version 0.1 de Navy Battle \n");
   printf("Cette version sert de test pour le moteur du jeu\n");
   printf("attention les cases vont de 0 a 9               \n");
   printf("-----------------------------------------------------\n");
   printf("-----------------------------------------------------\n");
   printf("placement des bateaux CPU\n");
   placement_alea(var);
   printf("-----------------------------------------------------\n");
   printf("placement de vos bateaux\n");
   placement_hum(var);
   printf("-----------------------------------------------------\n");
   printf("DEBUT DU JEU\n");
   clear
   while(var->remain_bat_cpu != 0 && var->remain_bat_hum != 0)
   {
      printf("-----------------------------------------------------\n");
      printf("-----------------------------------------------------\n");
      printf("votre matrice cible \n");
      affic_mat(var->mer_cible_hum,0);
      printf("-----------------------------------------------------\n");
      printf("-----------------------------------------------------\n");
      printf("votre matrice home\n");
      affic_mat(var->mer_home_hum,1);
      printf("-----------------------------------------------------\n");
      printf("-----------------------------------------------------\n");
      printf("A vous de tirer !\n");
      var->z = tir_humain(var);
      clear
      var->mer_cible_hum[var->z] = reponse_tir(var->z,1,var);
      switch(var->mer_cible_hum[var->z])
      {
         case 0: printf("Votre tir a rate\n");
                 break;
         case 1: printf("Votre tir a touche un bateau\n");
                 break;
         case 2: printf("Votre tir a touche et coule un bateau\n");
                 var->remain_bat_cpu = var->remain_bat_cpu - 1;
                 break;
      }
      printf("Au CPU de tirer\n");
      var->z = tir_alea(permit_tir, &rep_tir_cpu, var);
      trans1D_2D(var->z,&x,&y);
      printf("le CPU a tire a la case %d %d \n",x,y);
      switch(rep_tir_cpu)
      {
         case 0: printf("Son tir a rate\n");
                 break;
         case 1: printf("Son tir a touche un de vos bateau\n");
                 break;
         case 2: printf("Son tir a touche et coule un de vos bateau\n");
                 break;
      }
   }
   if(var->remain_bat_cpu == 0)
      printf("Bravo vous avez gagne!!!\n");
   else
      printf("dommage vous avez perdu \n");

   free(var->mer_home_cpu);
   free(var->mer_home_hum);
   free(var->mer_cible_cpu);
   free(var->mer_cible_hum);
   free(permit_tir);
   fclose(var->log_erreur);
   free(var);
   return(EXIT_SUCCESS);
}

int mode_local_client()
{
   /*declaration des variables*/
   var_game_t * var;
   void * temp;
   long ready = 1;
   long deb;
   char adresse_ip[20];
   pthread_t thread;


   /*ouverture du module socket sous windows*/
   #ifdef __WIN32__
      WSADATA WSAData;
      WSAStartup(MAKEWORD(2,2), &WSAData);
   #endif


   /*allocation des ressources*/
   init_var(0,&var);

   do
   {
      /*demande de l'adresse IP du serveur*/
      /*gestion temporaire avec un scanf  */
      printf("adresse ip du serveur?\n");
      scanf("%s",adresse_ip);

      /*creation de la socket*/
      var->sock_client=socket(AF_INET, SOCK_STREAM, 0);

      /*configuration de la connexion*/
      var->sin_client.sin_addr.s_addr = inet_addr(adresse_ip);
      var->sin_client.sin_family = AF_INET;
      var->sin_client.sin_port = htons(PORT);
   }while(connect(var->sock_client, (SOCKADDR*) &var->sin_client, sizeof(var->sin_client)) < 0);
   printf("connection effectue\n");

   
   pthread_create(&thread, NULL,(void *)recept_rdy,var);
   printf("-----------------------------------------------------\n");
   printf("placement de vos bateaux\n");
   placement_hum(var);

   ready = htonl(1);
   if(send(var->sock_client,&ready,sizeof(long),0) == -1)
   {
      fprintf(var->log_erreur,"Erreur envoie ready\n");
      fclose(var->log_erreur);
      exit(EXIT_FAILURE);
   }

   printf("attente placement des bateaux du joueur adverse \n");
   pthread_join(thread,&temp);

   /*reception du jeton de depart*/
   if(recv(var->sock_client, &deb, sizeof(long),0) == -1)
   {
      fprintf(var->log_erreur,"Erreur reception deb\n");
      fclose(var->log_erreur);
      exit(EXIT_FAILURE);
   }
   deb = ntohl(deb);

   while(var->remain_bat_cpu != 0 && var->remain_bat_hum != 0)
   {
      clear
      printf("-----------------------------------------------------\n");
      printf("-----------------------------------------------------\n");
      printf("votre matrice cible \n");
      affic_mat(var->mer_cible_hum,0);
      printf("-----------------------------------------------------\n");
      printf("-----------------------------------------------------\n");
      printf("votre matrice home\n");
      affic_mat(var->mer_home_hum,1);
      printf("-----------------------------------------------------\n");
      printf("-----------------------------------------------------\n");

      if(deb == 1)
      {
         pthread_create(&thread, NULL,(void *)recept_coord,var);
         /*gestion du rafraichissement SDL pas d'actualité dans cette version*/
         printf("attente du tir du joueur adverse \n");

         pthread_join(thread,&temp);

      }

      printf("A vous de tirer !\n");
      var->z = tir_humain(var);
      envoi_coord(var);

      pthread_create(&thread, NULL,(void *)recept_rep,var);
      /*gestion du rafraichissement SDL pas d'actualité dans cette version*/
      printf("attente reponse joueur adverse\n");
      pthread_join(thread,&temp);

      if(deb != 1)
      {
         pthread_create(&thread, NULL,(void *)recept_coord,var);
         /*gestion du rafraichissement SDL pas d'actualité dans cette version*/
         printf("attente du tir du joueur adverse \n");

         pthread_join(thread,&temp);

      }
   }
   if(var->remain_bat_cpu == 0)
      printf("Bravo vous avez gagne!!!\n");
   else
      printf("dommage vous avez perdu \n");

   close_sock(var, 0);

   #ifdef __WIN32__
      WSACleanup();
   #endif

   free(var->mer_home_cpu);
   free(var->mer_home_hum);
   free(var->mer_cible_cpu);
   free(var->mer_cible_hum);
   fclose(var->log_erreur);
   free(var);
   return 1;
}

int mode_local_serveur()
{
   /*declaration des variables*/
   var_game_t * var;
   void * temp;
   long ready = 1;
   long deb;
   pthread_t thread;


   /*ouverture du module socket sous windows*/
   #ifdef __WIN32__
      WSADATA WSAData;
      WSAStartup(MAKEWORD(2,2), &WSAData);
   #endif


   /*allocation des ressources*/
   init_var(0,&var);

   /*creation de la socket*/
   var->sock_serveur=socket(AF_INET, SOCK_STREAM, 0);

   /*configuration de la connexion*/
   var->sin_serveur.sin_addr.s_addr = htonl(INADDR_ANY);
   var->sin_serveur.sin_family = AF_INET;
   var->sin_serveur.sin_port = htons(PORT);

   if( bind(var->sock_serveur, (SOCKADDR*)&(var->sin_serveur), sizeof(var->sin_serveur)) < 0)
   {
      fprintf(var->log_erreur,"erreur lors du bind serveur \n");
      fclose(var->log_erreur);
      exit(EXIT_FAILURE);
   }

   if(listen(var->sock_serveur,5) == -1)
   {
      fprintf(var->log_erreur,"erreur lors du listen \n");
      fclose(var->log_erreur);
      exit(EXIT_FAILURE);
   }

   deb = rand()%2;


   pthread_create(&thread, NULL,(void *)accept_connect,var);
   /*gestion du rafraichissement SDL pas d'actualité dans cette version*/
   printf("attente de connexion du joueur adverse\n");
   pthread_join(thread,&temp);

   pthread_create(&thread, NULL,(void *)recept_rdy,var);
   printf("-----------------------------------------------------\n");
   printf("placement de vos bateaux\n");
   placement_hum(var);

   ready = htonl(1);
   if(send(var->sock_client,&ready,sizeof(long),0) == -1)
   {
      fprintf(var->log_erreur,"Erreur envoie ready\n");
      fclose(var->log_erreur);
      exit(EXIT_FAILURE);
   }
   printf("attente placement des bateaux du joueur adverse \n");
   pthread_join(thread,&temp);

   deb = htonl(deb);
   if(send(var->sock_client,&deb,sizeof(long),0) == -1)
   {
       fprintf(var->log_erreur,"Erreur envoie deb\n");
       fclose(var->log_erreur);
       exit(EXIT_FAILURE);
   }
   deb = ntohl(deb);
   while(var->remain_bat_cpu != 0 && var->remain_bat_hum != 0)
   {
      clear
      printf("-----------------------------------------------------\n");
      printf("-----------------------------------------------------\n");
      printf("votre matrice cible \n");
      affic_mat(var->mer_cible_hum,0);
      printf("-----------------------------------------------------\n");
      printf("-----------------------------------------------------\n");
      printf("votre matrice home\n");
      affic_mat(var->mer_home_hum,1);
      printf("-----------------------------------------------------\n");
      printf("-----------------------------------------------------\n");

      if(deb == 1)
      {
         printf("A vous de tirer !\n");
         var->z = tir_humain(var);
         envoi_coord(var);

         pthread_create(&thread, NULL,(void *)recept_rep,var);
         /*gestion du rafraichissement SDL pas d'actualité dans cette version*/
         printf("attente reponse joueur adverse\n");
         pthread_join(thread,&temp);

      }

      pthread_create(&thread, NULL,(void *)recept_coord,var);
      /*gestion du rafraichissement SDL pas d'actualité dans cette version*/
      printf("attente du tir du joueur adverse \n");
      pthread_join(thread,&temp);

      if(deb != 1)
      {
         printf("A vous de tirer !\n");
         var->z = tir_humain(var);
         envoi_coord(var);

         pthread_create(&thread, NULL,(void *)recept_rep,var);
         /*gestion du rafraichissement SDL pas d'actualité dans cette version*/
         printf("attente reponse joueur adverse\n");
         pthread_join(thread,&temp);

      }
   }
   if(var->remain_bat_cpu == 0)
      printf("Bravo vous avez gagne!!!\n");
   else
      printf("dommage vous avez perdu \n");

   close_sock(var, 1);

   #ifdef __WIN32__
      WSACleanup();
   #endif

   free(var->mer_home_cpu);
   free(var->mer_home_hum);
   free(var->mer_cible_cpu);
   free(var->mer_cible_hum);
   fclose(var->log_erreur);
   free(var);
   return(1);
}

void affic_mat(int * mer,int type)
{
   int i,j;
   printf("  0 1 2 3 4 5 6 7 8 9\n");
   if(type == 0) /*mer cible*/
   {
      for(i=0;i<10;i++)
      {
         printf("%d ",i);
         for(j=0;j<10;j++)
         {
            switch(mer[10*i+j])
            {
               case -1: printf("  ");
                        break;
               case 0: printf("O ");
                       break;
               case 1:
               case 2: printf("X ");
                       break;
            }
         }
         printf("\n");
      }
   }
   else /*mer home*/
   {
      for(i=0;i<10;i++)
      {
         printf("%d ",i);
         for(j=0;j<10;j++)
         {
            switch(mer[10*i+j])
            {
               case -1: printf("  ");
                        break;
               case 0:
               case 1:
               case 2:
               case 3:
               case 4:
                       printf("X ");
                       break;
               case 5: printf("O ");
                       break;
               case 6: printf("# ");
            }
         }
         printf("\n");
      }
   }
}
