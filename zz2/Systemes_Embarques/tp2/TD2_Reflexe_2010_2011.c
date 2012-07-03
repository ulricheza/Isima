   /****************************************************************************/
   /*  MESNARD Emmanuel                                               ISIMA    */
   /*  Janvier 2009                                                            */
   /*                                                                          */
   /*                     TD 2 - Mesure de reflexe geree par des IT            */
   /*                                                                          */
   /*                                                                          */
   /****************************************************************************/
   
   // Utilisation des entr�es d'interruption EXINT[7..4] 
   // Ces entr�es sont connect�es sur les boutons poussoirs BP4 .. BP7
   
   
   /****************************************************************************/
   /*  MESNARD Emmanuel                                               ISIMA    */
   /*  Janvier 2009                                                            */
   /*                                                                          */
   /*                Constantes, Variables et Initialisations                  */
   /*                                                                          */
   /****************************************************************************/
   
   // Boutons utilises et les IT associees
   #define BTN_STOP    4
   #define BTN_READY   5
   #define BTN_GAME    6
   #define BTN_MONEY   7
   
   // LEDS (jaunes) utilisees
   #define LED_GAMEOVER 7
   #define LED_READY    6
   #define LED_GO2      5
   #define LED_GO1      4
   #define LED_GO0      3
   #define LED_GAME2    2
   #define LED_GAME1    1
   #define LED_GAME0    0
   
   // Etats internes de la machine d'etats sous jacente
   #define ETAT_INIT                 0
   #define ETAT_ATTENTE_MONEY        1
   #define ETAT_ATTENTE_READY        2
   #define ETAT_ATTENTE_ALEA         3
   #define ETAT_ATTENTE_STOP         4
   
   // Variables globales necessaires au jeu
   unsigned char GameOver;            // Vrai quand le jeu est termine
   unsigned char Ready;               // Etat de la LED ready
   unsigned short Nbre_Partie;        // Nombre de parties jouables (par defaut : 1)
   unsigned int Attente_Aleatoire;    // Delai aleatoire compris entre 1 et 10 secondes
   int Germe_Rand;                    // Germe pour initier le generateur aleatoire
   int Temps_Ecoule;                  // Chronometre, de precision d'environ 1ms
   unsigned char Reflexe;             // Valeur, en ms, du reflexe mesure
   int Etat;                          // Etat courant de la machine d'etats
   
   
   void PPI_Init(void)
   { // Initialisation des ports PA, PB et PC en entr�e
     PPI_SetMode(PA,0xff);  PPI_Out    (PA,0xff);
     PPI_SetMode(PB,0xff);  PPI_Out    (PB,0xff);
     PPI_SetMode(PC,0xff);  PPI_Out    (PC,0xff);
   }
   
   void EXPORT_Init(void)
   { // Initialisation des ports EXPA, EXPB et EXPD en entr�e
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
   /*  Janvier 2009                                                            */
   /*                                                                          */
   /*                             Gestion des Evenements                       */
   /*                                                                          */
   /****************************************************************************/
   
   void IRQ_EVENT_(void)
   { 
     unsigned char EVT;
     
     EVT=GetMsg();    // Lecture d'un evenement
     switch(EVT)
     { 
       case MSG_EXINT4 : // Bouton STOP
            ExintOff(BTN_STOP);      // l'appui sur STOP n'est plus autorise
            DebugPrint("Bouton STOP appuy�\n");
            
            // Extinction de l'affichage du GO et du READY
            LED_Y_Off(LED_GO2);LED_Y_Off(LED_GO1);LED_Y_Off(LED_GO0);
            Ready=FALSE;
   
            // Memorisation de la valeur du chronometre
            Reflexe=(unsigned char)Temps_Ecoule;
            
            // Cette valeur va maintenant etre affichee dans la tache de fond,
            // donc, dans la boucle while(1) du programme principal
   
            // Le changement d'etat d'automate differe selon le nombre de parties restantes
            
            if (Nbre_Partie>0) {     // encore des parties
               // Machine d'�tats dans l'�tat n� 2 de l'automate, d'attente de ready
               // ------------------------------------------------------------------
               Etat = ETAT_ATTENTE_READY;
               ExintOn(BTN_READY);   // l'appui sur READY est possible
   
               } else {              // plus de parties
               // Re-initialisation des variables globales
               GameOver = TRUE;
               Nbre_Partie = 0;
   
               // Machine d'�tats dans l'�tat n� 1 de l'automate, d'attente de money
               // ------------------------------------------------------------------
               Etat = ETAT_ATTENTE_MONEY;
               ExintOn(BTN_MONEY);   // seul l'appui sur MONEY est possible
            }
            break;
   
       case MSG_EXINT5 : // Bouton READY
            ExintOff(BTN_READY);     // l'appui sur READY n'est plus autorise
            ExintOff(BTN_GAME);      // ni sur GAME de modif du nombre de parties
            DebugPrint("Bouton READY appuy�\n");      
            Ready=TRUE;              // Allumage du voyant de controle READY
            
            Nbre_Partie--;           // D�cr�mente le nombre de parties
            
            Temps_Ecoule = 0;        // Initialisation du chronometre
           
            // Machine d'�tats dans l'�tat n� 3 de l'automate, d'attente al�atoire
            // -------------------------------------------------------------------
            Etat = ETAT_ATTENTE_ALEA;
            // L'attente d'une duree aleatoire ne se fait pas dans l'ISR (JAMAIS)
            // mais dans le programme principal, au milieu de sa boucle while(1)
            // donc, sortie de l'ISR, avec toute les IT non-autorisees.
            break;
   
       case MSG_EXINT6 : // Bouton GAME
            DebugPrint("Bouton GAME appuy�\n");  
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
     
           break;
   
       case MSG_EXINT7 :  // Bouton MONEY 
            ExintOff(BTN_MONEY);     // l'appui sur MONEY n'est plus autorise
            DebugPrint("Bouton MONEY appuy�\n");
   
            Nbre_Partie = 1;         // une partie par defaut, si pas d'appui sur bouton GAME
            srand(Germe_Rand);       // Initialisation des nombres aleatoires
   
            GameOver=FALSE;          // le jeu peut commencer
             
            // Machine d'�tats dans l'�tat n� 2 de l'automate, d'attente de ready
            // ------------------------------------------------------------------
            Etat = ETAT_ATTENTE_READY;
            
            ExintOn(BTN_READY);   // on autorise maintenant soit l'appui sur ready
            ExintOn(BTN_GAME);    // soit l'augmentation du nombre de parties
            break;
            
       default :          // En cas d'IT etranges...
            DebugPrint("\n !!! IT non pr�vue : ");
            DebugCHAR(EVT,DEC);
            DebugPrint("\n");
            break;
     }
   }
   
   /****************************************************************************/
   /*  MESNARD Emmanuel                                               ISIMA    */
   /*  Janvier 2009                                                            */
   /*                                                                          */
   /*                              Programme Principal                         */
   /*                                                                          */
   /****************************************************************************/
   
   void main (void)
   { 
     // Pas encore d'evenements autorises
     EventOff();
     
     // Machine d'�tats dans l'�tat initial, n� 0 de l'automate
     // -------------------------------------------------------
     Etat = ETAT_INIT; 
   
     // Initialisation des variables globales
     GameOver = TRUE;
     Ready = FALSE;
     Nbre_Partie = 0;
     Reflexe = 0;
     Attente_Aleatoire = 0;
     Germe_Rand = 0;
   
     // Initialisation des ports
     DebugClear();
     PPI_Init();  
     EXPORT_Init();
     LED_Y_Init();
     LED_R_Init();
     
     // Initialisation des entrees d'interruption EXINT
     PortSetMode(EXPB,0xf0); // les broches EXINT[7..4] sont en entree
     PortOut(EXPB,0xff);     // entrees configurees en Pull_Up
     
     // Bouton 7 = EXINT.7 = MONEY
     ExintSet(BTN_MONEY,EXINT_LEDGE); // IT lors de l'appui
   
     // Bouton 6 = EXINT.6 = NOMBRE DE PARTIES par bouton GAME
	 ExintSet(BTN_GAME,EXINT_LOW);
     // Bouton 5 = EXINT.5 = READY
     ExintSet(BTN_READY,EXINT_LEDGE);
     // Bouton 4 = EXINT.4 = STOP
     ExintSet(BTN_STOP,EXINT_LEDGE);  // IT lors de l'appui
     ExintOff(BTN_STOP);
    
     ExintOn(BTN_MONEY); // Au depart, seul l'appui du bouton Money est possible
     
     
     // Machine d'�tats dans l'�tat n� 1 de l'automate, d'attente de money
     // ------------------------------------------------------------------
     Etat = ETAT_ATTENTE_MONEY; 
     
     EventOn();  // Autorise les evenements (en fait, uniquement Money)
   
   
     while(1) {  // Boucle principale... d'attente d'evenements !
     
       // Rafraichissement des affichages
       Delay_ms(5); // on laisse souffler un peu les LEDs, car refresh en boucle !
       LED_R(Reflexe);
       LED_Y_Bit(LED_GAMEOVER,GameOver);
       LED_Y_Bit(LED_READY,Ready);
	   LED_Y_Bit(LED_GAME0,Nbre_Partie & 0x01);
	   LED_Y_Bit(LED_GAME1,Nbre_Partie & 0x10);
	   LED_Y_Bit(LED_GAME2,Nbre_Partie & 0x100);
       // Pendant l'attente de demarrage, creation du germe de la s�quence aleatoire
       if (Etat==ETAT_ATTENTE_MONEY) Germe_Rand++;
   
       // Suite de l'etat n� 3, pour l'attente d'une duree aleatoire
       if (Etat==ETAT_ATTENTE_ALEA) {
            // Extinction eventuelle de l'affichage du GO
            LED_Y_Off(LED_GO2);LED_Y_Off(LED_GO1);LED_Y_Off(LED_GO0);
            // Attente aleatoire
            Attente_Aleatoire = 1000+(int)(((double)rand()/pow(2,31))*9000);
            Delay_ms(Attente_Aleatoire);
            // Affichage du GO ! (sur 3 LEDS pour une meilleure lisibilite !)
            LED_Y_On(LED_GO2);LED_Y_On(LED_GO1);LED_Y_On(LED_GO0);
            
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
       }
     }   
   }
     
     
   
