   /****************************************************************************/
   /*  MESNARD Emmanuel                                               ISIMA    */
   /*  Octobre 2010                                                            */
   /*                                                                          */
   /*                     TD 2 - Gestion des LEDS Rouges                       */
   /*                                                                          */
   /*                                                                          */
   /****************************************************************************/
   
    
   
   void PPI_Init(void)
   { // Initialisation des ports PA, PB et PC en entrée
     PPI_SetMode(PA,0xff);  PPI_Out    (PA,0xff);
     PPI_SetMode(PB,0xff);  PPI_Out    (PB,0xff);
     PPI_SetMode(PC,0xff);  PPI_Out    (PC,0xff);
   }
   
   void EXPORT_Init(void)
   { // Initialisation des ports EXPA, EXPB et EXPD en entrée
     PortSetMode(EXPA,0xff);
     PortSetMode(EXPB,0xff);
     PortSetMode(EXPD,0xff);
   }
   
   void Delay_ms(unsigned int TIMEms)
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
   { 
      SpiCreate(0,PC,(0<<4)|3,2,(0<<4)|1,(1<<4)|0,SPI_CPHA0|SPI_CPOL0,SPI_MSBFIRST,0);
      /*cf aide rovin p.160 et plus si affinite*/
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
   { 
      SpiOut(0,~Value);//~ negation bit a bit 
      SpiLatch(0,SPI_HIGHPULSE);
   }
   
   
   /****************************************************************************/
   /*  MESNARD Emmanuel                                               ISIMA    */
   /*  Octobre 2010                                                            */
   /*                                                                          */
   /*                              Programme Principal                         */
   /*                                                                          */
   /****************************************************************************/
   
   void main (void)
   {
     int i;     
     LED_R_Init();
     LED_Y_Init();
     for(i=0;i<=255;i++)
     {
        LED_R((unsigned char) i);
        LED_Y((unsigned char) i);
        Delay_ms(500);
     }
   }
     
   
     
     
   
