/****************************************************************************/
/*  MESNARD Emmanuel                                               ISIMA    */
/*  Fevrier 2010                                                            */
/*                                                                          */
/*      Bibliotheque de fonctions elementaires sur EasyPIC                  */
/*                                                                          */
/* biblio_etudiant.h                                                PIC     */
/****************************************************************************/

// Constantes generales
#define TRUE   1
#define FALSE  0

unsigned short pow2(unsigned short power);

// Conversion DECimal vers AFFicheur 7 segments à cathode commune
unsigned short DEC2AFF(unsigned short NombreDecimal);

// Initialisation des AFFicheurs 7 segments à cathode commune
void AFF_Init(void);

// Initialisation des ports B et C d'affichage en LEDS JAUNES
void LED_B_Init(void);
void LED_C_Init(void);

// Affichage de 4 caractères sur les afficheurs durant 1 seconde
void AFF(unsigned short V4, unsigned short V3, unsigned short V2, \
         unsigned short V1, unsigned int duree);

// Affichage d'un caractère sur les afficheurs
void AFF1(unsigned short Value);
void AFF2(unsigned short Value);
void AFF3(unsigned short Value);
void AFF4(unsigned short Value);

// Affichage d'une valeur sur les leds
void LED_B(unsigned char Value);
void LED_C(unsigned char Value);

// Allumage ou extection d'un bit donne
void LED_B_Bit(int BitNbr, int Value);
void LED_C_Bit(int BitNbr, int Value);
void LED_B_Bit_On(unsigned char BitNbr);
void LED_B_Bit_Off(unsigned char BitNbr);
void LED_C_Bit_On(unsigned char BitNbr);
void LED_C_Bit_Off(unsigned char BitNbr);

void LED_B_Switch(void);
void LED_C_Switch(void);
