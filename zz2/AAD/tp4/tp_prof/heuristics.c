/* ======================================================================= */
/* heuristics.c:                                                           */
/* several functions to build a solution                                   */
/*                                                                         */
/* created: nov 8, 2009 by Christophe Duhamel                              */
/* updated: nov 17, 2010 by Christophe Duhamel                             */
/* ======================================================================= */


#include "prototypes.h"


/* ======================================================================= */
/* basic construction: one route for each request                          */
/* ======================================================================= */

void H1_heuristic (Problem * pb, Solution * s)
{
  initSolution (s);
  checkSolution (s, pb);

  /* build one route for each request */
  double distance = 0.0;
  for (uint16 req = 0; req < pb->nb_requests; ++req)
  {
    /* the four nodes involved */
    uint16 out  = s->id_out + req;
    uint16 pic  = pb->requests[req].orig->id;
    uint16 del  = pb->requests[req].dest->id;
    uint16 in   = s->id_in + req;

    /* set the next - prev chain */
    s->next[out] = pic;
    s->next[pic] = del;
    s->next[del] = in;
    s->prev[pic] = out;
    s->prev[del] = pic;
    s->prev[in]  = del;

    /* set the travel time */
    double arrival = 0.0;
    if (arrival < pb->nodes[0].open)
      arrival = pb->nodes[0].open;
    s->arrival[out] = arrival;
    arrival += pb->nodes[0].service;
    arrival += pb->duration[0][pic];
    if (arrival < pb->nodes[pic].open)
      arrival = pb->nodes[pic].open;
    s->arrival[pic] = arrival;
    arrival += pb->nodes[pic].service;
    arrival += pb->duration[pic][del];
    if (arrival < pb->nodes[del].open)
      arrival = pb->nodes[del].open;
    s->arrival[del] = arrival;
    arrival += pb->nodes[del].service;
    arrival += pb->duration[del][0];
    if (arrival < pb->nodes[0].open)
      arrival = pb->nodes[0].open;
    s->arrival[in] = arrival;

    /* compute the latest arrival time */
    double latest = pb->nodes[0].close;
    s->latest[in] = latest;
    latest -= pb->duration[del][0] + pb->nodes[del].service;
    if (latest > pb->nodes[del].close)
      latest = pb->nodes[del].close;
    s->latest[del] = latest;
    latest -= pb->duration[pic][del] + pb->nodes[pic].service;
    if (latest > pb->nodes[pic].close)
      latest = pb->nodes[pic].close;
    s->latest[pic] = latest;
    latest -= pb->duration[0][pic] + pb->nodes[0].service;
    if (latest > pb->nodes[0].close)
      latest = pb->nodes[0].close;
    s->latest[out] = latest;

    /* set the capacity */
    uint16 amount = pb->requests[req].amount;
    s->load[out] = 0;
    s->load[pic] = 0;
    s->load[del] = amount;
    s->load[in]  = 0;

    /* update the number of vehicles used */
    ++s->nb_vehicles;

    /* update the total distance */
    distance += pb->duration[0][pic] +
                pb->duration[pic][del] +
                pb->duration[del][0];
  }

  s->distance = distance;
}


/* ======================================================================= */
/* end of file                                                             */
/* ======================================================================= */
