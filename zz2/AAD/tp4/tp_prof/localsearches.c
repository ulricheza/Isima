/* ======================================================================= */
/* localsearches.c:                                                        */
/* several functions to improve a solution                                 */
/*                                                                         */
/* created: nov 8, 2009 by Christophe Duhamel                              */
/* updated: nov 17, 2010 by Christophe Duhamel                             */
/* ======================================================================= */


#include "prototypes.h"


/* ======================================================================= */
/* ======================================================================= */

void basicOrOpt1 (Problem * pb, Solution * s)
{
  Node * depot = pb->nodes;
  double duration_cost;
  /* double vehicle_cost; */
  double best_cost;
  Node * best_optr, * best_dptr, * best_voisinptr;
  bool   best_red;

  /* initialization */
  best_cost = NO_ARC;
  best_optr = best_voisinptr = NULL;
  best_red = false;

  /* scan all the requests */
  for (uint16 req = 0; req < pb->nb_requests; ++req)
  {
    Node * optr = pb->requests[req].orig;
    Node * dptr = pb->requests[req].dest;
    bool red = false;

    /* compute the removal cost */
    Node * prevoptr = depot;
    Node * nextdptr = depot;

    if (s->prev[optr->id] < s->id_out)
      prevoptr = pb->nodes + s->prev[optr->id];
    if (s->next[dptr->id] < s->id_out)
      nextdptr = pb->nodes + s->next[dptr->id];

    if (s->next[optr->id] == dptr->id)
    {
      /* simple case: d is just after o */
      duration_cost = pb->duration[prevoptr->id][nextdptr->id] - pb->duration[prevoptr->id][optr->id] -
                      pb->duration[dptr->id][nextdptr->id];

      /* check if the request is the only one -> remove the tour */
      red = (prevoptr == nextdptr);
    }
    else
    {
      /* general case: o ... d */
      Node * nextoptr = pb->nodes + s->next[optr->id];
      Node * prevdptr = pb->nodes + s->prev[dptr->id];
      duration_cost = pb->duration[prevoptr->id][nextoptr->id] + pb->duration[prevdptr->id][nextdptr->id] -
                      pb->duration[prevoptr->id][optr->id] - pb->duration[optr->id][nextoptr->id] -
                      pb->duration[prevdptr->id][dptr->id] - pb->duration[dptr->id][nextdptr->id];

      /* check if the request is the only one -> remove the tour */
      red = false;
    }

    /* check for the insertion points */
    for (Arc * arcptr = optr->in; arcptr != NULL; arcptr = arcptr->next_in)
    {
      Node * voisinptr = arcptr->orig;
      if (voisinptr == depot)
        continue; /* TO DO */
      Node * voisin2ptr = depot;
      if (s->next[voisinptr->id] < s->id_out)
        voisin2ptr = pb->nodes + s->next[voisinptr->id];

      /* quick check */
      if (pb->duration[dptr->id][voisin2ptr->id] > BAD_ARC)
        continue;

      /* capacity check */
      if (s->load[s->next[voisinptr->id]] + pb->requests[req].amount > pb->capacity)
        continue;

      /* check the time compatibility */
      double arrival = s->arrival[voisinptr->id];
      if (arrival < voisinptr->open)
        arrival = voisinptr->open;
      arrival += voisinptr->service + pb->duration[voisinptr->id][optr->id];
      if (arrival > optr->close)
        continue;
      if (arrival < optr->open)
        arrival = optr->open;
      arrival += optr->service + pb->duration[optr->id][dptr->id];
      if (arrival > dptr->close)
        continue;
      if (arrival < dptr->open)
        arrival = dptr->open;
      arrival += dptr->service + pb->duration[dptr->id][voisin2ptr->id];
      if (arrival > voisin2ptr->close)
        continue;
      if (arrival > s->latest[s->next[voisinptr->id]])
        continue;

      /* compute the insertion cost */
      double cost = duration_cost + pb->duration[voisinptr->id][optr->id] + pb->duration[dptr->id][voisin2ptr->id];
      if (((red == best_red) && (cost < best_cost)) || ((red == true) && (best_red == false)))
      {
        best_cost = cost;
        best_optr = optr;
        best_dptr = dptr;
        best_voisinptr = voisinptr;
        best_red = red;
printf("BasicOrOpt: red = %d (%3d,%3d) after %3d val = %g\n", red, optr->id, dptr->id, voisinptr->id, cost);
      }
    }
  }

  if (best_cost < NO_ARC)
  {
#ifdef __COINCOIN__
    /* remove the request from its tour */
    s->next[s->prev[best_optr->id]] = s->next[best_dptr->id];
    s->prev[s->next[best_dptr->id]] = s->prev[best_optr->id];

    /* perform the insertion */
    uint16 voisin2 = s->next[best_voisinptr->id];
    s->next[best_voisinptr->id] = best_optr->id;
    s->prev[best_optr->id] = best_voisinptr->id;
    s->next[best_dptr->id] = voisin2;
    s->prev[voisin2] = best_dptr->id;

    /* GERER LA SUPPRESSION D'UNE TOURNEE -> liste des index de tournees */
    /* REFAIRE LE CALCUL DES DATES */
    /* METTRE LES ACCELERATEURS DE CALCUL */
#endif
  }
}


/* ======================================================================= */
/* end of file                                                             */
/* ======================================================================= */
