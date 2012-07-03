/*----------------------------------------------------*/
/*Maxime Escourbiac                                   */
/*Fiche de revision sur la FMOD 3.75        */
/*Library Sonore                                           */
/*----------------------------------------------------*/

/*initialisation et liberation de FMOD*/

dans le header
#include <FMOD/fmod.h>

initialisation:
FSOUND_init(44100, 32, 0) //44100: frequence d'echantillonage, 32: nbre de canaux utilisé, 0 flags

Liberation:
FSOUND_Close();


/*Lecture de son court*/

creation de pointeur:
FSOUND_SAMPLE *tir = NULL;

charger le son:
tir = FSOUND_Sample_Load(FSOUND_FREE, "pan.wav", 0, 0, 0); 
/*-----------------------------------------------------------------------------------------------------------------------------*/
/*explications                                                                                                                                                 */
/*FSOUND_FREE: fonction qui retourne le premier emplacement libre  de la "pool"                             */
/*pan.wav: Nom du fichier a charger                                                                                                           */
/*0: caracteristiques du fichier (OSEF pour les formats classique car les infos sont dans le fichier */
/*0: Offset a quel moment on lit la chanson                                                                                                */
/*0: longueur de la chanson                                                                                                                           */
/*----------------------------------------------------------------------------------------------------------------------------*/

jouer le son:
FSOUND_PlaySound(FSOUND_FREE, tir);

libere le son en memoire:
FSOUND_Sample_Free(tir);

/*lecture de musique*/

creation de pointeur:
FSOUND_STREAM *musique = NULL;

charger le son:
musique = FSOUND_Stream_Open("Hype_Home.mp3", 0, 0, 0);
/*-----------------------------------------------------------------------------------------------------------------------------*/
/*explications                                                                                                                                                 */
/*FSOUND_FREE: fonction qui retourne le premier emplacement libre  de la "pool"                             */
/*"Hype_Home.mp3": Nom du fichier a charger                                                                                         */
/*0: caracteristiques du fichier (OSEF pour les formats classique car les infos sont dans le fichier */
/*0: Offset a quel moment on lit la chanson                                                                                                */
/*0: longueur de la chanson                                                                                                                           */
/*----------------------------------------------------------------------------------------------------------------------------*/

jouer la musique:
FSOUND_Stream_Play(FSOUND_FREE, musique);

Modifier le volume:
FSOUND_SetVolume(FSOUND_ALL, 120);
/*FSOUND_ALL : prend en comptte tous les canaux*/
/*volume de 0 a 255*/

Repetition de la chanson:
FSOUND_Stream_SetLoopCount(musique, -1);
/*-1 repetition infini*/
/*Pour que la répétition fonctionne, il faut envoyer FSOUND_LOOP_NORMAL en second paramètre de la fonction FSOUND_Stream_Open.*/

Mettre en pause la chanson:
FSOUND_GetPaused(numero_du_canal) : indique si la chanson jouée sur le canal 
                                    indiqué est en pause ou pas.
                                    Elle renvoie vrai si la chanson est en pause,
 									faux si elle est en train d'être jouée.
FSOUND_SetPaused(numero_du_canal, etat) : met en pause ou réactive la lecture de la
                                          chanson sur le canal indiqué.
										  Envoyez 1 (vrai) pour mettre en pause,

										  0 (faux) pour réactiver la lecture.

Stopper la lecture:
FSOUND_Stream_Stop(musique);

/*lecture de MIDI*/
creation de pointeur:
FMUSIC_MODULE *musique = NULL;

Charger le MIDI:
musique = FMUSIC_LoadSong("mario.mid");

Jouer un midi:
MUSIC_PlaySong(musique);

Test si en pause:
FMUSIC_GetPaused(musique);

met/reactive la pause: 1:met en pause, 0: reactive la chanson
FMUSIC_SetPaused(musique, 1);

Modifier le volume:
FMUSIC_SetMasterVolume(musique, 150);

Stopper la lecture:
FMUSIC_StopSong(musique);

Liberer le midi:
FMUSIC_FreeSong(musique);

&