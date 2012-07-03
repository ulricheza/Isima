/* ======================================================================= */
/* gestion.c :                                                             */
/* functions for common I/O manipulation, timer, allocation                */
/*                                                                         */
/* created    21/06/1996 by Christophe Duhamel                             */
/* last modif: oct 8, 2010 by Christophe Duhamel                           */
/* ======================================================================= */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "prototypes.h"

#ifdef __UNIX_TARGET__
  #include <sys/time.h>
  #include <sys/resource.h>
#else
  #include <time.h>
  #define CLOCK_DIV (1.0/((double)CLOCKS_PER_SEC))
#endif



/* ======================================================================= */
/* display an error log then exit the program (vararg)                     */
/* ======================================================================= */

void error (char const file[], uint16 line, char const func[], char const msg[], ... )
{
  va_list list;

  fprintf(stderr, "%s (%s, line %d) error: ", file, func, line);

  va_start(list, msg);
  vfprintf(stderr, msg, list);
  va_end(list);

  fprintf(stderr, "\n");
  fflush(stdout);

  exit(EXIT_FAILURE);
}


/* ======================================================================= */
/* display a warning log (vararg)                                          */
/* ======================================================================= */

void warning (char const file[], uint16 line, char const func[], char const msg[], ... )
{
  va_list list;

  fprintf(stderr, "%s (%s, line %d) warning: ", file, func, line);

  va_start(list, msg);
  vprintf(msg, list);
  va_end(list);

  printf("\n");
  fflush(stdout);
}


/* ======================================================================= */
/* generic vector allocation                                               */
/* ======================================================================= */

void * allocV (size_t size, size_t nb_elts, const char name[])
{
  void * block;

  if ((size == 0) || (nb_elts == 0))
    return (NULL);

  block = (void *)calloc(nb_elts, size);
  if (block == NULL)
    error (__FILE__, __LINE__, __func__, "no room for %s (%lu bytes)\n",
      name, (uint32)size * (uint32)nb_elts);

  return (block);
}


/* ======================================================================= */
/* generic vector free                                                     */
/* ======================================================================= */

void freeV (void * obj, const char name[])
{
  if (obj == NULL)
    warning (__FILE__, __LINE__, __func__, "NULL %s pointer\n", name);
  else
    free(obj);
}


/* ======================================================================= */
/* generic matrix allocation                                               */
/* ======================================================================= */

void ** allocM (size_t ptr_size, size_t elt_size, size_t nb_rows, size_t nb_cols,
                const char name[])
{
  void     **vec, *tbl;
  char     *cptr;
  register uint16 i;

  /* args consistency check */
  if ((nb_rows == 0) || (nb_cols == 0) || (ptr_size == 0) || (elt_size == 0))
    return (NULL);

  /* first col memory allocation */
  vec = (void **)calloc(nb_rows, ptr_size);
  if (vec == NULL)
    error (__FILE__, __LINE__, __func__, "no room for %s (%lu bytes)\n",
      name, (uint32)ptr_size * (uint32)nb_rows);

  /* matrix memory allocation */
  tbl = (void *)calloc(nb_rows * nb_cols, elt_size);
  if (tbl == NULL)
  {
    free(vec);
    error (__FILE__, __LINE__, __func__, "no room for %s (%lu bytes)\n",
      name, (uint32)elt_size * (uint32)nb_rows * (uint32)nb_cols);
  }

  /* vector/matrix linking */
  cptr = (char *)tbl;
  for (i = 0; i < nb_rows; i++, cptr += elt_size * nb_cols)
    vec[i] = cptr;

  return (vec);
}


/* ======================================================================= */
/* generic matrix free                                                     */
/* ======================================================================= */

void freeM (void ** obj, const char name[])
{
  if (obj == NULL)
    warning (__FILE__, __LINE__, __func__, "NULL %s pointer\n", name);
  else
  {
    if (*obj == NULL)
      warning (__FILE__, __LINE__, __func__, "NULL %s pointer (2)\n", name);
    else
      free(*obj);
    free(obj);
  }
}


/* ======================================================================= */
/* open a file                                                             */
/* ======================================================================= */

FILE * openFile (const char name[], const char mode[])
{
  FILE * handle;

  if ((handle = fopen(name, mode)) == NULL)
    error (__FILE__, __LINE__, __func__, "unable to open %s\n", name);

  return (handle);
}


/* ======================================================================= */
/* close a file                                                            */
/* ======================================================================= */

void closeFile (const char name[], FILE * handle)
{
  if (fclose(handle) == EOF)
    error (__FILE__, __LINE__, __func__, "unable to close %s\n", name);
}


/* ======================================================================= */
/* launch the chrono: keep the starting time                               */
/* ======================================================================= */

double startChrono (void)
{
#ifdef __UNIX_TARGET__
  struct rusage time;

  getrusage(RUSAGE_SELF, &time);
  return (time.ru_utime.tv_sec + 1E-6 * time.ru_utime.tv_usec);
#else
  return (clock());
#endif
}


/* ======================================================================= */
/* compute the elapsed time since the starting time                        */
/* ======================================================================= */

double stopChrono (double start)
{
  double diff;

#ifdef __UNIX_TARGET__
  struct rusage end;

  getrusage(RUSAGE_SELF, &end);
  diff = end.ru_utime.tv_sec + 1E-6 * end.ru_utime.tv_usec - start;
#else
  diff = ((double)(clock() - start)) * CLOCK_DIV;
#endif

  if (diff < EPSILON)
    return (0.0);
  return (diff);
}


/* ======================================================================= */
/* end of file                                                             */
/* ======================================================================= */
