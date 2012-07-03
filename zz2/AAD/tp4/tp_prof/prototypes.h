/* ======================================================================= */
/* prototypes.h :                                                          */
/*   prototypes header for the Pickup and Delivery Problem with Time       */
/*   Windows (PDPTW)                                                       */
/*                                                                         */
/* created: nov 24, 2009 by Christophe Duhamel                             */
/* updated: nov 17, 2010 by Christophe Duhamel                             */
/* ======================================================================= */

#ifndef __PROTOTYPE_H__
#define __PROTOTYPE_H__

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#include "defines.h"


/* ======================================================================= */
/* file gestion.c                                                          */
/* ======================================================================= */

void    error       (char const file[], uint16 line, char const func[],
                     char const msg[], ... );
void    warning     (char const file[], uint16 line, char const func[],
                     char const msg[], ... );

void *  allocV      (size_t size, size_t nb_elts, const char name[]);
void    freeV       (void * obj, const char name[]);
void ** allocM      (size_t ptr_size, size_t elt_size, size_t nb_rows,
                     size_t nb_cols, const char name[]);
void    freeM       (void ** obj, const char name[]);

FILE *  openFile    (const char name[], const char mode[]);
void    closeFile   (const char name[], FILE *handle);

double  startChrono (void);
double  stopChrono  (double start);


/* ======================================================================= */
/* file minheap.c                                                          */
/* ======================================================================= */

/*
void   createMinHeap      (MinHeap * heap, uint16 size);
void   destroyMinHeap     (MinHeap * heap);
void   clearMinHeap       (MinHeap * heap);
void   insertMinHeap      (MinHeap * heap, void * data, int key);
void * getMinMinHeap      (MinHeap * heap);
void   decreaseKeyMinHeap (MinHeap * heap, void * data, int key);
int    isEmptyMinHeap     (MinHeap * heap);
void   dumpMinHeap        (MinHeap * heap);
void   checkMinHeap       (MinHeap * heap);
*/

/* ======================================================================= */
/*  file graph.c                                                           */
/* ======================================================================= */

void readData       (Problem * pb, const char name[64], bool red);
void displayProblem (Problem * pb);
void freeProblem    (Problem * pb);
void checkProblem   (Problem * pb);


/* ======================================================================= */
/*  file solution.c                                                        */
/* ======================================================================= */

void createSolution  (Problem * pb, Solution * s);
void freeSolution    (Solution * s);
void initSolution    (Solution * s);
void displaySolution (Solution * s, bool abr);
void dumpSolution    (Solution * s);
void displaySolutionGnuplot (Solution * s, Problem * pb, const char name[64]);
void checkSolution   (Solution * s, Problem * pb);


/* ======================================================================= */
/* file heuristics.c                                                       */
/* ======================================================================= */

void H1_heuristic (Problem * pb, Solution * s);


/* ======================================================================= */
/* file localsearches.c                                                    */
/* ======================================================================= */

void basicOrOpt1 (Problem * pb, Solution * s);


/* ======================================================================= */
/* file metaheuristics.c                                                   */
/* ======================================================================= */


#endif

/* ======================================================================= */
/* end of file                                                             */
/* ======================================================================= */
