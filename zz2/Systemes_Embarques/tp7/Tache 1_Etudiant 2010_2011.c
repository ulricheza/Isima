 
/****************************************************************************/
/*  MESNARD Emmanuel                                               ISIMA    */
/*  Mars 2010                                                               */
/*                                                                          */
/*                  TD 7 - Vitesse de clignotement des LEDS                 */
/*                  controlee par le potentiometre d'entree                 */
/*                                                                          */
/*                  Tache 1 : Gestion de la lecture du potentiometre        */
/*                                                                          */
/****************************************************************************/

//  + Lecture du potentiomètre (Conversion Analogique Numérique ADC0)
//    avec facteur de division de 128 (la valeur lue est initialement sur 10 bits)
//  + Affichage sur les LEDS rouges sur 8 bits
//  + Ecriture de cette valeur dans la Heap a l'aide des primitives synchronisees
//  + Affichage de la valeur décimale dans la fenêtre "On-The-Fly" du PC


/****************************************************************************/
/*  MESNARD Emmanuel                                               ISIMA    */
/*  Mars 2010                                                               */
/*                                                                          */
/*                           Constantes et Initialisations                  */
/*                                                                          */
/****************************************************************************/

// Structure de la Heap
#define     HEAP_ABS    0x50000 // position absolue de la Heap
#define     HEAP_INIT   0       // position relative de la Heap
#define     HEAP_MAX    20      // fin de la zone utilisee sur la Heap
// Definition des boites et des evenements
#define     MsgBox_1    0       // boite a message 1 (donnees sur 2 octets)
#define     Signal_1    2       // adresse du signal logiciel 1 (question 2)
#define     Signal_2    4       // adresse du signal logiciel 2 (question 3)
#define     MsgBox_2    6       // boite a message 2 (donnees sur 2 octets)
#define     RdVBox_1    8       // adresse de la boite de Rendez-vous (question 4)
#define     Semaphore_1 10      // adresse du semaphore 1 (question 5)
#define     Semaphore_2 12      // adresse du semaphore 2 (question 5)


void PPI_Init(void)
{ // Initialisation des ports PA, PB et PC en entrées.
  PPI_SetMode(PA,0xff);  PPI_Out    (PA,0xff);
  PPI_SetMode(PB,0xff);  PPI_Out    (PB,0xff);
  PPI_SetMode(PC,0xff);  PPI_Out    (PC,0xff);
}

void EXPORT_Init(void)
{ // Initialisation des ports EXPA, EXPB et EXPD en entrées (haute impédance).
  PortSetMode(EXPA,0xff);
  PortSetMode(EXPB,0xff);
  PortSetMode(EXPD,0xff);
}

void Delay_ms(int TIMEms)
// Delai mesure en millisecondes
// Valeur mini : 1 ms
// Valeur maxi : 580 400 984 ms, soit 6 jours 17 heures 13 minutes et 20 secondes !
{
  unsigned int boucle;
  if (TIMEms<1) {
     TIMEms = 1;
  } else if (TIMEms>580400984) {
     TIMEms = 580400984;
  }
  boucle = (unsigned int) (TIMEms*74/10);
  while(boucle--);
}

void LED_Y_Init(void)
{ // Initialisation du port PD d'affichage des LEDS * JAUNES *
  PPI_SetMode(PD,0x00);  // Initialisation du port PD en sortie 
  PPI_Out    (PD,0xff);  // Extinction des Leds
}

void LED_R_Init(void)
{ // Initialisation d'un port SPI pour 74HC595 d'affichage des LEDS * ROUGES *
  SpiCreate(0,        // Creation du port SPI n° 0
            PC,       // Utilisation du port XPPI-PC du Rovin
            (1<<4)|3, // MOSI sur PC.3 (poids faible) initialise a 1 (poids fort)
            2,        // MISO sur PC.2 (non utilise ici)
            (0<<4)|1, // SCK sur PC.1 initialise a 0
            (0<<4)|0, // CS sur PC.0 initialise a 0
            SPI_CPHA0|SPI_CPOL0, // Utilisation modes CPHA0 et CPOL0
            SPI_MSBFIRST, // Configuration pour sortie des bits de poids fort en premier
            0);       // Vitesse maximale du port SPI
  SpiOut(0, 0xff); SpiLatch(0, SPI_HIGHPULSE); // Extinction des Leds
}

void LED_Y(unsigned char Value)
{ // Affichage de la valeur sur les leds JAUNES
  PPI_Out    (PD,~Value);  
}

void LED_Y_Bit(unsigned char BitNbr, unsigned char Value)
{ // Allumage ou extinction d'un bit des leds JAUNES
  PPI_BitOut    (PD,BitNbr,~Value);  
}

void LED_Y_On(unsigned char BitNbr)
{ // Allumage d'un bit des leds JAUNES
  PPI_BitOut    (PD,BitNbr,0);  
}

void LED_Y_Off(unsigned char BitNbr)
{ // Extinction d'un bit des leds JAUNES
  PPI_BitOut    (PD,BitNbr,1);  
}

void LED_R(unsigned char Value)
{ // Affichage de la valeur sur les leds ROUGES
  SpiOut(0, ~Value);
  SpiLatch(0, SPI_HIGHPULSE);
}

/****************************************************************************/
/*  MESNARD Emmanuel                                               ISIMA    */
/*  Mars 2010                                                               */
/*                                                                          */
/*                  Primitives de Synchronisation / communication           */
/*                                                                          */
/****************************************************************************/
//                    |//
//                   (o o)
//   +---------oOO----(_)-----------------+
//   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
//   |~~~~  A   C O M P L E T E R   ! ~~~~|
//   |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~|
//   +--------------------oOO-------------+
//                    |__|__|
//                     || ||
//                    ooO Ooo
void XHeap_init(void)
{// Effacement de la premiere partie de la memoire Heap
unsigned int i;
for(i=HEAP_INIT;i<HEAP_MAX;i++) HeapWrShort(i,0);
}

void Signal(unsigned int SignalName)
{// Envoi d'un signal logiciel
	HeapWrShort(SignalName,1);
}

void Wait(unsigned int SignalName)
{// Attente bloquante du signal logiciel
	while(HeapRdShort(SignalName)!=1);
	HeapWrShort(SignalName,0);
}

void Send_1(unsigned int MsgBox, unsigned short MsgData)
{

HeapWrShort(MsgBox,MsgData);
Signal(Signal_1);
Wait(Signal_2);
}

unsigned short Receive_1(unsigned int MsgBox)
{
Signal(Signal_2);
Wait(Signal_1);
return(HeapRdShort(MsgBox));

}



void Send_2(unsigned int MsgBox, unsigned int RdVBox, unsigned short MsgData)
{// Envoi bloquant par RdV d'un message
   HeapWrShort(MsgBox,MsgData);
   HeapWrShort(RdVBox,TRUE);
   while(HeapRdShort(RdVBox)!=FALSE);
}

unsigned short Receive_2(unsigned int MsgBox, unsigned int RdVBox)
{// Reception bloquante par RdV d'un message
   unsigned short RdMsgData;
   while(HeapRdShort(RdVBox)!=TRUE);
   RdMsgData = HeapRdShort(MsgBox);
   HeapWrShort(RdVBox,FALSE);

}


void Init_Sem(unsigned int Sem, short ValeurSem)
{// Initialisation du semaphore
   HeapWrShort(Sem,ValeurSem);
}

void V(unsigned int Sem)
{// Emission du semaphore
   unsigned short CurrentValue;
   CurrentValue = HeapRdShort(Sem);
   HeapWrShort(Sem,CurrentValue+1);
}

void P(unsigned int Sem)
{// Attente du semaphore
   unsigned short CurrentValue;
   HeapWrShort(Sem,CurrentValue-1);
   while(HeapRdShort(sem)<0);
}


// Tache 1 :
// V(Semaphore_1);
// P(Semaphore_2);
// Send_1(MsgBox_1,bal_freq);

// Tache 2
// V(Semaphore_2);
// P(Semaphoe_1);
// Val_Freq = Receive_1(MsgBox);

/****************************************************************************/
/*  MESNARD Emmanuel                                               ISIMA    */
/*  Mars 2010                                                               */
/*                                                                          */
/*                              Programme Principal                         */
/*                                                                          */
/****************************************************************************/


void main(void)
{ 
  unsigned short Val_Freq; // Valeur analogique de la frequence lue sur le potentiometre

  DebugClear();

  // Initialisation des ports
  PPI_Init();  
  EXPORT_Init();
  LED_Y_Init();
  LED_R_Init();

  // Initialisation de la memoire
  XHeap_init();

  // Mise en marche du convertisseur
  AdcSet(ADC0,ADCDF_128);
  AdcOn();

  while(1) { 
    Val_Freq = AdcRead(); // Acquisition de la valeur

    // affichage des 8 MSB (sur 10) de la valeur de la tension sur les LEDS hautes en SPI
    LED_R(Val_Freq>>2);
   
    Send_1(MsgBox_1, Val_Freq);


    // Affichage de la mesure dans la fenêtre 'ON-The-Fly' du mode Débug
    DebugClear();
    DebugPrint("\nValeur clignotement (0 à 1023) : ");
    DebugSHORT(Val_Freq,DEC);
  }
}
