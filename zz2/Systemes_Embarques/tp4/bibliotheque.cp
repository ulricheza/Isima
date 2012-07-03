#line 1 "C:/Documents and Settings/septier/Bureau/td4/bibliotheque.c"
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
#line 14 "C:/Documents and Settings/septier/Bureau/td4/bibliotheque.c"
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
 case 10: return 0x77;
 case 11: return 0x7C;
 case 12: return 0x58;
 case 13: return 0x5E;
 case 15: return 0x79;
 case 16: return 0x71;
 case 17: return 0x78;
 case 18: return 0x5C;
 case 19: return 0x00;
 }
}

void AFF_Init(void)
{
 TRISA = 0x00;
 PORTA = 0;
 TRISD = 0x00;
 PORTD = 0;
}

void LED_B_Init(void)
{
 TRISB = 0x00;
 PORTB = 0;
}

void LED_C_Init(void)
{
 TRISC = 0x00;
 PORTC = 0;
}
#line 60 "C:/Documents and Settings/septier/Bureau/td4/bibliotheque.c"
void AFF(unsigned short V4, unsigned short V3, unsigned short V2, unsigned short V1,unsigned int duree)
{



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
 elapsedTime += 8;
 }
 PORTD = 0;
}


void AFF1(unsigned short Value)
{
 PORTA = 1;
 PORTD = Value;
}

void AFF2(unsigned short Value)
{
 PORTA = 2;
 PORTD = Value;
}

void AFF3(unsigned short Value)
{
 PORTA = 4;
 PORTD = Value;
}

void AFF4(unsigned short Value)
{
 PORTA = 8;
 PORTD = Value;
}

void LED_B(unsigned char Value)
{
 PORTB = Value;
}

void LED_C(unsigned char Value)
{
 PORTC = Value;
}

void LED_B_Bit(int BitNbr, int Value)
{


 PORTB = (PORTB & ~(1<<BitNbr)) | (1<<BitNbr);
}

void LED_C_Bit(int BitNbr, int Value)
{


 PORTC = (PORTC & ~(1<<BitNbr)) | (1<<BitNbr);
}

void LED_B_Bit_On(unsigned char BitNbr)
{
 LED_B_Bit(BitNbr,  1 );
}

void LED_B_Bit_Off(unsigned char BitNbr)
{
 LED_B_Bit(BitNbr,  0 );
}

void LED_C_Bit_On(unsigned char BitNbr)
{
 LED_C_Bit(BitNbr,  1 );
}

void LED_C_Bit_Off(unsigned char BitNbr)
{
 LED_C_Bit(BitNbr,  0 );
}

void LED_B_Switch(void)
{
 PORTB = ~PORTB;
}

void LED_C_Switch(void)
{
 PORTC = ~PORTC;
}
