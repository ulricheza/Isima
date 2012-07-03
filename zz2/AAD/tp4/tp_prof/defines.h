/* ======================================================================= */
/* file : defines.h                                                        */
/* contains the definition of the structures for the PDPTW                 */
/*                                                                         */
/* created: nov 24, 2009 by Christophe Duhamel                             */
/* updated: nov 17, 2010 by Christophe Duhamel                             */
/* ======================================================================= */

#ifndef __DEFINES_H__
#define __DEFINES_H__

#define __UNIX_TARGET__
#ifdef __UNIX_TARGET__
  #include <stdbool.h>
#else
  #define __func__ __FUNCTION__
  #pragma warning(disable : 4996) /* faire taire Visual Studio sur la demande de remplacement de fonctions standard */
#endif

#include <limits.h>
#include <float.h>


/* NDEBUG must be defined for assert() to be on */
#define NDEBUG

#ifdef NDEBUG
  #define __DEBUG__
  #define __TRACE_CALLS__
#else
  #undef __DEBUG__
  #undef __TRACE_CALLS__
#endif


/* ======================================================================= */
/* general types                                                           */
/* ======================================================================= */

typedef unsigned int      uint16;
typedef unsigned long int uint32;


/* ======================================================================= */
/* general constants                                                       */
/* must be static because external linkage by default in C (even C99)      */
/* ======================================================================= */

static const int    INFINITE  = INT_MAX;
static const double EPSILON   =  1.0E-6;
static const uint16 NOBODY    = UINT_MAX;

static const double NO_ARC    = DBL_MAX; /* INF / 16 */
static const double BAD_ARC   = DBL_MAX * 0.01; /* INF / 100 */


/* ======================================================================= */
/* macros for memory allocation/disallocation                              */
/* ======================================================================= */

#define ALLOCATION(nb,type) ((type*)malloc((nb)*sizeof(type)))
#define FREE(x) if (x!=NULL) free(x)

#define VECTOR_ALLOC(n,type) ((type*)allocV(sizeof(type),n,""))
#define VECTOR_FREE(x) freeV((void*)x,"")

#define MATRIX_ALLOC(m,n,type) ((type**)allocM(sizeof(type*),sizeof(type),m,n,""))
#define MATRIX_FREE(x) freeM((void**)x,"")

#define ERROR(...)   error(__FILE__, __LINE__, __func__, __VA_ARGS__)
#define WARNING(...) warning(__FILE__, __LINE__, __func__, __VA_ARGS__)
#define TODO(...) WARNING("ToDo: "__VA_ARGS__)

#ifdef __DEBUG__
  #define DEBUG(expr) {printf(#expr" = %f\n",(double)(expr));fflush(stdout);}
  #define TRACE(str)  {printf(str"\n");fflush(stdout);}
#else
  #define DEBUG(expr)
  #define TRACE(str)
#endif

#ifdef __TRACE_CALLS__
  #define IN_FCT()  {printf("Entering %s...\n", __func__); fflush(stdout);}
  #define OUT_FCT() {printf("Leaving %s...\n", __func__); fflush(stdout);}
#else
  #define IN_FCT()
  #define OUT_FCT()
#endif

#define UPD_COL(hdl,cpt,max) {if ((cpt)>(max)){fprintf((hdl),"\n");(cpt)=0;}}

#define MAX(a,b) (((a) < (b)) ? (b) : (a))
#define MIN(a,b) (((a) > (b)) ? (b) : (a))


/* ======================================================================= */
/* data structures                                                         */
/* ======================================================================= */

typedef enum {DEPOT = 0, PICKUP, DELIVERY} Type;


struct _Arc;
typedef struct _Node
{
  uint16         id;         /* node id                   */
  uint16         abs;        /* node abscissa             */
  uint16         ord;        /* node ordinate             */
  Type           type;       /* node type                 */
  int            contrib;    /* node contribution         */
  double         service;    /* time to serve the node    */
  double         open;       /* opening time              */
  double         close;      /* closing time              */
  struct _Node * sibling;    /* other node of the request */

  uint16         nb_in;      /* nb incoming arcs          */
  uint16         nb_out;     /* nb outgoing arcs          */
  struct _Arc *  in;         /* incoming arcs             */
  struct _Arc *  out;        /* outgoing arcs             */

  int            flag;       /* flag                      */
} Node;


typedef struct
{
  uint16 id;     /* request id            */
  Node * orig;   /* pickup node           */
  Node * dest;   /* delivery node         */
  uint16 amount; /* quantity to transport */
} Request;


typedef struct _Arc
{
  uint16        id;        /* arc id            */
  Node *        orig;      /* origin node       */
  Node *        dest;      /* destination node  */
  struct _Arc * next_in;   /* next arc for orig */
  struct _Arc * next_out;  /* next arc for dest */
  double        duration;  /* arc cost          */
} Arc;


typedef struct
{
  uint16   size;
  uint16   nb_nodes;
  uint16   id_out;
  uint16   id_in;

  uint16 * prev;        /* previous node in the vehicle tour      */
  uint16 * next;        /* next node in the vehicle tour          */
  double * arrival;     /* vehicle arrival time at the node       */
  uint16 * load;        /* vehicle load when arriving at the node */
  double * latest;      /* largest feasible arrival at the node   */

  uint16   nb_vehicles; /* amount of vehicles in the solution     */
  double   distance;    /* total travelled distance               */
} Solution;


typedef struct
{
  char      name[64];    /* name of the instance        */
  uint16    nb_nodes;    /* nb nodes in the graph       */
  uint16    nb_requests; /* nb nodes in the graph       */
  uint16    nb_arcs;     /* nb arcs in the graph        */
  Node *    nodes;       /* list of nodes               */
  Request * requests;    /* list of requests            */
  Arc *     arcs;        /* list of arcs                */
  double ** duration;    /* travel time matrix          */
  uint16    max_vehicles; /* maximal number of vehicles */
  uint16    capacity;     /* vehicle capacity           */
} Problem;


/* ======================================================================= */
/* prototypes for structures                                               */
/* ======================================================================= */

/* #include "minheap.h" */

#endif


/* ====================================================================== */
/* end of file                                                            */
/* ====================================================================== */
