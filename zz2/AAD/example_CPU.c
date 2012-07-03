#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <sys/resource.h>

/*include du programme*/
#include "graphe.h"
#include "dijkstra.h"

#define SIZE 10000


/* ====================================================================== */
/* return the current time in seconds                                     */
/* ====================================================================== */

double startChrono ()
{
  struct rusage time;

  getrusage(RUSAGE_SELF, &time);
  return (time.ru_utime.tv_sec + 1E-6 * time.ru_utime.tv_usec);
}


/* ====================================================================== */
/* compute the elapsed time in seconds                                    */
/* ====================================================================== */

double stopChrono (double start)
{
  struct rusage time;

  getrusage(RUSAGE_SELF, &time);
  return (time.ru_utime.tv_sec + 1E-6 * time.ru_utime.tv_usec - start);
  
}


/* ====================================================================== */
/* example                                                                */
/* ====================================================================== */

int main (int argc, char * argv[])
{
  int T[SIZE], max, diff;
  double start, stop;
  register int i, j;

  /* keep the starting time */
  start = startChrono ();

  /*algo a gogo*/
  retour * res;
  graphe_t * gr = creation_arbre("DLP_170.dat");
  res = dijkstra(gr,1,170);
  for(int i=0;i<169;i++)
     cout <<"label: " << res[i].label << " prec: " << res[i].prec << " dist: " << res[i].distance << endl;
  /*fin algo*/

  /* stop the chrono */
  stop = stopChrono (start);

  /* display the elapsed time */
  printf("algo: max = %8d in %.2f s\n", max, stop);

  return EXIT_SUCCESS;
}