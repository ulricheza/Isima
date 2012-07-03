 
/****************************************************************************/
/*  MESNARD Emmanuel                                               ISIMA    */
/*  Mars 2010                                                               */
/*                                                                          */
/*                  TD 7 -  Vitesse de clignotement des LEDS                */
/*                  controlee par le potentiometre d'entree                 */
/*                                                                          */
/*                  Tache 2 : Gestion du clignotement des LEDS              */
/*                                                                          */
/****************************************************************************/

//  + Lecture de la vitesse de clignotement dans la Heap a l'aide des primitives synchronisees
//  + Affichage de la valeur lue dans la fenêtre "On-The-Fly" du PC
//  + Gestion du clignotement des LEDS en consequence



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
#define    Signal_1	2
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

void Send_2(unsigned int MsgBox, unsigned short MsgData)
{
}

unsigned short Receive_2(unsigned int MsgBox)
{
}


void Init_Sem(unsigned int Sem, short ValeurSem)
{// Initialisation du semaphore
}

void V(unsigned int Sem)
{// Emission du semaphore
}

void P(unsigned int Sem)
{// Attente du semaphore
}


/****************************************************************************/
/*  MESNARD Emmanuel                                               ISIMA    */
/*  Mars 2010                                                               */
/*                                                                          */
/*                              Programme Principal                         */
/*                                                                          */
/****************************************************************************/

void main(void)
{ 
  unsigned short Val_Freq; // Valeur analogique de la frequence recuperee en Heap
  int led;
  int sens_led;
  int demi_periode;

  // Init des ports
  PPI_Init();
  EXPORT_Init();
  LED_Y_Init();
  LED_R_Init();

  // Init des variables
  led=0;
  sens_led=0;
  demi_periode=0;

  while(1) { 
    Val_Freq = Receive_1(MsgBox_1);

    // Affichage de la valeur lue dans la fenêtre 'ON-The-Fly' du mode Débug
    DebugClear();
    DebugPrint("\nValeur clignotement (0 à 1023) : ");
    DebugSHORT(Val_Freq,DEC);

    //demi_periode = 10 + (int)(1024/(Val_Freq+1));
    demi_periode = 5 + (int)((1024-Val_Freq)/2);
    DebugPrint("\nValeur demi periode : ");
    DebugINT(demi_periode,DEC);

    // Attente correspondante (entre 11 et 1034 ms)
    Delay_ms(demi_periode);

    // Clignotement effectif
    // Gestion pour decaler (d'un cran) l'allumage des LEDS en chenillard
    LED_Y_Off(led); // extinction de la precedente LED
    if (sens_led==0) { 
        led++; // incrementation - decalage droite
        if (led>7) {
          led=6;
          sens_led=1;
        }
    } else {
        led--; // decrementation - decalage gauche
        if (led<0) {
           led=1;
           sens_led=0;
         }
    }
    LED_Y_On(led); // allumage de la nouvelle LED
  }
}