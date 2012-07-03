/**
 * \file graphic.h
 * \brief fichier de declaration de la classe Graphic
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 27 Fevrier 2011
 * \version 1.0
 *
 */

#ifndef _GRAPHIC_H
#define	_GRAPHIC_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <FMOD/fmod.h>
#include <pthread.h>

#include "entite.h"

#define TAILLE_PXL 35

/**
 * \class Graphic
 * \brief Classe gerant l'affichage graphique
 *
 * On a decide de gerer l'affichage par une classe qui contient que des methodes
 * static.
 *
 * On remarquera que l'on aura le code SDL que dans cette classe ce qui permettra
 * de modifier la type d'interface tres facilement
 */
class Graphic {
public:
    Graphic();
    virtual ~Graphic();

    static void Initialisation(int largeur, int hauteur, int time_trans, Simulator * simu);
    static void AfficherHumain(int x, int y);
    static void AfficherArme(int x, int y);
    static void AfficherBackground();
    static void AfficherZombie(int x , int y);
    static void * Fermeture( void * useless);
    static void LiberationRessource();
    static void Transition();
    static void TransitionTour();
    static void TransitionTourSimulation();
    static void Rafraichir();
private:
    static int  _largeur;
    static int  _hauteur;
    static int  _time_transition;
    static Simulator * _simu;
    static FSOUND_SAMPLE * _ding;
    static SDL_Surface * _background;
    static SDL_Surface * _arme;
    static SDL_Surface * _ecran;
    static SDL_Surface * _humain;
    static SDL_Surface * _zombie;

};

#endif	/* _GRAPHIC_H */

