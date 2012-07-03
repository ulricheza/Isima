/**
 * \file graphisme.c
 * \brief version 1.0 des fonctions graphique du jeu
 * \author Maxime Escourbiac 
 * \version 1.0
 * \date 14 juin 2010
 *
 */


#include "graphisme.h"


int transpix_1D(int x, int y)
{
   int z=-1;
   if( x >= 400 && x <=700)
   {
      if( y >= 25 && y <=325)
      {
         x = (x-400)/30;
         y = (y-25)/30;
         z = trans2D_1D(x,y);
      }
   }
   return z;
}

void affich_score(var_game_t * var, int cpu)
{
    SDL_Surface * numero = NULL;
    SDL_Rect position_chiffre;
    SDL_Color color = {255, 255, 255};
    char chiffre[2];
    
    if(cpu == 0)
    {   
       sprintf(chiffre,"%d",var->remain_bat_hum);
       var->score_position.y = 275;
       position_chiffre.y = 290;
    }     
    else
    {
       sprintf(chiffre,"%d",var->remain_bat_cpu);
       var->score_position.y = 525;
       position_chiffre.y = 540;
    }

    position_chiffre.x = 120;
    /*creation de la surface d'ecriture du score*/

    numero =  TTF_RenderText_Blended(var->police_score,chiffre,color);
    
    /*maj de la surface support puis de la surface de l'ecriture*/
    SDL_BlitSurface(var->score,NULL,var->ecran,&(var->score_position));
    SDL_BlitSurface(numero,NULL,var->ecran,&position_chiffre);
    
    SDL_Flip(var->ecran);
    SDL_FreeSurface(numero);
 }
 
 void message_box(var_game_t * var, char * chaine)
 {
    SDL_Surface * message = NULL;
    SDL_Rect position_mess;
    SDL_Color noir = {0, 0, 0};

    /*creation de la surface d'ecriture du message*/
    message =  TTF_RenderText_Blended(var->police_box,chaine,noir);
    position_mess.x = 125;
    position_mess.y = 725;
    
    /*maj de la surface support puis de la surface de l'ecriture*/
    SDL_BlitSurface(var->message_img,NULL,var->ecran,&(var->box_position));
    SDL_BlitSurface(message,NULL,var->ecran,&position_mess);
    
    SDL_Flip(var->ecran);
    SDL_FreeSurface(message);
 }
 
char * read_adress(var_game_t * var)
{
   /*initialisation des variables*/
   char * adresse_ip;
   int i=0;
   int finp = 0;
   SDL_Surface * fond = NULL;
   SDL_Rect fond_position;
   SDL_Surface * adresse = NULL;
   SDL_Rect adresse_position;
   SDL_Event event;
   TTF_Font * police = TTF_OpenFont("./police/papercuts-2.ttf",50);
   SDL_Color noir = {0,0,0};
   
   adresse_ip = (char *) malloc(20*sizeof(char));
   adresse_ip[0]=0;
   
   fond = IMG_Load("./dessin/adresse_fond.jpg");
   fond_position.x = 250;
   fond_position.y = 250;
   SDL_BlitSurface(fond,NULL,var->ecran,&fond_position);
   
   adresse = TTF_RenderText_Blended(police,adresse_ip,noir);
   adresse_position.x = 260;
   adresse_position.y = 250;
   SDL_BlitSurface(adresse,NULL,var->ecran,&adresse_position);
   SDL_Flip(var->ecran);
   
   while(finp == 0)
   {
      if(i < 16)
      {
         SDL_WaitEvent(&event);
         switch(event.type)
         {
	    case SDL_QUIT :
	                  fin(var,1);
		          break;	       
	    case SDL_KEYDOWN :
/*utilisation des valeurs directes car les SDLK_1, etc... ne fonctionnent pas    */
/*l'utilisateur n'est pas force d'apuyer sur la touche MAJ pour saisir l'adresse */
	                 switch(event.key.keysym.sym)
		         {
			    case 224      :
			    case SDLK_KP0 :
			                  adresse_ip[i++] = '0';
				          break;
			     case 38      :
			     case SDLK_KP1:
			                  adresse_ip[i++] = '1';
				         break;
			     case 233     :
			     case SDLK_KP2:
			                  adresse_ip[i++] = '2';
				          break;
                             case 34      :
			     case SDLK_KP3:
			                  adresse_ip[i++] = '3';
				          break; 
			     case 39      :
			     case SDLK_KP4:
			                  adresse_ip[i++] = '4';
				          break; 
			     case 40      :
			     case SDLK_KP5:
			                  adresse_ip[i++] = '5';
				          break;
			     case 45      :
			     case SDLK_KP6:
			                  adresse_ip[i++] = '6';
				          break;
                             case 232     :
			     case SDLK_KP7:
			                  adresse_ip[i++] = '7';
				          break;
			     case 95      :
			     case SDLK_KP8:
			                  adresse_ip[i++] = '8';				      
				          break;
			     case 231     :
			     case SDLK_KP9:
			                  adresse_ip[i++] = '9';
			       	          break;
			     case 59            :
			     case SDLK_KP_PERIOD:
			                  adresse_ip[i++] = '.';
				          break;
			     case SDLK_BACKSPACE:	 
			     case SDLK_DELETE:
			                 if(i > 0)
					    i--;
			                 break;
			     case SDLK_RETURN:
			     case SDLK_KP_ENTER:
			                 finp = 1;
				         break;
			     default:
			                 break;
		        }
		        adresse_ip[i] = 0;
		        SDL_FreeSurface(adresse);
		        adresse = TTF_RenderText_Blended(police,adresse_ip,noir);
		        SDL_BlitSurface(fond,NULL,var->ecran,&fond_position);
                        SDL_BlitSurface(adresse,NULL,var->ecran,&adresse_position);
		        SDL_Flip(var->ecran);
		        break;
	
	 }
	 
     }
     else
        adresse_ip[--i] = 0; 
   }   
   SDL_FreeSurface(adresse);
   SDL_FreeSurface(fond);
   TTF_CloseFont(police);
   return (adresse_ip);
}

void sound_enable(var_game_t * var)
{
   var->mute = (++var->mute)%2;
   if(var->mute==1)
      SDL_BlitSurface(var->mute_button,NULL,var->ecran,&(var->mute_position));
   else
      SDL_BlitSurface(var->unmute_button,NULL,var->ecran,&(var->mute_position));
   SDL_Flip(var->ecran);
}

int conv_placement(int x, int y)
{
   int z = -1;
   if( x >= 400 && x <=700)
   {
      if( y >= 350 && y <= 650)
      {
         x = (x-400)/30;
         y = (y-350)/30;
         z = trans2D_1D(x, y);
      }
   }
   return(z);
}
