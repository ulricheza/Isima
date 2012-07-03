/****************************************************************************/
/*  MESNARD Emmanuel                                               ISIMA    */
/*  Septembre 2010                                                          */
/*                                                                          */
/*                  TD 1 -   Chenillard LAS - Led Array Shift               */
/*                           evoluant sur les LED du port PD                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/


void PPI_Init(void)
{// Initialisation des ports PA, PB et PC en entrées.
  // 0 : Broche en sortie.
  // 1 : Broche en entrée.

  PPI_SetMode(PA,0xff);
  PPI_Out    (PA,0xff);
  PPI_SetMode(PB,0xff);
  PPI_Out    (PB,0xff);
  PPI_SetMode(PC,0xff);
  PPI_Out    (PC,0xff);

  // Initialisation du port PD en sortie et extinction des Leds de la platine

  PPI_SetMode(PD,0x00);
  PPI_Out    (PD,0xff);
}

void EXPORT_Init(void)
{ // Initialisation des ports EXPA, EXPB et EXPD en entrées (haute impédance)

  PortSetMode(EXPA,0xff);
  PortSetMode(EXPB,0xff);
  PortSetMode(EXPD,0xff);
}

void Delay(unsigned int pDELAYtime)
{ while(pDELAYtime--); // Peu elegant, mais suffisament precis...
}

void main(void)
{ unsigned char iBIT8;
  int i;
   

  PPI_Init();     // Initialisation des ports PA, PB et PC en entrées.
  EXPORT_Init();  // Initialisation des ports EXPA, EXPB et EXPD en entrées
  
  while(1) 
  { PPI_Out(PD,0xff);   // Extinction des LED 
    Delay(0x5f);

    // Décalage des bits (Leds) vers la droite
    for(i=7;i>=0;i--)
    {
        PPI_BitOut(PD,i,0);
        Delay(0x5f);
        PPI_BitOut(PD,i,1);
    }    
    Delay(0x5f);

    PPI_Out(PD,0xff);    
    Delay(0x5f);  

    // Décalage des bits (Leds) vers la gauche
    for(i=0;i<8;i++)
    {
        PPI_BitOut(PD,i,0);
        Delay(0x5f);
        PPI_BitOut(PD,i,1);
    } 
  }
}