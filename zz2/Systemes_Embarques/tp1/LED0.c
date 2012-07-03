/****************************************************************************/
/*  MESNARD Emmanuel                                               ISIMA    */
/*  Septembre 2010                                                          */
/*                                                                          */
/*                  TD 1 -   MultiTaskLAS - Tache 2 : LED0.c                */
/*                           Chenillard ecrit en multi-tache                */
/*                                                                          */
/*                                                                          */
/****************************************************************************/

// Ceci est la 2ème tâche réalisée. On attend en premier d'avoir reçu l'information
// (de la tâche d'initialisation) via la mémoire XHEAP que les ports ont bien été
// initialisés. Si ces le cas, après une legère temporisation, on fait clignoter la Led
// N° 0 du port PD.
//  

// Tâche N° 2

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

  Delay((int)0xff*1/8);

  while(1)
  { 
    PPI_BitOut(PD, 0, ~PPI_BitIn(PD, 0));
    Delay(0xff);
  }
}