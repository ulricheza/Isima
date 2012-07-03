/****************************************************************************/
/*  MESNARD Emmanuel                                               ISIMA    */
/*  Fevrier 2010                                                            */
/*                                                                          */
/*                  TD 4 -  Gestion des IT et TIMERS sur PIC                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/
// TD installant 2 interruptions : le Timer 0, qui se charge de faire
// clignoter des LEDS sur le PORTC, et les boutons sur le PORTB[7:4]
// Les afficheurs 7 segments comptabilisent le nombre d'IT generees par
// les boutons. Leur affichage est rafraichi par le Timer 0.


// TIMER 0 : Interruption primaire
// Controlee par INTCON, a l'Adresse : 0x0B, 0x8B, 0x10B et 0x18B
//
// INTCON[7:0]=GIE, PEIE, T0IE, INTE, RBIE, T0IF, INTF, RBIF
// GIE : Global Interrupt Enable, pour l'autorisation generale des IT
// T0IE : Autorisation interruption Timer 0
// T0IF : Flag signalant l'IT du Timer 0
//
// OPTION_REG[7:0]=RBPU, INTEDG, T0CS, T0SE, PSA, PS2, PS1, PSO
// a l'Adresse 0x81h, 0x181h
// RBPU : Retrait des Pull-UP sur le PORTB
// T0CS : Clock Source du TMR0 (0 pour source interne = mode Timer)
// T0SE : Source Edge du TMR0 (0 pour front montant)
// PSA : PreScaler Assginment (0 pour affecte le prediviseur au TMR0)
// PS[2:0] : Predivision par 2, 4, ..., 256

#include "bibliotheque.h"

unsigned short Compteur_Temps;  // Subdivision temporelle pour le clignotement
unsigned short Compteur_Bouton; // Compteur du nombre d'appui sur le bouton
unsigned short Numero_Afficheur_Rafraichi; //  Chaque afficheur est rafraichi...
unsigned short Pas_IT_sur_Maintien; // Controle des IT sur niveau bas

void interrupt() {
    if (INTCON.TMR0IF) { // IT provenant du TMR0
        Compteur_Temps++;
        TMR0 = 0x20;
        INITCON.TMR0IF=0;
        INITCON.TMR0IE=1;
        
        // Rafraichissement des afficheurs
        Numero_Afficheur_Rafraichi++;
        switch( Numero_Afficheur_Rafraichi)
        {
         case 4: Numero_Afficheur_Rafraichi=1;
         case 1: AFF1(DEC2AFF(Compteur_Bouton%10));break;
         case 2: AFF2(DEC2AFF((Compteur_Bouton/10)%10));break;
         case 3: AFF3(DEC2AFF((Compteur_Bouton/100))); break;
         }


    }
    if (INTCON.RBIF) {  // IT provenant d'un des boutons RB[7:4], lors
        // 1) d'un appui (front descendant),
        // 2) d'un relachement (front montant)
        // 3) ou d'un maitien  (niveau bas)
        Compteur_Bouton++;
        Pas_IT_sur_Maintien = PORTB;
        INTCON.RBIF=0;
        INTCON.RBIE=1;
    }
}

void main() {

    // Pre-initialisation des registres
    OPTION_REG = 0;
    INTCON=0;

    // Configuration du Timer 0
    // ------------------------
    OPTION_REG |= 0b00000001;
    TMR0=0x20;

    INTCON.TMR0IF=0;
    INITCON.TRM0IE=1;
    
    OPTION_REG.NOT_RBPU = 1;
    TRISB = 0b11110000;
    INTCON.RBIF=0;
    INTCON.TBIE=1;
    


    // Initialisation des variables
    Compteur_Temps = 0;
    Compteur_Bouton = 0;
    Numero_Afficheur_Rafraichi=0;

    // Initialisation des LED de clignotement et de l'afficheur
    LED_C_Init();
    LED_C(0xAA);
    AFF_Init();

                ooO Ooo

    while(1) {
        if (Compteur_Temps==0xFF) {
            //LED_C_Switch(); // Clignotement
            AFF(15,14,13,12,0x8);
            Compteur_Temps = 0;
        }
    }
}
