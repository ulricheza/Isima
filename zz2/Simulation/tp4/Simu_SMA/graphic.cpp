/**
 * \file graphic.cpp
 * \brief fichier d'implementation de la classe Graphic
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 27 Fevrier 2011
 * \version 1.0
 *
 */

#include "graphic.h"
#include "simulator.h"

#include <iostream>
#include <stdlib.h>

using namespace std;


//initialisation des variables statiques

int             Graphic::_largeur = 0;
int             Graphic::_hauteur = 0;
int             Graphic::_time_transition = 0;
Simulator *     Graphic::_simu = NULL;
FSOUND_SAMPLE * Graphic::_ding = NULL;
SDL_Surface *   Graphic::_background = NULL;
SDL_Surface *   Graphic::_arme = NULL;
SDL_Surface *   Graphic::_ecran = NULL;
SDL_Surface *   Graphic::_humain = NULL;
SDL_Surface *   Graphic::_zombie = NULL;

/**
 * \fn  Graphic::Graphic()
 * \brief Constructeur de la classe Graphic
 *
 * Charge les librairies utilises
 */

Graphic::Graphic() {
    //initialisation du son
    FSOUND_Init(44100,32,0);
    //initialisation des graphismes
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
}

/**
 * \fn  Graphic::~Graphic()
 * \brief destructeur de la classe Graphic
 *
 * libere les librairies utilises
 */
Graphic::~Graphic() {
    //liberation du module de son
    FSOUND_Close();
    SDL_Quit();
}

/**
 * \fn void Graphic::Initialisation(int largeur, int hauteur, int time_trans, Simulator * simu)
 * \brief Methode qui initialise les ressources de l'interface graphique
 * \param largeur largeur de la map
 * \param hauteur hauteur de la map
 * \param time_trans temps de transition en ms
 * \param simu pointeur sur l'instance de simulation
 */
void Graphic::Initialisation(int largeur, int hauteur, int time_trans, Simulator * simu)
{
    pthread_t thread;

    _ecran = SDL_SetVideoMode(largeur*TAILLE_PXL,hauteur*TAILLE_PXL,32,SDL_HWSURFACE | SDL_DOUBLEBUF);

    SDL_WM_SetCaption("Simulation SMA ZZ2F2",NULL);

    if(_ecran == NULL)
    {
        exit(EXIT_FAILURE);
    }

    _arme  =  IMG_Load("knife.jpg");
    _humain = IMG_Load("humain.jpg");
    _zombie = IMG_Load("zombie.jpg");
    _background = IMG_Load("background.jpg");

    if( _arme == NULL || _humain == NULL || _zombie == NULL || _background == NULL)
    {
        cerr << "Erreur Image" << endl;
        exit(EXIT_FAILURE);
    }

    _ding = FSOUND_Sample_Load(FSOUND_FREE, "bell.mp3",0,0,0);
    if(_ding == NULL)
    {
        cerr << "Erreur son" << endl;
        exit(EXIT_FAILURE);
    }

    _simu = simu;
    _time_transition = time_trans;

    //lancement du thread pour la fin de la simu
    pthread_create(&thread,NULL,Fermeture,NULL);
}

/**
 * \fn void Graphic::LiberationRessource()
 * \brief Methode qui libere les ressources de l'interface graphique
 */

void Graphic::LiberationRessource()
{
    FSOUND_Sample_Free(_ding);
    SDL_FreeSurface(_arme);
    SDL_FreeSurface(_ecran);
    SDL_FreeSurface(_humain);
    SDL_FreeSurface(_zombie);
    SDL_FreeSurface(_background);
}

/**
 * \fn void Graphic::AfficherArme(int x, int y)
 * \brief Methode qui permet l'affichage d'une arme a une coordonne precise
 * \param x coordonne de l'objet a afficher
 * \param y coordonne de l'objet a afficher
 */
void Graphic::AfficherArme(int x, int y)
{
    SDL_Rect position;
    position.x = TAILLE_PXL*x;
    position.y = TAILLE_PXL*y;
    SDL_BlitSurface(_arme,NULL,_ecran,&position);
}

/**
 * \fn void Graphic::AfficherHumain(int x, int y)
 * \brief Methode qui permet l'affichage d'un humain a une coordonne precise
 * \param x coordonne de l'objet a afficher
 * \param y coordonne de l'objet a afficher
 */
void Graphic::AfficherHumain(int x, int y)
{
    SDL_Rect position;
    position.x = TAILLE_PXL*x;
    position.y = TAILLE_PXL*y;
    SDL_BlitSurface(_humain,NULL,_ecran,&position);
}

/**
 * \fn void Graphic::AfficherZombie(int x, int y)
 * \brief Methode qui permet l'affichage d'un zombie a une coordonne precise
 * \param x coordonne de l'objet a afficher
 * \param y coordonne de l'objet a afficher
 */
void Graphic::AfficherZombie(int x , int y)
{
    SDL_Rect position;
    position.x = TAILLE_PXL*x;
    position.y = TAILLE_PXL*y;
    SDL_BlitSurface(_zombie,NULL,_ecran,&position);
}

/**
 * \fn void Graphic::AfficherBackground()
 * \brief Methode qui permet l'affichage de l'image de fond du simulateur
 */
void Graphic::AfficherBackground()
{
    SDL_Rect position;
    position.x = 0;
    position.y = 0;
    SDL_BlitSurface(_background,NULL,_ecran,&position);
}

/**
 * \fn void Graphic::Transition()
 * \brief Methode qui fixe la transition entre deux tour de simulation
 *
 */

void Graphic::Transition()
{
    FSOUND_PlaySound(FSOUND_FREE,_ding);
    TransitionTourSimulation();
}

/**
 * \fn void Graphic::TransitionTour()
 * \brief Methode qui fixe la transition entre deux action d'un agent
 *
 */
void Graphic::TransitionTour()
{
    SDL_Delay(_time_transition);
}

/**
 * \fn void Graphic::TransitionTourSimulation()
 * \brief Methode qui fixe la transition entre deux agentt
 *
 */
void Graphic::TransitionTourSimulation()
{
    SDL_Delay(_time_transition);
}

/**
 * \fn void Graphic::Rafraichir()
 * \brief Methode qui permet le rafraichissement de l'ecran
 * /!\ specifique a la SDL
 */
void Graphic::Rafraichir()
{
    SDL_Flip(_ecran);
}

/**
 * \fn void * Graphic::Fermeture(void * useless)
 * \brief Methode lance en parallele qui ordonne la fermeture du soft au prochain tour de simulation
 * \param useless inutile dans la methode mais necessaire pour le thread
 *
 */
void * Graphic::Fermeture(void * useless)
{
    SDL_Event event;
    bool continuer = false;
    while(!continuer)
    {
        SDL_PollEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                _simu->FinSimu();
                continuer = true;
                break;
        }
    }
    return NULL;
}