/* ======================================================================= */
/* graph.c:                                                                */
/* several functions to handle the problem data                            */
/*                                                                         */
/* created: nov 24, 2009 by Christophe Duhamel                             */
/* updated: nov 17, 2010 by Christophe Duhamel                             */
/* ======================================================================= */


#include <string.h>
#include <math.h>

#include "prototypes.h"


/* ======================================================================= */
/* function that reduces the set of arcs from an instance by identifying   */
/* bad arcs (time/capacity violation for instance)                         */
/* reduce also the time windows and only work on the duration matrix       */
/* ======================================================================= */

void reduce (Problem * pb)
{
  uint16 red_cpt = 0;
  uint16 tw_cpt = 0;
  double arrival, leaving, arrival2, leaving2;

  /* static reductions: done once for all */
  {
    /* prohibited arcs: delivery -> pickup, depot -> delivery, pickup -> depot, loops */
    for (uint16 req = 0; req < pb->nb_requests; ++req)
    {
      uint16 pic = pb->requests[req].orig->id;
      uint16 del = pb->requests[req].dest->id;
      pb->duration[del][pic] = NO_ARC;
      pb->duration[0][del] = NO_ARC;
      pb->duration[pic][0] = NO_ARC;
      pb->duration[pic][pic] = NO_ARC;
      pb->duration[del][del] = NO_ARC;
      red_cpt += 5;
    }
    pb->duration[0][0] = NO_ARC;
    ++red_cpt;

    /* obvious reduction: pickup and delivery at the same location and the same tw */
    for (uint16 req = 0; req < pb->nb_requests; ++req)
    {
      Node * optr = pb->requests[req].orig;
      Node * dptr = pb->requests[req].dest;
      if ((optr->abs == dptr->abs) && (optr->ord == dptr->ord) && (optr->service < EPSILON) &&
          (optr->open == dptr->open) && (optr->close == dptr->close))
      {
        /* forbid all o's outgoing arcs but (o,d), same for d... */
        for (uint16 i = 1; i < pb->nb_nodes; ++i)
        {
          if (i != dptr->id)
          {
            pb->duration[optr->id][i] = BAD_ARC;
            ++red_cpt;
          }
          if (i != optr->id)
          {
            pb->duration[i][dptr->id] = BAD_ARC;
            ++red_cpt;
          }
        }
      }
    }

    /* time window reduction: depot -> pickup -> delivery -> depot */
    for (uint16 req = 0; req < pb->nb_requests; ++req)
    {
      uint16 pic = pb->requests[req].orig->id;
      uint16 del = pb->requests[req].dest->id;

      /* tw reduction depot -> pickup -> delivery -> depot */
      arrival = pb->nodes[0].open + pb->nodes[0].service + pb->duration[0][pic];
      if (arrival > pb->nodes[pic].open)
      {
        pb->nodes[pic].open = arrival;
        ++tw_cpt;
      }
      else
        arrival = pb->nodes[pic].open;
      arrival += pb->nodes[pic].service + pb->duration[pic][del];
      if (arrival > pb->nodes[del].open)
      {
        pb->nodes[del].open = arrival;
        ++tw_cpt;
      }

      /* tw reduction depot <- pickup <- delivery <- depot */
      leaving = pb->nodes[0].close - pb->duration[del][0] - pb->nodes[del].service;
      if (leaving < pb->nodes[del].close)
      {
        pb->nodes[del].close = leaving;
        ++tw_cpt;
      }
      else
        leaving = pb->nodes[del].close;
      leaving -= pb->duration[pic][del] + pb->nodes[pic].service;
      if (leaving < pb->nodes[pic].close)
      {
        pb->nodes[pic].close = leaving;
        ++tw_cpt;
      }
    }
  }

  /* dynamic reduction: can be done again when some arcs are deleted / some tw are strengthened */
  bool ok;
  do
  {
    ok = false;

    /* time window constraints */
    for (uint16 i = 0; i < pb->nb_nodes; ++i)
    {
      Node * iptr = pb->nodes + i;

      for (uint16 j = i + 1; j < pb->nb_nodes; ++j)
      {
        Node * jptr = pb->nodes + j;

        /* arc (i,j) */
        if ((pb->duration[i][j] < BAD_ARC) && (iptr->open + iptr->service + pb->duration[i][j] > jptr->close))
        {
          pb->duration[i][j] = BAD_ARC;
          ++red_cpt;
        }

        /* arc (j,i) */
        if ((pb->duration[j][i] < BAD_ARC) && (jptr->open + jptr->service + pb->duration[j][i] > iptr->close))
        {
          pb->duration[j][i] = BAD_ARC;
          ++red_cpt;
        }
      }
    }

    /* improve time window constraints: selecting (i,j) forbids the completion of req[i] or req[j] */
    for (uint16 i = 1; i < pb->nb_nodes; ++i)
    {
      Node * iptr = pb->nodes + i;
      Node * sibiptr = iptr->sibling;

      for (uint16 j = 1; j < pb->nb_nodes; ++j)
      {
        Node * jptr = pb->nodes + j;
        Node * sibjptr = jptr->sibling;

        /* quick check */
        if ((iptr == jptr) || (iptr->sibling == jptr) || (pb->duration[iptr->id][jptr->id] >= BAD_ARC))
          continue;

        /* arrival time at node j */
        arrival = iptr->open + iptr->service + pb->duration[iptr->id][jptr->id];
        if (arrival < jptr->open)
          arrival = jptr->open;

        /* leaving time at node i */
        leaving = jptr->close - pb->duration[iptr->id][jptr->id] - iptr->service;
        if (leaving > iptr->close)
          leaving = iptr->close;

        /* type of i */
        if (iptr->type == PICKUP)
        {
          /* case 1: i is a pickup */
          if (jptr->type == PICKUP)
          {
            /* case 1.1.a: j is a pickup -> go to deliv(i), to deliv(j) and to the depot */
            bool bad_case = false;
            arrival2 = arrival + jptr->service + pb->duration[jptr->id][sibiptr->id];
            if (arrival > sibiptr->close)
              bad_case = true;
            else
            {
              if (arrival < sibiptr->open)
                arrival = sibiptr->open;
              arrival += sibiptr->service + pb->duration[sibiptr->id][sibjptr->id];
              if (arrival > sibjptr->close)
              {
                bad_case = true;
              }
              else
              {
                if (arrival < sibjptr->open)
                  arrival = sibjptr->open;
                arrival += sibjptr->service + pb->duration[sibjptr->id][0];
                if (arrival > pb->nodes[0].close)
                  bad_case = true;
              }
            }

            /* case 1.1.b: j is a pickup -> go to deliv(j), to deliv(i) and to the depot */
            if (bad_case == true)
            {
              arrival2 = arrival + jptr->service + pb->duration[jptr->id][sibjptr->id];
              if (arrival > sibjptr->close)
              {
                pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
              }
              else
              {
                if (arrival < sibjptr->open)
                  arrival = sibjptr->open;
                arrival += sibjptr->service + pb->duration[sibjptr->id][sibiptr->id];
                if (arrival > sibiptr->close)
                {
                  pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
                }
                else
                {
                  if (arrival < sibiptr->open)
                    arrival = sibiptr->open;
                  arrival += sibiptr->service + pb->duration[sibiptr->id][0];
                  if (arrival > pb->nodes[0].close)
                  {
                    pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
                  }
                }
              }
            }

            /* case 1.1.c: j is a pickup -> come from depot */
            leaving -= pb->duration[0][iptr->id] + pb->nodes[0].service;
            if (leaving < pb->nodes[0].open)
            {
              pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
            }
          }
          else
          {
            /* case 1.2.a: j is a delivery -> go to deliv(i) and to depot */
            arrival += jptr->service + pb->duration[jptr->id][sibiptr->id];
            if (arrival > sibiptr->close)
            {
              pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
            }
            else
            {
              if (arrival < sibiptr->open)
                arrival = sibiptr->open;
              arrival += sibiptr->service + pb->duration[sibiptr->id][0];
              if (arrival > pb->nodes[0].close)
              {
                pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
              }
            }

            /* case 1.2.b: j is a delivery -> come from depot and deliv(j) */
            leaving -= pb->duration[sibjptr->id][iptr->id] + sibjptr->service;
            if (leaving < sibjptr->open)
            {
              pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
            }
            else
            {
              if (leaving > sibjptr->close)
                leaving = sibjptr->close;
              leaving -= pb->duration[0][sibjptr->id] + pb->nodes[0].service;
              if (leaving < pb->nodes[0].open)
              {
                pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
              }
            }
          }
        }
        else
        {
          /* case 2: i is a delivery */
          if (jptr->type == PICKUP)
          {
            /* case 2.1.a: j is a pickup -> go to deliv(j) and to the depot */
            arrival += jptr->service + pb->duration[jptr->id][sibjptr->id];
            if (arrival > sibjptr->close)
            {
              pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
            }
            else
            {
              if (arrival < sibjptr->open)
                arrival = sibjptr->open;
              arrival += sibjptr->service + pb->duration[sibjptr->id][0];
              if (arrival > pb->nodes[0].close)
              {
                pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
              }
            }

            /* case 2.1.b: j is a pickup -> come from depot and deliv(i) */
            leaving -= pb->duration[sibiptr->id][iptr->id] + sibiptr->service;
            if (leaving < sibiptr->open)
            {
              pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
            }
            else
            {
              if (leaving > sibiptr->close)
                leaving = sibiptr->close;
              leaving -= pb->duration[0][sibiptr->id] + pb->nodes[0].service;
              if (leaving < pb->nodes[0].open)
              {
                pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
              }
            }
          }
          else
          {
            /* case 2.2.a: j is a delivery -> go to depot */
            arrival += jptr->service + pb->duration[jptr->id][0];
            if (arrival > pb->nodes[0].close)
            {
              pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
            }

            /* case 2.1.b: j is a delivery -> come from depot, deliv(i) and deliv(j) */
            bool bad_case = false;
            leaving2 = leaving - pb->duration[sibjptr->id][iptr->id] + sibjptr->service;
            if (leaving2 < sibjptr->open)
            {
              bad_case = true;
            }
            else
            {
              if (leaving2 > sibjptr->close)
                leaving2 = sibjptr->close;
              leaving2 -= pb->duration[sibiptr->id][sibjptr->id] + sibiptr->service;
              if (leaving2 < sibiptr->open)
              {
                bad_case = true;
              }
              else
              {
                leaving2 -= pb->duration[0][sibiptr->id] + pb->nodes[0].service;
                if (leaving2 < pb->nodes[0].open)
                  bad_case = true;
              }
            }

            /* case 2.1.c: j is a delivery -> come from depot, deliv(j) and deliv(i) */
            if (bad_case == true)
            {
              leaving2 = leaving - pb->duration[sibiptr->id][iptr->id] + sibiptr->service;
              if (leaving2 < sibiptr->open)
              {
                pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
              }
              else
              {
                if (leaving2 > sibiptr->close)
                  leaving2 = sibiptr->close;
                leaving2 -= pb->duration[sibjptr->id][sibiptr->id] + sibjptr->service;
                if (leaving2 < sibjptr->open)
                {
                  pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
                }
                else
                {
                  leaving2 -= pb->duration[0][sibjptr->id] + pb->nodes[0].service;
                  if (leaving2 < pb->nodes[0].open)
                    pb->duration[iptr->id][jptr->id] = BAD_ARC; ++red_cpt; ok = true;
                }
              }
            }
          }
        }
      }
    }

    /* neighbours-based tw reduction */
    for (uint16 i = 0; i < pb->nb_nodes; ++i)
    {
      double arrival = pb->nodes[i].close;
      for (uint16 j = 1; j < pb->nb_nodes; ++j)
      {
        if (pb->duration[j][i] >= BAD_ARC)
          continue;

        if (pb->nodes[j].close + pb->nodes[j].service + pb->duration[j][i] > arrival)
          arrival = pb->nodes[j].close + pb->nodes[j].service + pb->duration[j][i];
      }

      if (arrival < pb->nodes[i].close)
      {
        pb->nodes[i].close = arrival;
        ++tw_cpt; ok = true;
      }
    }
  } while (ok == true);

/*  printf("%u tw reduced, %u arcs removed\n", tw_cpt, red_cpt);*/
}


/* ====================================================================== */
/* comparison function on arc duration                                    */
/* ====================================================================== */

static int compareArcs (const void * p1, const void * p2)
{
  double diff = ((Arc *)p1)->duration - ((Arc *)p2)->duration;
  return ((diff < -EPSILON) ? -1 : ((diff > EPSILON) ? 1 : 0));
}


/* ====================================================================== */
/* function that loads data from an instance file                         */
/* ====================================================================== */

void readData (Problem * pb, const char name[64], bool red)
{
  Arc      **in, **out, *arcptr;
  FILE     *handle;
  fpos_t   pos;
  uint16   id, nb_nodes, cpt_req, nb_arcs;
  int      x, y, o, d, speed, cont, a, b, serv, pick, deli;
  register uint16 i, j;

  /* open the data file */
  handle = fopen(name, "rt");
  if (handle == NULL)
    ERROR("unable to open %s\n", name);

  /* set the name */
  strncpy(pb->name, name, 64);

  /* read the first line */
  fscanf(handle, "%u%u%d", &(pb->max_vehicles), &(pb->capacity), &speed);

  /* count the number of nodes */
  nb_nodes = 0;
  fgetpos (handle, &pos);
  while (fscanf(handle, "%u%d%d%d%d%d%d%d%d", &id, &x, &y, &cont, &a, &b, &serv, &pick, &deli) == 9)
    ++nb_nodes;

  /* memory allocations */
  pb->nb_nodes = nb_nodes;
  pb->nb_requests = (nb_nodes - 1) / 2;
  pb->nb_arcs = nb_nodes * (nb_nodes - 1);
  pb->nodes = VECTOR_ALLOC(nb_nodes,Node);
  pb->requests = VECTOR_ALLOC(pb->nb_requests,Request);
  pb->duration = (double**)MATRIX_ALLOC(nb_nodes,nb_nodes,double);

  /* read the nodes */
  fsetpos(handle, &pos);
  cpt_req = 0;
  for (i = 0; i < pb->nb_nodes; ++i)
  {
    /* read a node */
    fscanf(handle, "%u%d%d%d%d%d%d%d%d", &id, &x, &y, &cont, &a, &b, &serv, &pick, &deli);
    assert(i == id);

    /* set its informations */
    pb->nodes[i].id = id;
    pb->nodes[i].abs = x;
    pb->nodes[i].ord = y;
    pb->nodes[i].contrib = cont;
    pb->nodes[i].service = serv;
    pb->nodes[i].open = a;
    pb->nodes[i].close = b;

    /* update its request */
    if (pick == 0)
    {
      if (deli == 0)
      {
        assert(cont == 0);
        pb->nodes[i].type = DEPOT;
        pb->nodes[i].sibling = pb->nodes + i;
      }
      else
      {
        assert(cont > 0);
        pb->nodes[i].type = PICKUP;
        if (deli < id)
        {
          pb->requests[cpt_req].id = cpt_req;
          pb->requests[cpt_req].orig = pb->nodes + id;
          pb->requests[cpt_req].dest = pb->nodes + deli;
          pb->requests[cpt_req].amount = cont;
          ++cpt_req;
        }
        pb->nodes[i].sibling = pb->nodes + deli;
      }
    }
    else
    {
      assert(cont < 0);
      pb->nodes[i].type = DELIVERY;
      if (pick < id)
      {
        pb->requests[cpt_req].id = cpt_req;
        pb->requests[cpt_req].orig = pb->nodes + pick;
        pb->requests[cpt_req].dest = pb->nodes + id;
        pb->requests[cpt_req].amount = -cont;
        ++cpt_req;
      }
      pb->nodes[i].sibling = pb->nodes + pick;
    }
  }

  /* populate the distance matrix: symmetric */
  for (i = 0; i < pb->nb_nodes; ++i)
  {
    pb->duration[i][i] = NO_ARC;
    for (j = i + 1; j < pb->nb_nodes; ++j)
    {
      double delta_x = (int)pb->nodes[i].abs - (int)pb->nodes[j].abs;
      double delta_y = (int)pb->nodes[i].ord - (int)pb->nodes[j].ord;
      pb->duration[j][i] = pb->duration[i][j] = sqrt(delta_x * delta_x + delta_y * delta_y);
    }
  }

  /* call the reduction on the arc set and time windows */
  if (red == true)
    reduce (pb);

  /* fill the arc list */
  nb_arcs = 0;
  for (i = 0; i < pb->nb_nodes; ++i)
  {
    for (j = 0; j < pb->nb_nodes; ++j)
    {
      if (pb->duration[i][j] < BAD_ARC)
        ++nb_arcs;
    }
  }
  pb->nb_arcs = nb_arcs;
  pb->arcs = VECTOR_ALLOC(pb->nb_arcs,Arc);
  nb_arcs = 0;
  for (i = 0; i < pb->nb_nodes; ++i)
  {
    for (j = 0; j < pb->nb_nodes; ++j)
    {
      if (pb->duration[i][j] < BAD_ARC)
      {
        pb->arcs[nb_arcs].id = nb_arcs;
        pb->arcs[nb_arcs].orig = pb->nodes + i;
        pb->arcs[nb_arcs].dest = pb->nodes + j;
        pb->arcs[nb_arcs].duration = pb->duration[i][j];
        pb->arcs[nb_arcs].next_in = pb->arcs[nb_arcs].next_out = NULL;
        ++nb_arcs;
      }
    }
  }
  qsort(pb->arcs, pb->nb_arcs, sizeof(Arc), compareArcs);
  out = VECTOR_ALLOC(nb_nodes,Arc*);
  in  = VECTOR_ALLOC(nb_nodes,Arc*);
  for (i = 0; i < nb_nodes; ++i)
  {
    out[i] = in[i] = NULL;
  }

  /* build the adjacency list */
  for (i = 0, arcptr = pb->arcs; i < pb->nb_arcs; ++i, ++arcptr)
  {
    arcptr->id = i; /* IMPORTANT */
    o = arcptr->orig->id;
    d = arcptr->dest->id;

    /* update the outgoing set of arcs */
    if (out[o] == NULL)
      arcptr->orig->out = arcptr;
    else
      out[o]->next_out = arcptr;
    out[o] = arcptr;
    arcptr->orig->nb_out++;

    /* update the incoming set of arcs */
    if (in[d] == NULL)
      arcptr->dest->in = arcptr;
    else
      in[d]->next_in = arcptr;
    in[d] = arcptr;
    arcptr->dest->nb_in++;
  }

  /* clean up memory */
  VECTOR_FREE(in);
  VECTOR_FREE(out);

  /* close the data file */
  fclose (handle);
}


/* ====================================================================== */
/* function that prints out the data                                      */
/* ====================================================================== */

void displayProblem (Problem * pb)
{
  Node    * nodeptr;
  Arc     * arcptr;
  Request * reqptr;
  uint16    fixed_cpt;
  register uint16 i;

  static const char * TYPE_DESC[3] = {"O", "P", "D"};
  static const char * TYPE_LINK[3] = {"<>", "->", "<-"};

  /* display global data */
  printf("\n\nProblem %s: %d nodes %d arcs\n",
    pb->name, pb->nb_nodes, pb->nb_arcs);

  /* display the nodes */
  fixed_cpt = 0;
  for (i = 0, nodeptr = pb->nodes; i < pb->nb_nodes; ++i, ++nodeptr)
  {
    printf(" n %3d: (%u,%u) %s%s%3d %d [%g,%g] serv=%g", nodeptr->id, nodeptr->abs, nodeptr->ord, TYPE_DESC[nodeptr->type], TYPE_LINK[nodeptr->type], nodeptr->sibling->id, nodeptr->contrib, nodeptr->open, nodeptr->close, nodeptr->service);

    /* display the neighbourhood */
    printf(" in=(");
/*printf("%u", nodeptr->nb_in);*/
    for (arcptr = nodeptr->in; arcptr != NULL; arcptr = arcptr->next_in)
      printf(" %d", arcptr->orig->id);
    printf(") out=(");
/*printf("%u", nodeptr->nb_out);*/
    for (arcptr = nodeptr->out; arcptr != NULL; arcptr = arcptr->next_out)
      printf(" %d", arcptr->dest->id);
    printf(")\n");
    if (nodeptr->nb_in == 1)
      ++fixed_cpt;
    if (nodeptr->nb_out == 1)
      ++fixed_cpt;
  }

  /* display the arcs */
  for (i = 0, arcptr = pb->arcs; i < pb->nb_arcs; ++i, ++arcptr)
  {
    printf(" a %3d -> (%2d,%2d) [%p] : ",
      arcptr->id, arcptr->orig->id, arcptr->dest->id, (void*)(arcptr));
    printf(" duration = %lf, (%p,%p)\n",
      arcptr->duration, (void*)(arcptr->next_in), (void*)(arcptr->next_out));
  }

  /* display the requests */
  for (i = 0, reqptr = pb->requests; i < pb->nb_requests; ++i, ++reqptr)
  {
    printf(" r %3d -> %u units from %2d to %2d\n",
      reqptr->id, reqptr->amount, reqptr->orig->id, reqptr->dest->id);
  }

  /* display a quick analysis */
/*  printf("%u connections fixed\n", fixed_cpt);*/
  fflush(stdout);
}


/* ====================================================================== */
/* function that frees all the memories allocated for the problem         */
/* ====================================================================== */

void freeProblem (Problem * pb)
{
  /* free memory */
  VECTOR_FREE(pb->nodes);
  VECTOR_FREE(pb->arcs);
  VECTOR_FREE(pb->requests);
  MATRIX_FREE(pb->duration);
}


/* ====================================================================== */
/* function that checks integrity of the data                             */
/* ====================================================================== */

void checkProblem (Problem * pb)
{
  Node     *nodeptr;
  Arc      *arcptr;
  double   duration;
  register uint16 i;

  /* check tables size */
  if ((pb->nodes == NULL) || (pb->arcs == NULL))
    ERROR("one table is empty");

  /* check for the sort of the arcs */
  for (i = 0, arcptr = pb->arcs; i < pb->nb_arcs - 1; ++i)
  {
    duration = arcptr->duration;
    ++arcptr;
    if (duration > arcptr->duration)
      ERROR("unsorted arcs (duration): %f <= %f", duration, arcptr->duration);
  }

  /* check the adjacency lists */
  for (i = 0, nodeptr = pb->nodes; i < pb->nb_nodes; ++i, ++nodeptr)
  {
    duration = NO_ARC;
    for (arcptr = nodeptr->in; arcptr != NULL; )
    {
      duration = arcptr->duration;
      arcptr = arcptr->next_in;
      if (arcptr == NULL)
        break;
      if (duration > arcptr->duration)
        ERROR("unsorted in-list of %d", nodeptr->id);
    }

    for (arcptr = nodeptr->out; arcptr != NULL; )
    {
      duration = arcptr->duration;
      arcptr = arcptr->next_out;
      if (arcptr == NULL)
        break;
      if (duration > arcptr->duration)
        ERROR("unsorted out-list of %d", nodeptr->id);
    }

    if (duration == NO_ARC)
      ERROR("unconnected %d", nodeptr->id);
  }

  /* check miscelanous features */
  if (pb->nodes[0].type != DEPOT)
    ERROR("node 0 is not the depot (%d)", pb->nodes[0].type);
}


/* ======================================================================= */
/* end of file                                                             */
/* ======================================================================= */
