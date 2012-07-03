/****************************************************************************/
/*  MESNARD Emmanuel                                               ISIMA    */
/*  Fevrier 2010                                                            */
/*                                                                          */
/*      Bibliotheque de fonctions elementaires sur EasyPIC                  */
/*                                                                          */
/* biblio_etudiant.c                                                PIC     */
/****************************************************************************/
#include "bibliotheque.h"
#define TRUE  1
#define FALSE 0

// Conversion DECimal vers AFFicheur 7 segments à cathode commune
unsigned short DEC2AFF(unsigned short NombreDecimal) {
 switch (NombreDecimal) {
    case 0 : return 0x3F;
    case 1 : return 0x06;
    case 2 : return 0x5B;
    case 3 : return 0x4F;
    case 4 : return 0x66;
    case 5 : return 0x6D;
    case 6 : return 0x7D;
    case 7 : return 0x07;
    case 8 : return 0x7F;
    case 9 : return 0x6F;
    case 10: return 0x77;//A
    case 11: return 0x7C;//b
    case 12: return 0x58;//c
    case 13: return 0x5E;//d
    case 15: return 0x79;//E
    case 16: return 0x71;//F
    case 17: return 0x78; //t
    case 18: return 0x5C; //o
    case 19: return 0x00; //" "
 }
}

void AFF_Init(void)
{ // Initialisation des afficheurs 7 segments
    TRISA = 0x00;  // Initialisation du port A en sortie
    PORTA = 0;     // A = numéro d'afficheur (entre 1 et 4)
    TRISD = 0x00;  // Initialisation du port D en sortie
    PORTD = 0;     // D = valeur (cathode commune) a afficher
}

void LED_B_Init(void)
{ // Initialisation du port B d'affichage des LEDS JAUNES
    TRISB = 0x00;  // Initialisation du port B en sortie
    PORTB = 0;     // Extinction des Leds
}

void LED_C_Init(void)
{ // Initialisation du port C d'affichage des LEDS JAUNES
    TRISC = 0x00;  // Initialisation du port B en sortie
    PORTC = 0;     // Extinction des Leds
}

// Affichage de 4 digit sur les 4 afficheurs 7 segments durant "duree" secondes
void AFF(unsigned short V4, unsigned short V3, unsigned short V2, \
unsigned short V1,unsigned int duree)
{ // Les valeurs Vi passees en parametre sont les chiffres hexadecimaux
  // exprimes en decimal (donc, de 0 a 15)
  // Pour eviter tout scintillement, rafraichir chaque afficheur toutes
  // les 8 ms (utiliser pour cela la fonction Delay_ms())
  unsigned int elapsedTime;
  unsigned int totalTime;
  elapsedTime = 0;
  totalTime = duree;
  while(elapsedTime < totalTime)
  {
     PORTA = 1;
     PORTD = DEC2AFF(V1);
     Delay_ms(2);
     
     PORTA = 2;
     PORTD = DEC2AFF(V2);
     Delay_ms(2);
     
     PORTA = 4;
     PORTD = DEC2AFF(V3);
     Delay_ms(2);
     
     PORTA = 8;
     PORTD = DEC2AFF(V4);
     
     Delay_ms(2);
     elapsedTime += 8; //4 * 8ms
  }
  PORTD = 0;
}


void AFF1(unsigned short Value)
{ // Affichage sur l'afficheur 1
    PORTA = 1;
    PORTD = Value;
}

void AFF2(unsigned short Value)
{ // Affichage sur l'afficheur 2
    PORTA = 2;
    PORTD = Value;
}

void AFF3(unsigned short Value)
{ // Affichage sur l'afficheur 3
    PORTA = 4;
    PORTD = Value;
}

void AFF4(unsigned short Value)
{ // Affichage sur l'afficheur 4
    PORTA = 8;
    PORTD = Value;
}

void LED_B(unsigned char Value)
{ // Affichage de la valeur sur les leds JAUNES en port B
    PORTB = Value;
}

void LED_C(unsigned char Value)
{ // Affichage de la valeur sur les leds JAUNES en port C
    PORTC = Value;
}

void LED_B_Bit(int BitNbr, int Value)
{
     //Extinction de la diode visee (avec une negation de masque)
     //Mise en place de la valeur avec un "ou" du masque
     PORTB = (PORTB & ~(1<<BitNbr)) | (1<<BitNbr);
}

void LED_C_Bit(int BitNbr, int Value)
{
     //Extinction de la diode visee (avec une negation de masque)
     //Mise en place de la valeur avec un "ou" du masque
     PORTC = (PORTC & ~(1<<BitNbr)) | (1<<BitNbr);
}

void LED_B_Bit_On(unsigned char BitNbr)
{ // Allumage d'un bit des leds en port C
    LED_B_Bit(BitNbr, TRUE);
}

void LED_B_Bit_Off(unsigned char BitNbr)
{ // Extinction d'un bit des leds en port C
    LED_B_Bit(BitNbr, FALSE);
}

void LED_C_Bit_On(unsigned char BitNbr)
{ // Allumage d'un bit des leds en port C
    LED_C_Bit(BitNbr, TRUE);
}

void LED_C_Bit_Off(unsigned char BitNbr)
{ // Extinction d'un bit des leds en port C
    LED_C_Bit(BitNbr, FALSE);
}

void LED_B_Switch(void)
{ // Inversion de la valeur sur les leds JAUNES en port B
  PORTB = ~PORTB;
}

void LED_C_Switch(void)
{ // Inversion de la valeur sur les leds JAUNES en port C
  PORTC = ~PORTC;
}
