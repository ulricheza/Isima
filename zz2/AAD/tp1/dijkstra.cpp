/**
 * \file dijkstra.cpp
 * \brief Programme de plus court chemin selon l'algo de dijkstra
 * \author Maxime Escourbiac Jean Christophe Septier
 * \version 0.1
 * \date Mercredi 12 Octobre 2010
 *
 * Programme de plus court chemin selon l'algo de dijkstra en C++
 *
 */



#include "dijkstra.h"


retour * dijkstra(graphe_t * gr,const int & debut,const int & fin)
{
   //declaration des variables
   register int i,j;
   int sommets=0,sommet_change,prec=-1,first_arc,sauv_sommet;
   bool fini = false;
   
   retour * res = new retour[gr->nb_sommets];
   list<dij>li(gr->nb_sommets); // creation de la liste 
   list<dij>::iterator it = li.begin();
   
   //initialisation de la liste de travail
   for(i=0;i<gr->nb_sommets;++i)
   {
      (*it).som = &(gr->sommets[i]);
      if(gr->sommets[i].label == debut)
         (*it).distance = 0;
      else
         (*it).distance = GR_MAX; //distance choisi assez grande pour simuler un max_float
      ++it;
   }


   while(li.size() != 0 && fini == false)
   {
      //tri sur la distance
      li.sort(compare_distance); 
      it = li.begin();
      
      //on met a jour la chaine de sortie
      res[sommets].label = (*it).som->label;
      res[sommets].prec = prec;
      res[sommets].distance = (*it).distance;
      
      if(fin == res[sommets].label)
         fini = true;
      
      //mise a jour distance fils
      sommet_change = (*it).som->nb_arcs;
      sauv_sommet = sommet_change;
      first_arc = (*it).som->first_arc;
      prec = res[sommets].label;
      while(sommet_change > 0 && it!=li.end())
      {
         ++it;
         j=0;
         while(j < sauv_sommet)
         {
            if((*it).som->label == gr->arcs[first_arc+j].destination)
            {
               (*it).distance = res[sommets].distance + gr->arcs[first_arc+j].distance;
               --sommet_change;
            }
            ++j;
         }
      }
      //on sort l'element de tete de la liste
      li.pop_front();
      ++sommets;
   }  
   
   return res;
}
      
bool compare_distance(const dij & first, const dij & second)
{
  return(first.distance < second.distance);
}   
