/****************************************************************************/
/*  MESNARD Emmanuel                                               ISIMA    */
/*  Septembre 2010                                                          */
/*                                                                          */
/*                  TD 1 -   MultiTaskLAS - Tache 1 : init.c                */
/*                           Chenillard ecrit en multi-tache                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

// L'adresse 0 de la mémoire RAM XHEAP contient la variable partagée entre toutes les tâches
// Elle est utilisée pour mémoriser le fait que les ports n'ont pas encore étés initialisés (FALSE)
// Lorsque les ports ont été initialisés, cette variable est mise à TRUE pour avertir les autres
// tâches qu'elles peuvent débuter leur traitement

// La durée de la temporisation après la confirmation de l'initialisation des ports sera
// différente pour toutes les taches afin que les clignotements de Leds de chaque
// tâche soient décalés dans le temps pour créer un effet de défilement.

// Tâche N° 1 (initialisation)
  
#define	HEAP_INIT_COMPLETE	0


void PPI_Init(void)
{ // Initialisation des ports PA, PB et PC en entrée
  // 0 : Broche en sortie.
  // 1 : Broche en entrée.

  PPI_SetMode(PA,0xff);  PPI_Out(PA,0xff);
  PPI_SetMode(PB,0xff);  PPI_Out(PB,0xff);
  PPI_SetMode(PC,0xff);  PPI_Out(PC,0xff);

  // Initialisation du port PD en sortie et extinction des Leds de la platine.
  PPI_SetMode(PD,0x00);  PPI_Out    (PD,0xff);
}

void EXPORT_Init(void)
{ // Initialisation des ports EXPA, EXPB et EXPD en entrée
  PortSetMode(EXPA,0xff);
  PortSetMode(EXPB,0xff);
  PortSetMode(EXPD,0xff);
} 

void main(void)
{
  // On indique via un emplacement de la mémoire XHEAP que les ports ne sont pas initialisés
  HeapWrChar(HEAP_INIT_COMPLETE, FALSE);

  // Initialisation des ports  
  PPI_Init();
  EXPORT_Init();
  
  // On indique via un emplacement de la mémoire XHEAP que les ports ont été initialisés
  HeapWrChar(HEAP_INIT_COMPLETE, TRUE);
}
