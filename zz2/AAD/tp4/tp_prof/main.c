/* ======================================================================= */
/* file: main.c                                                            */
/*   read the instance file, then calls the PDPTW algorithms               */
/*                                                                         */
/* created: nov 24, 2009 by Christophe Duhamel                             */
/* ======================================================================= */

#include "prototypes.h"

#include <string.h>
#include <errno.h>

#ifdef __UNIX_TARGET__
  #include <unistd.h>
  #include <sys/stat.h>
#else
  #include <io.h>
  #ifndef F_OK
    #define F_OK 00
  #endif
  #ifndef W_OK
    #define W_OK 02
  #endif
  #ifndef R_OK
    #define R_OK 04
  #endif

  #define access _access
  #define ssize_t int

  #include <sys/stat.h>
  #ifndef S_IFREG
    #define       S_IFREG        0100000   /* regular */
  #endif
  #ifndef S_IFMT
    #define       S_IFMT         0170000   /* file type mask */
  #endif
  #define S_ISREG(m)      (((m) & S_IFMT) == S_IFREG)     /* regular file */
#endif


/* ======================================================================= */
/* global variables to speed up the computation (avoid multiple alloc)     */
/* ======================================================================= */

/* static MinHeap  MINHEAP,  *H; */


/* ======================================================================= */
/* function that initialises the global variables                          */
/* ======================================================================= */

static void initGlobals (Problem * pb)
{
/*
H = &MINHEAP;
  createMinHeap (H, pb->nb_nodes);
*/
}


/* ======================================================================= */
/* function that destroy the global variables                              */
/* ======================================================================= */

static void destroyGlobals (void)
{
/*
destroyMinHeap (H);
*/
}


/* ======================================================================= */
/* utility function to display the right way to call the program           */
/* ======================================================================= */

void printUsage (FILE * stream, const char name[])
{
  fprintf(stream, "\nUsage: %s filename\n", name);
}


/* ======================================================================= */
/* utility function to parse the command line and set options accordingly  */
/* ======================================================================= */

void parseCmdLine (int argc, char * argv[], char filename[64])
{
  struct stat infos;
  int res;

  /* safety check */
  if (argc > 2)
  {
    WARNING("wrong number of arguments");
    printUsage (stderr, argv[0]);
    exit(EXIT_FAILURE);
  }

  /* get the first argument */
  if (argc == 1)
  {
    strncpy(filename, "Data/pdp_100/lc101.txt", 23);
  }
  else if (sscanf(argv[1], "%s", filename) == 0)
  {
    WARNING("wrong first argument");
    printUsage (stderr, argv[0]);
    exit(EXIT_FAILURE);
  }

  /* checking the file */
  if ((res = access(filename, F_OK | R_OK)) != 0)
    ERROR("file %s -> %s", filename, strerror(errno));
  else
  {
    res = stat(filename, &infos);
    if ((res) || (!S_ISREG(infos.st_mode)))
      ERROR("file %s -> not a file", filename);
  }
}


/* ======================================================================= */
/* doQ1: load a graph and display it                                       */
/* ======================================================================= */

void doQ1 (char filename[64], Problem * pb)
{
  double  timer;

  /* read the data file */
  printf("reading file %s", filename);
  fflush(stdout);
  timer = startChrono();
  readData (pb, filename, true);
  timer = stopChrono(timer);
  checkProblem (pb);
  printf(" (%d nodes, %d arcs) %8.3f s\n", pb->nb_nodes, pb->nb_arcs, timer);
  fflush(stdout);

  /* displayProblem (pb); */
}


/* ======================================================================= */
/* doQ2: some constructive heuristics                                      */
/* ======================================================================= */

void doQ2 (Problem * pb)
{
  double  timer;
  Solution sol;

  /* initialization */
  /* initGlobals (pb); */
  createSolution(pb, &sol);

  /* first basic heuristic */
  printf("performing H1 (dummy constructive heuristic 1)");
  fflush(stdout);
  timer = startChrono();
  H1_heuristic (pb, &sol);
  timer = stopChrono(timer);
  printf(" veh = %3u val = %f in %8.3f s\n", sol.nb_vehicles, sol.distance, timer);

  /*dumpSolution(&sol); */
  checkSolution(&sol, pb);
  displaySolution (&sol, false);
  displaySolutionGnuplot (&sol, pb, "H1.sol");

  /* improving it */
  basicOrOpt1(pb, &sol);

  /* memory cleaning */
  /* destroyGlobals (); */
  freeSolution(&sol);
}


/* ======================================================================= */
/* main function: parse the command line and call the routines accordingly */
/* ======================================================================= */

int main (int argc, char * argv[])
{
  char    srcfile[64];
  Problem pb;

  /* display the lastest news */
  TODO("red_cpt is not computed correctly in reduction()");
  TODO("finish the code");

  /* parse the command line */
  parseCmdLine (argc, argv, srcfile);

  /* answer the questions */
  doQ1 (srcfile, &pb);
  doQ2 (&pb);


  return (EXIT_SUCCESS);
}


/* ======================================================================= */
/* end of file                                                             */
/* ======================================================================= */
