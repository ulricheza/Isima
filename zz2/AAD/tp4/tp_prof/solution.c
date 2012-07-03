/* ======================================================================= */
/* solution.c:                                                             */
/* several functions to handle a solution                                  */
/*                                                                         */
/* created: nov 24, 2009 by Christophe Duhamel                             */
/* updated: nov 17, 2010 by Christophe Duhamel                             */
/* ======================================================================= */


#include "prototypes.h"


void createSolution (Problem * pb, Solution * s)
{
  s->nb_nodes = pb->nb_nodes;
  s->size = pb->nb_nodes + 2 * pb->nb_requests;
  assert(s->size);
  s->id_out = s->nb_nodes;
  s->id_in  = s->id_out + pb->nb_requests;
  s->prev    = VECTOR_ALLOC(s->size, uint16);
  s->next    = VECTOR_ALLOC(s->size, uint16);
  s->arrival = VECTOR_ALLOC(s->size, double);
  s->load    = VECTOR_ALLOC(s->size, uint16);
  s->latest  = VECTOR_ALLOC(s->size, double);
}


void freeSolution (Solution * s)
{
  VECTOR_FREE(s->prev);
  VECTOR_FREE(s->next);
  VECTOR_FREE(s->arrival);
  VECTOR_FREE(s->load);
  VECTOR_FREE(s->latest);
}


void initSolution (Solution * s)
{
  for (uint16 i = 0; i < s->size; ++i)
  {
    s->prev[i] = s->next[i] = NOBODY;
    s->arrival[i] = 0.0;
    s->load[i] = 0;
    s->latest[i] = 0.0;
  }
  s->nb_vehicles = 0;
  s->distance = 0.0;
}


void displaySolution (Solution * s, bool abr)
{
  if (abr == false)
  {
    for (uint16 veh = 0; veh < s->nb_vehicles; ++veh)
    {
      printf("%3d: ", veh);
      for (uint16 nod = s->id_out + veh; nod != NOBODY; nod = s->next[nod])
      {
        if (nod < s->id_out)
          printf(" %d", nod);
        else if (nod < s->id_in)
          printf(" [0");
        else
          printf(" 0]");
      }
      printf("\n");
    }
  }
  printf(" veh = %3u val = %f\n", s->nb_vehicles, s->distance);
}


void dumpSolution (Solution * s)
{
  printf("prev:");
  for (uint16 i = 0; i < s->size; ++i)
    printf(" %u", s->prev[i]);
  printf("\n");

  printf("next:");
  for (uint16 i = 0; i < s->size; ++i)
    printf(" %u", s->next[i]);
  printf("\n");

  printf("arrival:");
  for (uint16 i = 0; i < s->size; ++i)
    printf(" %g", s->arrival[i]);
  printf("\n");

  printf("latest:");
  for (uint16 i = 0; i < s->size; ++i)
    printf(" %g", s->latest[i]);
  printf("\n");

  printf("load:");
  for (uint16 i = 0; i < s->size; ++i)
    printf(" %d", s->load[i]);
  printf("\n");

  printf(" veh = %3u val = %f\n", s->nb_vehicles, s->distance);
}


void displaySolutionGnuplot (Solution * s, Problem * pb, const char name[64])
{
  char dataname[64], cmdname[64];
  FILE * handle;

  /* create the data file */
  sprintf(dataname, "%s.dat", name);
  handle = fopen(dataname, "wt");
  if (handle == NULL)
    ERROR("unable to open %s\n", dataname);

  /* write the description */
  fprintf(handle, "# abs   ord\n");
  for (uint16 veh = 0; veh < s->nb_vehicles; ++veh)
  {
    /* write the tour */
    uint16 node = s->id_out + veh;
    fprintf(handle, "%d %d\n", pb->nodes[0].abs, pb->nodes[0].ord);
    for (node = s->next[node]; node != NOBODY; node = s->next[node])
    {
      if (node > s->id_out)
        fprintf(handle, "%d %d\n", pb->nodes[0].abs, pb->nodes[0].ord);
      else
        fprintf(handle, "%d %d\n", pb->nodes[node].abs, pb->nodes[node].ord);
    }
    fprintf(handle, "\n\n");
  }

  /* close the data file */
  fclose(handle);

  /* create the command file */
  sprintf(cmdname, "%s.plt", name);
  handle = fopen(cmdname, "wt");
  if (handle == NULL)
    ERROR("unable to open %s\n", cmdname);

  /* write the command */
  fprintf(handle, "set autoscale\nunset label\n");
  fprintf(handle, "plot");
  for (uint16 veh = 0; veh < s->nb_vehicles; ++veh)
  {
    fprintf(handle, "%s\"%s\" index %d using 1:2 w lines", ((veh == 0) ? " " : ", "), dataname, veh);
  }
  fprintf(handle, "\n");

  /* close the command file */
  fclose(handle);
}


void checkSolution (Solution * s, Problem * pb)
{
  char val[s->size];

  /* initialization */
  for (uint16 i = 0; i < s->size; i++)
    val[i] = 0;

  /* check the chain on next */
  for (uint16 veh = 0; veh < s->nb_vehicles; ++veh)
  {
    uint16 load = 0;
    double arrival = 0.0;
    for (uint16 nod = s->id_out + veh; nod != NOBODY; )
    {
      /* get the true node id */
      uint16 true_nod = nod;
      if (nod >= s->id_out)
        true_nod = 0;

      /* check that the node was not already visited */
      assert(val[nod] == 0);
      ++val[nod];

      /* get the next node */
      uint16 next = s->next[nod];
      assert((next < s->size) || (next == NOBODY));

      /* check the capacity */
      assert(load == s->load[nod]);
      if (nod == true_nod)
      {
        int contrib = pb->nodes[nod].contrib;
        if (contrib > 0)
          assert(load + contrib < pb->capacity);
        else
          assert(load >= -contrib);
        load += contrib;
      }

      /* check the time */
      if (arrival < pb->nodes[true_nod].open)
        arrival = pb->nodes[true_nod].open;
      assert(arrival == s->arrival[nod]);
      if (nod == true_nod)
      {
        assert(arrival <= pb->nodes[nod].close);
        arrival += pb->nodes[nod].service;
        if (next >= s->id_in)
          arrival += pb->duration[nod][0];
        else
        {
          assert(next < s->id_out);
          arrival += pb->duration[nod][next];
        }
      }
      else
      {
        assert(arrival <= pb->nodes[0].close);
      }

      /* go to the next node */
      nod = next;
    }
  }

  /* check the chain on prev and the latest arrival time */
  for (uint16 veh = 0; veh < s->nb_vehicles; ++veh)
  {
    uint16 nod = s->id_in + veh;
    double latest = pb->nodes[0].close;
    do
    {
      assert(val[nod] == 1);
      assert (latest == s->latest[nod]);
      ++val[nod];
      uint16 old_nod = nod;
      nod = s->prev[nod];
      if (nod != NOBODY)
      {
        uint16 true_nod = nod;
        if (true_nod >= s->id_out)
          true_nod = 0;
        uint16 true_old_nod = old_nod;
        if (true_old_nod >= s->id_out)
          true_old_nod = 0;
        latest -= pb->duration[true_nod][true_old_nod] + pb->nodes[true_nod].service;
        latest = MIN(latest,pb->nodes[true_nod].close);
      }
    } while (nod != NOBODY);
  }
}


/* ======================================================================= */
/* END OF FILE                                                             */
/* ======================================================================= */
