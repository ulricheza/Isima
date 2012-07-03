#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>


void pause();
 
int main(int argc, char *argv[])
{
    int i;

    SDL_Init(SDL_INIT_VIDEO); // Initialisation de la SDL

    SDL_Surface * ecran = NULL;

    SDL_Surface * degrade[256] = {NULL};
    ecran = SDL_SetVideoMode(480, 256, 32, SDL_HWSURFACE); // Ouverture de la fenêtre


    SDL_WM_SetCaption("exercise dégradé",NULL);
    SDL_Rect  position; //declaration de la structure pour definir une position
    position.x = 0;
    for(i=0;i<256;i++)
    {
      degrade[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,480,1,32,0,0,0,0); //creation de la surface
      SDL_FillRect(degrade[i],NULL,SDL_MapRGB(ecran->format,i,i,i)); //remplissage de la surface
      position.y = i;
      SDL_BlitSurface(degrade[i],NULL,ecran,&position); //collage de la surface 
    }
    SDL_Flip(ecran);
    pause(); // Mise en pause du programme
    for(i=0;i<256;i++)
       SDL_FreeSurface(degrade[i]);
    SDL_Quit(); // Arrêt de la SDL
    return EXIT_SUCCESS; // Fermeture du programme
}
 
void pause()
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
