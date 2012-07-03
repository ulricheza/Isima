/**
 * \file core.c
 * \brief rassemblement des fonctiosn developpees en 1er partie 
 * \author Maxime Escourbiac 
 * \version 1.01
 * \date Jeudi 9 septembre 2010
 *
 * 
 */


#include "core.h"

void placement_hum(var_game_t * var)
{
   int bateau,i,z,za,clic,x,y;
   SDL_Event event;
   SDL_Surface * temp;
   SDL_Rect position;
   za = -1;
   message_box(var,"placement des bateaux");
   for(bateau=0;bateau<5;bateau++)
   {
      var->flotte_hum[bateau].sens = 0;
      do
      {
	 clic = 0;
	 while(!clic)
	 {
        SDL_WaitEvent(&event);
	    switch(event.type)
	    {
	      case SDL_QUIT:
	                   fin(var,1);
			   break;
	      case SDL_MOUSEBUTTONDOWN:
		           switch(event.button.button)
			   {
			     case SDL_BUTTON_RIGHT:
			        var->flotte_hum[bateau].sens = (var->flotte_hum[bateau].sens + 1)%2;
				x = event.button.x;
	                        y = event.button.y;
			        z = conv_placement(x,y);
                                if(z != -1)
                                {
				   trans1D_2D (z,&x,&y);
			           if(placement_valide (x,y,var->flotte_hum[bateau].sens,var->flotte_hum[bateau].taille,var))
			              temp = var->frag_bat;
			           else
			              temp = var->touche;
			           dessin_bateau_precedent(var,bateau);
                                   dessin_bateau_courant(var,bateau,x,y,temp);
			           SDL_Flip(var->ecran);
                                }
				break;
			     case SDL_BUTTON_LEFT:
			        z = conv_placement(event.button.x, event.button.y);
				if(z!=-1)
				{
				   clic = 1;
				   trans1D_2D (z,&x,&y);
				}
				break;
			   }
			   break;
	      case SDL_MOUSEMOTION:
	                   x = event.motion.x;
	                   y = event.motion.y;
			   z = conv_placement(x,y);
			   if(z!=-1 && za != z)
			   {
			      za = z;
			      trans1D_2D (z,&x,&y);
			      if(placement_valide (x,y,var->flotte_hum[bateau].sens,var->flotte_hum[bateau].taille,var)) /*placement valide*/
			         temp = var->frag_bat;
			      else
			         temp = var->touche;
                              dessin_bateau_precedent(var,bateau);
                              dessin_bateau_courant(var,bateau,x,y,temp);
			      SDL_Flip(var->ecran);
			   }
			   break;
	    }
	 }		   
      }while(!placement_valide (x,y,var->flotte_hum[bateau].sens,var->flotte_hum[bateau].taille,var));
  
      dessin_bateau_courant(var,bateau,x,y,var->frag_bat);
      FSOUND_PlaySound(FSOUND_FREE,var->place_sound);
      SDL_Flip(var->ecran);
      var->flotte_hum[bateau].x = x;
      var->flotte_hum[bateau].y = y;
      ;
     /*remplissage de la matrice*/
      z = trans2D_1D(x,y);
      if(var->flotte_hum[bateau].sens == 0)
      {
         for(i=0;i<var->flotte_hum[bateau].taille;i++)
            var->mer_home_hum[z+i] = bateau;
      }
      else
      {
         for(i=0;i<var->flotte_hum[bateau].taille;i++)
            var->mer_home_hum[z+10*i] = bateau;
      }
   }
}

void dessin_bateau_precedent(var_game_t * var, int bateau)
{
   int j,k;
   SDL_Rect position;
   /*on redessine le fond avec les bateaux deja pose*/
   SDL_BlitSurface(var->background,NULL,var->ecran,&(var->position_back));
   message_box(var,"placement des bateaux");
   /*redessinage des bateaux precedemment poses*/
   for(j=0;j<bateau;j++)
   {
      if(var->flotte_hum[j].sens == 0)
      {
         position.y = 350 + 30*var->flotte_hum[j].y;
         for(k=0;k<var->flotte_hum[j].taille;k++)
         {
            position.x = 400 + 30*var->flotte_hum[j].x + 30*k ;
            SDL_BlitSurface(var->frag_bat,NULL,var->ecran,&position);
         }
      }
      else
      {
         position.x = 400 + 30*var->flotte_hum[j].x;
         for(k=0;k<var->flotte_hum[j].taille;k++)
         {
            position.y = 350 + 30*var->flotte_hum[j].y + 30*k ;
            SDL_BlitSurface(var->frag_bat,NULL,var->ecran,&position);
         }
      }
   }
}

void dessin_bateau_courant(var_game_t * var, int bateau,int x, int y,SDL_Surface * temp)
{
   SDL_Rect position;
   int j;
   /*dessin du bateau en cours de placement*/
   if(var->flotte_hum[bateau].sens == 0)
   {
      position.y = 350 + 30*y;
      for(j=0;j<var->flotte_hum[bateau].taille;j++)
      {
         position.x = 400 + 30*x + 30*j ;
         SDL_BlitSurface(temp,NULL,var->ecran,&position);
      }
   }
   else
   {
      position.x = 400 + 30*x;
      for(j=0;j<var->flotte_hum[bateau].taille;j++)
      {
         position.y = 350 + 30*y + 30*j ;
         SDL_BlitSurface(temp,NULL,var->ecran,&position);
      }
   }
}

void exit_err(var_game_t * var)
{
   fclose(var->log_erreur); /*fermeture du fichier log_erreur.txt*/
   exit(EXIT_FAILURE);
}

void init_fic_erreur(var_game_t * var)
{
   struct tm * actual;
   /*recuperation de la date actuelle*/
   time_t actual_temp;
   time(&actual_temp);
   actual = localtime(&actual_temp);

   /*ouverture du fichier d'erreur*/
   var->log_erreur = fopen("log_erreur.txt","a");

   if(var->log_erreur != NULL)
   {
      /*ecriture de l'en-tete du fichier d'erreur*/
      fprintf(var->log_erreur,"-----------------------------------\n");
      fprintf(var->log_erreur,"-----------------------------------\n");
      fprintf(var->log_erreur,"session du %d/ %d/ %d a %d h%d \n",actual->tm_mday, actual->tm_mon+1,(1900 + actual->tm_year),actual->tm_hour,actual->tm_min);
   }
   else
      exit(EXIT_FAILURE);

}

void init_var(int cpu,var_game_t ** var)
{
  int i;

  /*allocation de la structure de variable*/
   *var = (var_game_t *)malloc(sizeof(var_game_t));

   if(*var == NULL)
      exit(EXIT_FAILURE);

   /*affectation des valeurs aux variables de la structure*/
   (*var)->remain_bat_hum = 5;
   (*var)->remain_bat_cpu = 5;

   /*initialisation du fichier d'erreur*/
   init_fic_erreur(*var);

   (*var)->mer_cible_hum = (int *)malloc(100*sizeof(int));
   (*var)->mer_home_hum = (int *)malloc(100*sizeof(int));

   /*correctif 1.1*/
   if( (*var)->mer_cible_hum == NULL || (*var)->mer_home_hum == NULL)
   {
      fprintf((*var)->log_erreur,"Erreur dans l'allocation des mers hum \n");
      exit_err(*var);
   }
   /*fin correctif 1.1*/

   for(i=0;i<100;i++)
   {
      (*var)->mer_cible_hum[i] = -1;
      (*var)->mer_home_hum[i] = -1;
   }

   if(cpu == 1)
   {
      (*var)->mer_home_cpu = (int *)malloc(100*sizeof(int));
      (*var)->mer_cible_cpu = (int *)malloc(100*sizeof(int));
        /*correctif 1.1*/
      if( (*var)->mer_cible_cpu == NULL || (*var)->mer_home_cpu == NULL)
      {
         fprintf((*var)->log_erreur,"Erreur dans l'allocation des mers cpu\n");
         exit_err(*var);
      }
        /*fin correctif 1.1*/
      for(i=0;i<100;i++)
      {
         (*var)->mer_cible_cpu[i] = -1;
         (*var)->mer_home_cpu[i] = -1;
      }
   }


   /*initialisation des flottes*/
   /*1er bateau*/
   (*var)->flotte_hum[0].vie = 2;
   (*var)->flotte_cpu[0].vie = 2;
   (*var)->flotte_hum[0].taille = 2;
   (*var)->flotte_cpu[0].taille = 2;

   /*2ieme bateau*/
   (*var)->flotte_hum[1].vie = 3;
   (*var)->flotte_cpu[1].vie = 3;
   (*var)->flotte_hum[1].taille = 3;
   (*var)->flotte_cpu[1].taille = 3;

   /*3ieme bateau*/
   (*var)->flotte_hum[2].vie = 3;
   (*var)->flotte_cpu[2].vie = 3;
   (*var)->flotte_hum[2].taille = 3;
   (*var)->flotte_cpu[2].taille = 3;

   /*4ieme bateau*/
   (*var)->flotte_hum[3].vie = 4;
   (*var)->flotte_cpu[3].vie = 4;
   (*var)->flotte_hum[3].taille = 4;
   (*var)->flotte_cpu[3].taille = 4;

   /*5ieme bateau*/
   (*var)->flotte_hum[4].vie = 6;
   (*var)->flotte_cpu[4].vie = 6;
   (*var)->flotte_hum[4].taille = 6;
   (*var)->flotte_cpu[4].taille = 6;

   /*init parametre son*/
   (*var)->mute = 1;
   #ifdef __WIN32__
      (*var)->tir_sound = FSOUND_Sample_Load(FSOUND_FREE, ".\\son\\tir.mp3", 0, 0, 0);
   #else
      (*var)->tir_sound = FSOUND_Sample_Load(FSOUND_FREE, "./son/tir.mp3", 0, 0, 0);
   #endif
   if((*var)->tir_sound == NULL)
   {
      fprintf((*var)->log_erreur,"fichier musique tir non trouve\n");
      exit_err(*var);
   }
   
   #ifdef __WIN32__
      (*var)->rate_sound = FSOUND_Sample_Load(FSOUND_FREE, ".\\son\\rate.wav", 0, 0, 0);
   #else
      (*var)->rate_sound = FSOUND_Sample_Load(FSOUND_FREE, "./son/rate.wav", 0, 0, 0);
   #endif
   if((*var)->rate_sound == NULL)
   {
      fprintf((*var)->log_erreur,"fichier musique rate non trouve\n");
      exit_err(*var);
   }
   
   #ifdef __WIN32__
      (*var)->coule_sound = FSOUND_Sample_Load(FSOUND_FREE, ".\\son\\coule.wav", 0, 0, 0);
   #else
      (*var)->coule_sound = FSOUND_Sample_Load(FSOUND_FREE, "./son/coule.wav", 0, 0, 0);
   #endif
   if((*var)->coule_sound == NULL)
   {
      fprintf((*var)->log_erreur,"fichier musique coule non trouve\n");
      exit_err(*var);
   }
   
   #ifdef __WIN32__
      (*var)->touche_sound = FSOUND_Sample_Load(FSOUND_FREE, ".\\son\\touche.wav", 0, 0, 0);
   #else
      (*var)->touche_sound = FSOUND_Sample_Load(FSOUND_FREE, "./son/touche.wav", 0, 0, 0);
   #endif
   if((*var)->touche_sound == NULL)
   {
      fprintf((*var)->log_erreur,"fichier musique touche non trouve\n");
      exit_err(*var);
   }
   
   #ifdef __WIN32__
      (*var)->place_sound = FSOUND_Sample_Load(FSOUND_FREE, ".\\son\\place.wav", 0, 0, 0);
   #else
      (*var)->place_sound = FSOUND_Sample_Load(FSOUND_FREE, "./son/place.wav", 0, 0, 0);
   #endif
   if((*var)->place_sound == NULL)
   {
      fprintf((*var)->log_erreur,"fichier musique place non trouve\n");
      exit_err(*var);
   }
   
   #ifdef __WIN32__
      (*var)->gagne = FSOUND_Sample_Load(FSOUND_FREE, ".\\son\\gagne.wav", 0, 0, 0);
   #else
      (*var)->gagne = FSOUND_Sample_Load(FSOUND_FREE, "./son/gagne.wav", 0, 0, 0);
   #endif
   if((*var)->gagne == NULL)
   {
      fprintf((*var)->log_erreur,"fichier musique gagne non trouve\n");
      exit_err(*var);
   }
   
   #ifdef __WIN32__
   (*var)->perdu = FSOUND_Sample_Load(FSOUND_FREE, ".\\son\\perdu.wav", 0, 0, 0);
   #else
      (*var)->perdu = FSOUND_Sample_Load(FSOUND_FREE, "./son/perdu.wav", 0, 0, 0);
   #endif
   if((*var)->perdu == NULL)
   {
      fprintf((*var)->log_erreur,"fichier musique perdu non trouve\n");
      exit_err(*var);
   }
  
   /*fin init parametre son*/
   /*init parametres video*/
   
   /*allocation des parametres de la message_box*/
   
   #ifdef __WIN32__
      (*var)->message_img = IMG_Load(".\\dessin\\box.jpg");
   #else
      (*var)->message_img = IMG_Load("./dessin/box.jpg");
   #endif
   if((*var)->message_img == NULL)
   {
      fprintf((*var)->log_erreur,"erreur chargement image box\n");
      exit_err(*var);
   }
   (*var)->box_position.x = 100;
   (*var)->box_position.y = 725;
   #ifdef __WIN32__
      (*var)->police_box = TTF_OpenFont(".\\police\\game_over.ttf",80);
   #else
      (*var)->police_box = TTF_OpenFont("./police/game_over.ttf",80);
   #endif
   if((*var)->police_box == NULL)
   {
      fprintf((*var)->log_erreur,"erreur chargement police game_over\n");
      exit_err(*var);
   }
   
   /*allocation des parametres de l'affichage des scores*/
   #ifdef __WIN32__
      (*var)->score = IMG_Load(".\\dessin\\score.jpg");
   #else
      (*var)->score = IMG_Load("./dessin/score.jpg");
   #endif
   if((*var)->score == NULL)
   {
      fprintf((*var)->log_erreur,"erreur chargement image score\n");
      exit_err(*var);
   }
   (*var)->score_position.x = 100;
   #ifdef __WIN32__
      (*var)->police_score = TTF_OpenFont(".\\police\\score.ttf",100);
   #else
      (*var)->police_score = TTF_OpenFont("./police/score.ttf",100);
   #endif
   if((*var)->police_score == NULL)
   {
      fprintf((*var)->log_erreur,"erreur chargement police score\n");
      exit_err(*var);
   }
   
   
   /*allocation des parametre d'affiche des boutons mute/unmute*/
  
   /*mise en pause pour une version suivante
   (*var)->mute_button = IMG_Load("mute.jpg");
   if((*var)->mute_button == NULL)
   {
      fprintf((*var)->log_erreur,"erreur chargement image mute\n");
      exit_err(*var);
   }
   (*var)->unmute_button = IMG_Load("unmute.jpg");
   if((*var)->unmute_button == NULL)
   {
      fprintf((*var)->log_erreur,"erreur chargement image unmute\n");
      exit_err(*var);
   }
   (*var)->mute_position.x = 725;
   (*var)->mute_position.y = 25;
   fonctionnalite a develloper prochaine version*/
   
   /*allocation des affichages rate/touche/fragments_bateau des mers*/
   #ifdef __WIN32__
      (*var)->rate = IMG_Load(".\\dessin\\rate.jpg");
   #else
      (*var)->rate = IMG_Load("./dessin/rate.jpg");
   #endif
   if((*var)->rate == NULL)
   {
      fprintf((*var)->log_erreur,"erreur chargement image rate\n");
      exit_err(*var);
   }
   #ifdef __WIN32__
      (*var)->touche = IMG_Load(".\\dessin\\touche.jpg");
   #else
      (*var)->touche = IMG_Load("./dessin/touche.jpg");
   #endif
   if((*var)->touche == NULL)
   {
      fprintf((*var)->log_erreur,"erreur chargement image touche\n");
      exit_err(*var);
   }
   #ifdef __WIN32__
      (*var)->frag_bat = IMG_Load(".\\dessin\\fragbat.jpg");
   #else
      (*var)->frag_bat = IMG_Load("./dessin/fragbat.jpg");
   #endif
   if((*var)->frag_bat == NULL)
   {
      fprintf((*var)->log_erreur,"erreur chargement image fragment bateau\n");
      exit_err(*var);
   }
   /*allocation fond d'ecran*/
   #ifdef __WIN32__
      (*var)->background = IMG_Load(".\\dessin\\background.jpg");
   #else
      (*var)->background = IMG_Load("./dessin/background.jpg");
   #endif
   if((*var)->background == NULL)
   {
      fprintf((*var)->log_erreur,"erreur chargement image background\n");
      exit_err(*var);
   }
   (*var)->position_back.x = 0;
   (*var)->position_back.y = 0;
   
}

void placement_alea(var_game_t * var)
{
   int * permit_h = (int*) malloc(90*sizeof(int));
   int * permit_v = (int*) malloc(90*sizeof(int));

   int libre_h = 90;
   int libre_v = 90;

   int x=0,y=0,i,j,k,z,bateau;

   srand(time(NULL));

   if( permit_h == NULL || permit_v == NULL)
   {
      fprintf(var->log_erreur,"Erreur dans l'allocation des matrices de permitivite lors du placement alea\n");
      exit_err(var);
   }
   
   /*initialisation des matrices de permitivite*/
   for(i=0;i<90;i++)      /*init permit_v*/
   {
      permit_v[i]= i ;
   }

   for(i=0;i<90;i++)     /*init permit_h*/
   {
      if(x == 9)
      {
         ++y;
         x = 0;
      }
      permit_h[i]= y*10 + x++;
   }
   /*fin initialisation*/


   for(bateau=0;bateau<5;bateau++)
   {
      /*debut placement bateau*/
      /*correctif version 1.1 */

      if(libre_h == 0 || libre_v == 0)
      {
         if(libre_h == 0)
           var->flotte_cpu[bateau].sens=1;
         else
           var->flotte_cpu[bateau].sens=0;
      }
      else
         var->flotte_cpu[bateau].sens = rand()%2;
      /*fin correctif*/

      if(var->flotte_cpu[bateau].sens == 0) /*si sens horizontal*/
      {
         z= choix_alea(permit_h,libre_h);
         trans1D_2D(z,&x,&y);
         var->flotte_cpu[bateau].x = x;
         var->flotte_cpu[bateau].y = y;

         /*positionnement du bateau*/
         for(i=0;i<var->flotte_cpu[bateau].taille;i++)
            var->mer_home_cpu[z+i] = bateau;

         /*mise a jour de la matrice de permitivite */
         /* a cause du placement du bateau          */
         for(i=-1;i<=1;i++)
         {
            for(j=-1;j<=var->flotte_cpu[bateau].taille;j++)
            {
               suppr_point(permit_h,&libre_h,j+x,i+y);
               suppr_point(permit_v,&libre_v,j+x,i+y);
            }
         }
      }
      else /*si sens vertical*/
      {
         z= choix_alea(permit_v,libre_v);
         trans1D_2D(z,&x,&y);
         var->flotte_cpu[bateau].x = x;
         var->flotte_cpu[bateau].y = y;

         /*positionnement du bateau*/
         for(i=0;i<var->flotte_cpu[bateau].taille;i++)
            var->mer_home_cpu[z+10*i] = bateau;

         /*mise a jour de la matrice de permitivite */
         /* a cause du placement du bateau          */
         for(i=-1;i<=1;i++)
         {
            for(j=-1;j<=var->flotte_cpu[bateau].taille;j++)
            {
               suppr_point(permit_h,&libre_h,i+x,j+y);
               suppr_point(permit_v,&libre_v,i+x,j+y);
            }
         }
      }
      /*fin placement bateau*/

      /*debut maj des matrices de permitivites */
      if(bateau != 4)
      {
         /*on supprime les points selon la taille du bateau suivant*/
         /* pour la matrice horizontale*/
         for(j=1;j<var->flotte_cpu[bateau+1].taille;j++)
         {
            for(i=0;i<10;i++)
               suppr_point(permit_h,&libre_h,10-j,i);
         }

         /*pour la matrice verticale*/
         for(i=1;i<var->flotte_cpu[bateau+1].taille;i++)
         {
            for(j=0;j<10;j++)
               suppr_point(permit_v,&libre_v,j,10-i);
         }

         /*MAJ matrices selon les bateaux precedent*/
         for(k=bateau;k>=0;k--)
         {
            if(var->flotte_cpu[k].sens == 0) /*cas bateau horizontal*/
            {
               /*pour la partie horizontale*/
               for(j=2;j<=var->flotte_cpu[bateau+1].taille;j++)
               {
                  for(i=-1;i<=1;i++)
                     suppr_point(permit_h,&libre_h,var->flotte_cpu[k].x -j,var->flotte_cpu[k].y +i);
               }
               /*pour la partie verticale*/
               for(j=-1;j<=var->flotte_cpu[k].taille;j++)
               {
                  for(i=2;i<=var->flotte_cpu[bateau+1].taille;i++)
                     suppr_point(permit_v,&libre_v,var->flotte_cpu[k].x +j,var->flotte_cpu[k].y -i);
               }
            }
            else /*cas bateau vertical*/
            {
               /*pour la partie horizontale*/
               for(j=2;j<=var->flotte_cpu[bateau+1].taille;j++)
               {
                  for(i=-1;i<=var->flotte_cpu[k].taille;i++)
                     suppr_point(permit_h,&libre_h,var->flotte_cpu[k].x-j,var->flotte_cpu[k].y +i);
               }
               /*pour la partie verticale*/
               for(j=-1;j<=1;j++)
               {
                  for(i=2;i<=var->flotte_cpu[bateau+1].taille;i++)
                     suppr_point(permit_v,&libre_v,var->flotte_cpu[k].x +j,var->flotte_cpu[k].y -i);
               }
             }
         } 
       }
   }
   free(permit_v);
   free(permit_h);

}

int placement_valide (int x, int y, int sens,int taille,var_game_t * var)
{
   int valid = 1;
   int i,j,z;
   if(x>=0 && x<10 && y>=0 && y<10) /*test appartenance tete dans grille */ 
   {
       if(sens == 0) 
       {
          if((taille+x)>10) /*test si le bateau rentre dabns la grille*/
             valid=0;
          for(i=-1;i<=1;i++)
          {
             for(j=-1;j<=taille;j++) /*double boucle pour tester ls collisions*/
             {
                if((x+j)>=0 && (x+j)<10 && (y+i)>=0 && (y+i)<10)
                {
                   z= trans2D_1D((x+j),(y+i));
                   if(var->mer_home_hum[z]!= -1)
                      valid=0;
                }
             }
          }
       }
       else
       {
          if((taille+y)>10) /*test si le bateau rentre dabns la grille*/
             valid=0;
          for(j=-1;j<=1;j++)
          {
             for(i=-1;i<=taille;i++) /*double boucle pour tester ls collisions*/
             {
                if((x+j)>=0 && (x+j)<10 && (y+i)>=0 && (y+i)<10)
                {
                   z= trans2D_1D((x+j),(y+i));
                   if(var->mer_home_hum[z]!=-1)
                      valid=0;
                }
             }
          }
       }
   }
   else
      valid = 0;

   return valid;
}

 int trans2D_1D (int x, int y)
 {   
    return (x+10*y);               
 }

 void trans1D_2D (int z, int * x, int * y)
 {
     *y = z/10;
     *x = z - (*y)*10;   
 }

int reponse_tir(int coord ,int provenance,var_game_t * var)
{
   int reponse = 1;
   int x,y,temp;
   SDL_Rect position;
   
   trans1D_2D(coord,&x,&y);
   if(provenance == 0)
   {
      /*calcul de la position du jeton indicateur*/
      position.x = 400 + 30*x;
      position.y = 350 + 30*y;
      
      temp = var->mer_home_hum[coord];
      /*cas tir procenant du cpu ou joueur en reseau*/
      switch (temp)
      {
         case -1 : reponse = 0;              /*tir rate*/
                   var->mer_home_hum[coord]=5;
		   FSOUND_PlaySound(FSOUND_FREE,var->rate_sound);
		   SDL_BlitSurface(var->rate,NULL,var->ecran,&position);
		   message_box(var,"Son tir a echoue");
                   break;
         case 0:
         case 1:
         case 2:
         case 3:
         case 4:  var->mer_home_hum[coord]=6;    /*tir touche*/
		  SDL_BlitSurface(var->touche,NULL,var->ecran,&position);
                  var->flotte_hum[temp].vie = var->flotte_hum[temp].vie -1;
                  if(var->flotte_hum[temp].vie == 0)  /*test si coule*/
		  {
		     reponse = 2;
		     FSOUND_PlaySound(FSOUND_FREE,var->coule_sound);
		     message_box(var,"Son tir a coule un de vos bateau");
		  }
		  else
		  {
		     FSOUND_PlaySound(FSOUND_FREE,var->touche_sound);
		     message_box(var,"Son tir a touche un de vos bateau");
		  }
		  break;
      }
   }
   else
   {
       
       /*calcul de la position du jeton indicateur*/
       position.x = 400 + 30*x;
       position.y = 25 + 30*y;
       
       temp = var->mer_home_cpu[coord];
       /*cas tir provenant joueur humain*/
       switch (var->mer_home_cpu[coord])
       {
         case -1 : reponse = 0;
                   var->mer_home_cpu[coord]=5;
		   SDL_BlitSurface(var->rate,NULL,var->ecran,&position);
		   FSOUND_PlaySound(FSOUND_FREE,var->rate_sound);
		   message_box(var,"Votre tir a echoue");
                   break;
         case 0:
         case 1:
         case 2:
         case 3: 
         case 4:  var->mer_home_cpu[coord]=6;
                  var->flotte_cpu[temp].vie = var->flotte_cpu[temp].vie -1;
		  SDL_BlitSurface(var->touche,NULL,var->ecran,&position);
                  if(var->flotte_cpu[temp].vie == 0)
		  {  
                     reponse = 2;
		     FSOUND_PlaySound(FSOUND_FREE,var->coule_sound);
		     message_box(var,"Votre tir a coule un bateau");
		  }
		  else
		  {
		     FSOUND_PlaySound(FSOUND_FREE,var->touche_sound);
                     message_box(var,"Votre tir a touche un bateau");
		  }
		  break;
       }
   }
   
   SDL_Flip(var->ecran);
   return reponse;
}

int tir_alea(int * permit_tir, int * rep_tir, var_game_t * var)
{
   /*declaration des variables*/
   static int phase = 1;
   static int x1,x2,y1,y2;
   static int poss_p2[4];
   static int rest_p2 = 0;
   static int libre_tir = 100;
   static int first = 1;
   static int sens;

   int z,temp;

   srand(time(NULL));

   switch(phase)
   {
      case 1 :  /*phase 1 : full aleatoire*/
                z = choix_alea(permit_tir,libre_tir);
                trans1D_2D(z,&x1,&y1);
                *rep_tir = reponse_tir(z,0,var);
                var->mer_cible_cpu[z]=*rep_tir;

                if(*rep_tir == 1)
                {
                   phase++;
                   suppr_touch(permit_tir,&libre_tir,x1,y1);
                }

                suppr_point(permit_tir,&libre_tir,x1,y1);

                break;

      case 2:   /*phase 2: Recherche du sens*/
                if(first == 1)
                {
                   if(deja_tire(x1-1,y1,var) == 0)
                   {
                      z = trans2D_1D(x1-1,y1);
                      poss_p2[rest_p2]=z;
                      rest_p2++;
                   }
                   if(deja_tire(x1,y1+1,var) == 0)
                   {
                      z = trans2D_1D(x1,y1+1);
                      poss_p2[rest_p2]=z;
                      rest_p2++;
                   }
                   if(deja_tire(x1+1,y1,var) == 0)
                   {
                      z = trans2D_1D(x1+1,y1);
                      poss_p2[rest_p2]=z;
                      rest_p2++;
                   }
                   if(deja_tire(x1,y1-1,var) == 0)
                   {
                      z = trans2D_1D(x1,y1-1);
                      poss_p2[rest_p2]=z;
                      rest_p2++;
                   }
                   first = 0;
                }

                temp = rand()%rest_p2;
                z = poss_p2[temp];
                trans1D_2D(z,&x2,&y2);
                *rep_tir = reponse_tir(z,0,var);
                var->mer_cible_cpu[z]=*rep_tir;
                rest_p2--;
                poss_p2[temp]=poss_p2[rest_p2];

                if(*rep_tir != 0) /*cas du bateau touche ou coule*/
                {
                   suppr_touch(permit_tir,&libre_tir,x2,y2);

                   if(*rep_tir == 1)
		   {
		     if(x1 == x2)   /*calcul de sens*/
                      {
                         if(y2 == y1+1)
                            sens = 1;
                         else
                            sens = 3;
                      }
                      else
                      {
                         if(x2 == x1+1)
                            sens = 2;
                         else
                            sens = 0;
                      }
                      phase++;
		   }
		   else
                   {
                      phase = 1;
                      suppr_bout(permit_tir,&libre_tir,sens,x2,y2);
                      suppr_bout(permit_tir,&libre_tir,sens,x1,y1);
                      var->remain_bat_hum--;
                   }

                   first = 1;
                   rest_p2 = 0;
                 }

                 suppr_point(permit_tir,&libre_tir,x2,y2);
                 break;

      case 3:
                switch(sens)
                {
                   case 0:
                            x2--;
                            break;
                   case 1:
                            y2++;
                            break;
                   case 2:
                            x2++;
                            break;
                   case 3:
                            y2--;
                            break;
                }
                if(x2>=0 && x2<10 && y2>=0 && y2<10)/*verification de la validit� du point*/
                {
                    z = trans2D_1D(x2,y2);
                    *rep_tir = reponse_tir(z,0,var);
                    var->mer_cible_cpu[z]=*rep_tir;
                    if(*rep_tir == 2) /*coule*/
                    {
                       suppr_touch(permit_tir,&libre_tir,x2,y2);
                       suppr_bout(permit_tir,&libre_tir,sens,x2,y2);
                       suppr_bout(permit_tir,&libre_tir,sens,x1,y1);
                       phase = 1;
                       var->remain_bat_hum--;
                    }
                    else 
                    {
                         if(*rep_tir == 0) /*rate on change de sens*/
                         {
                            sens = (sens+2)%4;
                            phase++;
                         }
                         else
                            suppr_touch(permit_tir,&libre_tir,x2,y2);
                    }
                    suppr_point(permit_tir,&libre_tir,x2,y2);
                 }
                 else /*on se situe a un bord de la mer*/
                 {
                    sens = (sens+2)%4;

                    switch(sens)
                    {
                       case 0:
                               x1--;
                               break;
                       case 1:
                               y1++;
                               break;
                       case 2:
                               x1++;
                               break;
                       case 3:
                               y1--;
                               break;
                     }

                     z= trans2D_1D(x1,y1);
                     *rep_tir = reponse_tir(z,0,var);
                     var->mer_cible_cpu[z]=*rep_tir;

                     if(*rep_tir == 2)
                     {
                        suppr_bout(permit_tir,&libre_tir,sens,x1,y1);
                        phase = 1;
                        var->remain_bat_hum--;
                     }
                     else
                        phase++;

                     suppr_touch(permit_tir,&libre_tir,x1,y1);
                     suppr_point(permit_tir,&libre_tir,x1,y1);
                 }

                 break;

      case 4:
                switch(sens)
                {
                   case 0:
                            x1--;
                            break;
                   case 1:
                            y1++;
                            break;
                   case 2:
                            x1++;
                            break;
                   case 3:
                            y1--;
                            break;
                }

                z = trans2D_1D(x1,y1);
                *rep_tir = reponse_tir(z,0,var);
                var->mer_cible_cpu[z]=*rep_tir;

                if(*rep_tir == 2)
                {
                   suppr_bout(permit_tir,&libre_tir,sens,x1,y1);
                   phase = 1;
                   var->remain_bat_hum = var->remain_bat_hum - 1;
                }

                suppr_touch(permit_tir,&libre_tir,x1,y1);
                suppr_point(permit_tir,&libre_tir,x1,y1);

                break;
   }

   return z;
}

void suppr_touch(int * permit, int * max,int x, int y)
{
   /*on supprime les 4 points diagonaux a la case touchee*/
   suppr_point(permit, max, x+1, y+1);
   suppr_point(permit, max, x-1, y+1);
   suppr_point(permit, max, x+1, y-1);
   suppr_point(permit, max, x-1, y-1);
}


int deja_tire(int x, int y, var_game_t * var)
{
   /*on regarde si la case a deja ete tiree*/
   int rep = 1;
   if( x >= 0 && x<10)
   {  
      if(y >= 0 && y<10)
      {
         int z = trans2D_1D(x,y);
         if(var->mer_cible_cpu[z] == -1)
            rep = 0;
      }
   }
   return rep;
}


void suppr_bout(int * permit, int * max, int sens,int x, int y)
{
   switch(sens)
   {
      case 0:
               x--;
               break;
      case 1:
               y++;
               break;
      case 2:
               x++;
               break;
      case 3:
               y--;
               break;
   }
   suppr_point(permit, max, x, y);

}


int choix_alea(int * permit, int max)
{
   int z;
   static int init = 0;
   if(init==0)
   {
      srand(time(NULL));
      init = 1;
   }
   z = rand()%max;
   z= permit[z];

   return z;
}

void suppr_point(int * permit, int * max, int x, int y)
{
   int i,z;

   if( (x>=0) && (x<10) && (y>=0) && (y<10) )
   {
      z= trans2D_1D(x,y);
      i = 0;
      while(i<*max && permit[i]!=z)
         i++;

      if(i<*max)
      {
         permit[i]=permit[*max-1];
         *max = *max - 1;
      }
   }
}

int tir_humain(var_game_t * var)
{
   int z;
   int valide = 0;
   SDL_Event event;
   
   message_box(var,"A vous de tirer");
   
   while(valide == 0)
   {
      SDL_WaitEvent(&event);
      
      if(event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
      {
         z = transpix_1D(event.button.x,event.button.y);
	 if(z!=-1 && var->mer_cible_hum[z] == -1)
	    valide = 1;
      }
      else
      {
         if(event.type == SDL_QUIT)
	    fin(var,1);
      }
   }
   message_box(var,"Projectile tire");
   FSOUND_PlaySound(FSOUND_FREE,var->tir_sound);
   SDL_Delay(2000);
   return z;
}

void fin(var_game_t * var,int final)
{
   free(var->mer_cible_hum);
   free(var->mer_home_hum);
   if(var->mer_cible_cpu == NULL && var->mer_cible_cpu == NULL)
   {
      free(var->mer_cible_cpu);
      free(var->mer_home_cpu);
   }
      
   fclose(var->log_erreur); /*fermeture du fichier log_erreur.txt*/
   
   SDL_FreeSurface(var->message_img);
   SDL_FreeSurface(var->score);
   SDL_FreeSurface(var->mute_button);
   SDL_FreeSurface(var->unmute_button);
   SDL_FreeSurface(var->rate);
   SDL_FreeSurface(var->touche);
   SDL_FreeSurface(var->frag_bat);
   SDL_FreeSurface(var->background);
   
   TTF_CloseFont(var->police_box);
   TTF_CloseFont(var->police_score);
   
   FSOUND_Sample_Free(var->tir_sound);
   FSOUND_Sample_Free(var->rate_sound);
   FSOUND_Sample_Free(var->touche_sound);
   FSOUND_Sample_Free(var->coule_sound);
   FSOUND_Sample_Free(var->place_sound);
   FSOUND_Sample_Free(var->gagne);
   FSOUND_Sample_Free(var->perdu);
   
   free(var);
   if(final == 1)
      exit(EXIT_SUCCESS);
}

void * thread_evenement(var_game_t * var)
{
   SDL_Event event;
   while(1)
   {
      SDL_PollEvent(&event);
      if(event.type == SDL_QUIT)
         fin(var,1);
      SDL_Delay(30);
      SDL_Flip(var->ecran);
   }
   pthread_exit(NULL);
}
