#line 1 "C:/Documents and Settings/septier/Bureau/td4/tp4corig.c"
#line 1 "c:/documents and settings/septier/bureau/td4/bibliotheque.h"
#line 14 "c:/documents and settings/septier/bureau/td4/bibliotheque.h"
unsigned short pow2(unsigned short power);


unsigned short DEC2AFF(unsigned short NombreDecimal);


void AFF_Init(void);


void LED_B_Init(void);
void LED_C_Init(void);
#line 28 "c:/documents and settings/septier/bureau/td4/bibliotheque.h"
void AFF(unsigned short V4, unsigned short V3, unsigned short V2, unsigned short V1, unsigned int duree);


void AFF1(unsigned short Value);
void AFF2(unsigned short Value);
void AFF3(unsigned short Value);
void AFF4(unsigned short Value);


void LED_B(unsigned char Value);
void LED_C(unsigned char Value);


void LED_B_Bit(int BitNbr, int Value);
void LED_C_Bit(int BitNbr, int Value);
void LED_B_Bit_On(unsigned char BitNbr);
void LED_B_Bit_Off(unsigned char BitNbr);
void LED_C_Bit_On(unsigned char BitNbr);
void LED_C_Bit_Off(unsigned char BitNbr);

void LED_B_Switch(void);
void LED_C_Switch(void);
#line 33 "C:/Documents and Settings/septier/Bureau/td4/tp4corig.c"
unsigned short Compteur_Temps;
unsigned short Compteur_Bouton;
unsigned short Numero_Afficheur_Rafraichi;
unsigned short Pas_IT_sur_Maintien;

void interrupt() {
 if (INTCON.TMR0IF) {
 Compteur_Temps++;
 TMR0 = 0x20;
 INTCON.TMR0IF=0;
 INTCON.TMR0IE=1;


 Numero_Afficheur_Rafraichi++;
 switch( Numero_Afficheur_Rafraichi)
 {
 case 4: Numero_Afficheur_Rafraichi=1;
 case 1: AFF1(DEC2AFF(Compteur_Bouton%10));break;
 case 2: AFF2(DEC2AFF((Compteur_Bouton/10)%10));break;
 case 3: AFF3(DEC2AFF((Compteur_Bouton/100))); break;
 }


 }
 if (INTCON.RBIF) {



 Compteur_Bouton++;
 Pas_IT_sur_Maintien = PORTB;
 INTCON.RBIF=0;
 INTCON.RBIE=1;
 }
}

void main() {


 OPTION_REG = 0;
 INTCON=0;



 OPTION_REG |= 0b00000001;
 TMR0=0x20;
 INTCON |= 0x20;
 OPTION_REG.NOT_RBPU = 1;
 TRISB = 0b11110000;
 INTCON |= 0x08;




 Compteur_Temps = 0;
 Compteur_Bouton = 0;
 Numero_Afficheur_Rafraichi=0;


 LED_C_Init();
 LED_C(0xAA);
 AFF_Init();

 INTCON.GIE = 1;
 while(1) {
 if (Compteur_Temps==0xFF) {


 Compteur_Temps = 0;
 }
 }
}
