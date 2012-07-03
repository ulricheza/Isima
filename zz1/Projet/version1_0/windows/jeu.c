/**
 * \file jeu2p.c
 * \brief version 0.5 de navy battle en texte
 * \author Maxime Escourbiac 
 * \version 1.0
 * \date Jeudi 1 avril 2010
 *
 * 
 */


#include "jeu.h"

int main(int argc, char ** argv)
{
    int finp = 0,first = 1;
    SDL_Surface * menu = NULL;
    SDL_Surface * ecran = NULL;
    SDL_Rect position_menu;
    SDL_Event event;
    FSOUND_STREAM * musique = NULL;
    
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    FSOUND_Init(44100,32,0);
    
    ecran = SDL_SetVideoMode(800,800,32,SDL_HWSURFACE | SDL_DOUBLEBUF);
    
    if(ecran == NULL)
       exit(EXIT_FAILURE);
    SDL_WM_SetCaption("Prozet zz1",NULL);
    
    menu = IMG_Load(".\\dessin\\menu.jpg");
    if(menu == NULL)
       exit(EXIT_FAILURE);
    
    position_menu.x = 0;
    position_menu.y = 0;
        
    musique = FSOUND_Stream_Open(".\\son\\jourdefoot.mp3",0,0,0);
    if(musique == NULL)
       exit(EXIT_FAILURE);
    while(finp == 0)
    {
       if(first == 1)
       {
          SDL_BlitSurface(menu,NULL,ecran,&position_menu);
          SDL_Flip(ecran);
          FSOUND_Stream_Play(FSOUND_FREE,musique);
	  first = 0;
       }
       SDL_WaitEvent(&event);
       switch(event.type)
       {
          case SDL_QUIT:
	               finp = 1;
	               break;
	  case SDL_MOUSEBUTTONDOWN:
	               if(event.button.button == SDL_BUTTON_LEFT)
		       {
		          if(event.button.x >= 250 && event.button.x <= 550)
			  {
			     if(event.button.y >= 300 && event.button.y <= 400)
			     {
			        FSOUND_Stream_Stop(musique);
				mode_solo(ecran);
				first = 1;
			     }
			     else
			     {
			        if(event.button.y >= 450 && event.button.y <= 550)
				{
			           FSOUND_Stream_Stop(musique);
				   mode_local_serveur(ecran);
				   first = 1;
				}
				else
				{
				   if(event.button.y >= 600 && event.button.y <= 700)
				   {
			              FSOUND_Stream_Stop(musique);
				      mode_local_client(ecran);
				      first = 1;
				   }
				}
			     }
			  }
		       }
		       break;
       }
       
    }
    
    FSOUND_Stream_Stop(musique);
    FSOUND_Stream_Close(musique);
    FSOUND_Close();
    SDL_FreeSurface(menu);
    SDL_FreeSurface(ecran);
    TTF_Quit();
    SDL_Quit();
    return(EXIT_SUCCESS);
      
}

int mode_solo(SDL_Surface * fenetre)
{
   int rep_tir_cpu;
   int i,x,y;
   int * permit_tir;
   var_game_t * var;

   init_var(1,&var);
   var->ecran = fenetre;
   SDL_BlitSurface(var->background,NULL,var->ecran,&(var->position_back));
   SDL_Flip(var->ecran);
   permit_tir = (int *)malloc(100*sizeof(int));
   if(permit_tir == NULL)
   {
      fprintf(var->log_erreur,"erreur dans l'allocation de permit_tir\n");
      exit_err(var);
   }
   for(i=0;i<100;i++)
      permit_tir[i] = i;
   
   placement_alea(var);

   message_box(var,"placement de vos bateau");
   placement_hum(var);

   affich_score(var,0);
   affich_score(var,1);
   
   while(var->remain_bat_cpu != 0 && var->remain_bat_hum != 0)
   {
      message_box(var,"A vous de tirer");
      var->z = tir_humain(var);
      var->mer_cible_hum[var->z] = reponse_tir(var->z,1,var);
      if(var->mer_cible_hum[var->z] == 2)
      {
         (var->remain_bat_cpu)--;
	 affich_score(var,1);
      }
      SDL_Delay(2500);
      if(var->remain_bat_hum != 0)
      {
         message_box(var,"Au CPU de tirer");
         var->z = tir_alea(permit_tir, &rep_tir_cpu, var);
         if(rep_tir_cpu == 2)
            affich_score(var,0);
      }
      SDL_Delay(2500);
   }
   if(var->remain_bat_cpu == 0)
   {
      message_box(var,"Bravo vous avez gagne(e)");
      FSOUND_PlaySound(FSOUND_FREE,var->gagne);
   }
   else
   {
      message_box(var,"Dommage vous avez perdu(e)");
      FSOUND_PlaySound(FSOUND_FREE,var->perdu);
   }
   
   SDL_Delay(3000);
   message_box(var,"le menu s'affichera dans 5s");
   SDL_Delay(5000);
   fin(var,0);
   return(EXIT_SUCCESS);
}

int mode_local_serveur(SDL_Surface * fenetre)
{
  /*declaration des variables*/
   var_game_t * var;
   void * temp;
   long ready = 1;
   long deb;
   pthread_t thread;
   SDL_Event event;

   /*ouverture du module socket sous windows*/
   #ifdef __WIN32__
      WSADATA WSAData;
      WSAStartup(MAKEWORD(2,2), &WSAData);
   #endif


   /*allocation des ressources*/
   init_var(0,&var);

   var->ecran = fenetre;
   SDL_BlitSurface(var->background,NULL,var->ecran,&(var->position_back));
   SDL_Flip(var->ecran);
   
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
   message_box(var,"attente de connexion du joueur adverse");
   while(pthread_join(thread,&temp) !=0)  
   {
      SDL_PollEvent(&event);
      if(event.type == SDL_QUIT)
         fin(var,1);
      SDL_Delay(20);
   }
   pthread_create(&thread, NULL,(void *)recept_rdy,var);

   placement_hum(var);

   ready = htonl(1);
   if(send(var->sock_client,&ready,sizeof(long),0) == -1)
   {
      fprintf(var->log_erreur,"Erreur envoie ready\n");
      fclose(var->log_erreur);
      exit(EXIT_FAILURE);
   }
   
   message_box(var,"placement des bateaux du joueur adverse");
   while(pthread_join(thread,&temp) !=0)  
   {
      SDL_PollEvent(&event);
      if(event.type == SDL_QUIT)
         fin(var,1);
      SDL_Delay(20);
   }

   deb = htonl(deb);
   if(send(var->sock_client,&deb,sizeof(long),0) == -1)
   {
       fprintf(var->log_erreur,"Erreur envoie deb\n");
       fclose(var->log_erreur);
       exit(EXIT_FAILURE);
   }
   deb = ntohl(deb);
   
   affich_score(var,0);
   affich_score(var,1);
   
   while(var->remain_bat_cpu != 0 && var->remain_bat_hum != 0)
   {

      if(deb == 1)
      {
         message_box(var,"A vous de tirer !");
         var->z = tir_humain(var);
         envoi_coord(var);

         pthread_create(&thread, NULL,(void *)recept_rep,var);
         message_box(var,"attente reponse joueur adverse");
	 while(pthread_join(thread,&temp) !=0)  
         {
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT)
               fin(var,1);
            SDL_Delay(20);
         }
      }

      pthread_create(&thread, NULL,(void *)recept_coord,var);
      /*gestion du rafraichissement SDL pas d'actualité dans cette version*/
      message_box(var,"attente du tir du joueur adverse");
      while(pthread_join(thread,&temp) !=0)  
      {
         SDL_PollEvent(&event);
         if(event.type == SDL_QUIT)
            fin(var,1);
         SDL_Delay(20);
      }

      if(deb != 1)
      {
         message_box(var,"A vous de tirer !");
         var->z = tir_humain(var);
         envoi_coord(var);

         pthread_create(&thread, NULL,(void *)recept_rep,var);
         /*gestion du rafraichissement SDL pas d'actualité dans cette version*/
        message_box(var,"attente reponse joueur adverse\n");
        while(pthread_join(thread,&temp) !=0)  
        {
           SDL_PollEvent(&event);
           if(event.type == SDL_QUIT)
              fin(var,1);
           SDL_Delay(20);
        }

      }
   }
   if(var->remain_bat_cpu == 0)
   {
      message_box(var,"Bravo vous avez gagne(e)");
      FSOUND_PlaySound(FSOUND_FREE,var->gagne);
   }
   else
   {
      message_box(var,"Dommage vous avez perdu(e)");
      FSOUND_PlaySound(FSOUND_FREE,var->perdu);
   }
   
   SDL_Delay(3000);
   message_box(var,"le menu s'affichera dans 5s");
   SDL_Delay(5000);
   

   close_sock(var, 1);
   fin(var,0);
   
   #ifdef __WIN32__
      WSACleanup();
   #endif

   return(EXIT_SUCCESS);
}

int mode_local_client(SDL_Surface * fenetre)
{
   /*declaration des variables*/
   var_game_t * var;
   void * temp;
   long ready = 1;
   long deb;
   char * adresse_ip;
   pthread_t thread;
   SDL_Event event;

   /*ouverture du module socket sous windows*/
   #ifdef __WIN32__
      WSADATA WSAData;
      WSAStartup(MAKEWORD(2,2), &WSAData);
   #endif


   /*allocation des ressources*/
   init_var(0,&var);

   var->ecran = fenetre;
   SDL_BlitSurface(var->background,NULL,var->ecran,&(var->position_back));
   SDL_Flip(var->ecran);
   do
   {
      
      adresse_ip = read_adress(var);
      /*creation de la socket*/
      var->sock_client=socket(AF_INET, SOCK_STREAM, 0);

      /*configuration de la connexion*/
      var->sin_client.sin_addr.s_addr = inet_addr(adresse_ip);
      var->sin_client.sin_family = AF_INET;
      var->sin_client.sin_port = htons(PORT);
   }while(connect(var->sock_client, (SOCKADDR*) &var->sin_client, sizeof(var->sin_client)) < 0);
   
   SDL_BlitSurface(var->background,NULL,var->ecran,&(var->position_back));
   SDL_Flip(var->ecran);
   message_box(var,"connection effectue");

   
   pthread_create(&thread, NULL,(void *)recept_rdy,var);
   placement_hum(var);

   ready = htonl(1);
   if(send(var->sock_client,&ready,sizeof(long),0) == -1)
   {
      fprintf(var->log_erreur,"Erreur envoie ready\n");
      fclose(var->log_erreur);
      exit(EXIT_FAILURE);
   }

   message_box(var,"placement des bateaux du joueur adverse \n");
   while(pthread_join(thread,&temp) !=0)  
   {
      SDL_PollEvent(&event);
      if(event.type == SDL_QUIT)
         fin(var,1);
      SDL_Delay(20);
   }

   /*reception du jeton de depart*/
   if(recv(var->sock_client, &deb, sizeof(long),0) == -1)
   {
      fprintf(var->log_erreur,"Erreur reception deb\n");
      fclose(var->log_erreur);
      exit(EXIT_FAILURE);
   }
   deb = ntohl(deb);

   affich_score(var,0);
   affich_score(var,1);
   
   while(var->remain_bat_cpu != 0 && var->remain_bat_hum != 0)
   {

      if(deb == 1)
      {
         pthread_create(&thread, NULL,(void *)recept_coord,var);
         /*gestion du rafraichissement SDL pas d'actualité dans cette version*/
         message_box(var,"tir du joueur adverse");
         while(pthread_join(thread,&temp) !=0)  
         {
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT)
               fin(var,1);
            SDL_Delay(20);
         }
      }

      message_box(var,"A vous de tirer !");
      var->z = tir_humain(var);
      envoi_coord(var);

      pthread_create(&thread, NULL,(void *)recept_rep,var);
      /*gestion du rafraichissement SDL pas d'actualité dans cette version*/
      message_box(var,"reponse joueur adverse");
      while(pthread_join(thread,&temp) !=0)  
      {
         SDL_PollEvent(&event);
         if(event.type == SDL_QUIT)
            fin(var,1);
         SDL_Delay(20);
      }
      
      if(deb != 1)
      {
         pthread_create(&thread, NULL,(void *)recept_coord,var);
         /*gestion du rafraichissement SDL pas d'actualité dans cette version*/
         message_box(var,"tir du joueur adverse \n");
         while(pthread_join(thread,&temp) !=0)  
         {
            SDL_PollEvent(&event);
            if(event.type == SDL_QUIT)
            fin(var,1);
            SDL_Delay(20);
         }
      }
   }
   if(var->remain_bat_cpu == 0)
   {
      message_box(var,"Bravo vous avez gagne(e)");
      FSOUND_PlaySound(FSOUND_FREE,var->gagne);
   }
   else
   {
      message_box(var,"Dommage vous avez perdu(e)");
      FSOUND_PlaySound(FSOUND_FREE,var->perdu);
   }
   
   SDL_Delay(3000);
   message_box(var,"le menu s'affichera dans 5s");
   SDL_Delay(5000);
   
   close_sock(var,0);
   fin(var,0);
   #ifdef __WIN32__
      WSACleanup();
   #endif

   return(EXIT_SUCCESS);
}

void attendre()
{
    int continuer = 1;
    SDL_Event event;
 
    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
