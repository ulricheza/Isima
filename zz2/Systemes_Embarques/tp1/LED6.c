/****************************************************************************/
/*  MESNARD Emmanuel                                               ISIMA    */
/*  Septembre 2010                                                          */
/*                                                                          */
/*                  TD 1 -   MultiTaskLAS - Tache 8 : LED6.c                */
/*                           Chenillard ecrit en multi-tache                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

// Ceci est la 8ème tâche réalisée. On attend en premier d'avoir reçu l'information
// (de la tâche d'initialisation) via la mémoire XHEAP que les ports ont bien été
// initialisés. Si ces le cas, après une legère temporisation, on fait clignoter la Led
// N° 6 du port PD.
//  

// Tâche N° 8

#define	HEAP_INIT_COMPLETE	0
  
void Delay(int pTIME)
{ 
  while(pTIME--);
}

void main(void)
{ 
  Delay(0xff);

  // Attend ' le feu vert' de la tâche d'initialisation 

  while(!HeapRdChar(HEAP_INIT_COMPLETE));

  Delay((int)0xff*7/8);

  while(1)
  { 
    PPI_BitOut(PD, 6, ~PPI_BitIn(PD, 6));
    Delay(0xff);
  }
} 