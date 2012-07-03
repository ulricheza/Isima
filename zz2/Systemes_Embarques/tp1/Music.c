/****************************************************************************/
/*  MESNARD Emmanuel                                               ISIMA    */
/*  Septembre 2010                                                          */
/*                                                                          */
/*                  TD 1 -   Music.c                                        */
/*                           Air musical sur sortie Sound-CHA avec PWM1     */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

// Declaration des fonctions
void PPI_Init(void);
void EXPORT_Init(void);
void Delay(int pTIME);
void Play(char * pMELODY);


void PPI_Init(void)
{ // Initialisation des ports PA, PB et PC en entrée
  // 0 : Broche en sortie.
  // 1 : Broche en entrée..

  PPI_SetMode(PA,0xff);   PPI_Out(PA,0xff);
  PPI_SetMode(PB,0xff);   PPI_Out(PB,0xff);
  PPI_SetMode(PC,0xff);   PPI_Out(PC,0xff);
  // Initialisation du port PD en sortie et extinction des LED de la platine
  PPI_SetMode(PD,0x00);   PPI_Out(PD,0xff);
}

void EXPORT_Init(void)
{ 
  // Initialisation des ports EXPA, EXPB et EXPD en entrée
  PortSetMode(EXPA,0xff);
  PortSetMode(EXPB,0xff);
  PortSetMode(EXPD,0xff);
  PortOut(EXPA,0x00);
  PortOut(EXPB,0x00);
  PortOut(EXPD,0x00);
}

void Delay(int pTIME)
{ 
  while(pTIME--);
}

void Play(char * pMELODY)
{ 
  // Génération de la musique.
  
  unsigned short	iDATA;
  int 		i;
  unsigned int	iTIME;
  unsigned char   iOCTAVE;


  i=0;

  while(1) {
    iDATA = ((unsigned short *)pMELODY)[i++]; // Accès aux données

    if     ((iDATA&0xff)==',')
    { 
      // Génération d'une pause entre les notes musicales si caractère ',' rencontré.
      iTIME = 0x6ff*((iDATA>>8)&0xff - 48); 
      Delay(iTIME*3/4); 
      Pwm1_Off(PWM_CHA); 
      Delay(iTIME/4);      
    }
    else if((iDATA&0xff)=='^')
    { 
      // Test si on change d'octave ?
      // 2^ : Passe sur l'octave 2.
      // 3^ : Passe sur l'octave 3. 
      iOCTAVE = ((iDATA>>8)&0xff - 48); 
    }
    else if(iDATA == 'FF')
    { 
      // Test si on est arrivé à la fin de la mélodie (FF).
      Pwm1_Off(PWM_CHA);
      PortBitOut(EXPC, 5, 0); // Force la sortie buzzer (EXPC.5) au niveau logique '0'
      break;
    }
    else
    { 
      // Il ne s'agit pas d'une pause, ni de la fin de la mélodie
      // ni d'un changement d'octave: donc il s'agit d'une note musicale à jouer.
      Pwm1_On(PWM_CHA); 
      Sound(SOUND_CHA,  // Sélectionne le canal SOUND-CHA.
            iOCTAVE,    // Sélection de l'octave à jouer.
            iDATA);     // Tonalité à générer.
    }
  }
}

// Programme principal
// *******************
void main(void)
{ 
  char *SCHOOL_SONG;

  // Définition de la mélodie
  SCHOOL_SONG = "2^" // On commence sur l'octave 2              
                
"E_2,3^C_2,2^A_2,3^D_4,C_4,2^B_4,3^C_2,2^A_2,3^C_1,2^B_1,A_2,B_4,G_2,A_4,G_2,E_4";


  // Initialisation des ports
  PPI_Init();
  EXPORT_Init();
  Pwm1_Set(PWM_SOUND,0);
  Pwm1_On(PWM_CHA);
  

  // Force la sortie buzzer (EXPC.5) au niveau logique '0' 
  PortBitOut(EXPC, 5, 0); 
  
  // Génération de la mélodie sur le canal SOUND-CHA.
  // Puis forcage la sortie buzzer (EXPC.5) au niveau logique '0'. 
  Play(SCHOOL_SONG);
  PortBitOut(EXPC, 5, 0); 
  
  while(1); // Attente quand la musique est terminee
}