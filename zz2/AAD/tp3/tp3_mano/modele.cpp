/**
 * \file modele.cpp
 * \author Maxime Escourbiac Jean Christophe
 * \version 0.1
 * \date 21 novembre 2010
 */

#include "modele.h"

//-----------------------------------------------
// implementation des methodes de la classe Ville
//-----------------------------------------------

double Ville::calcul_distance(Ville * voisin)
{
  return ( sqrt( (voisin->_y - _y) * (voisin->_y - _y) + (voisin->_x - _x)*(voisin->_x - _x)));
}

//-----------------------------------------------
// implementation des methodes de la classe pb
//-----------------------------------------------

void Pb::lecture_fic(char * name)
{
  register int i;
  FILE * fic;
  Ville * temp;
  
  fic = fopen(name,"r");
  if(fic == NULL)
  {
    cout << "erreur ouverture fichier" << endl;
    exit(EXIT_FAILURE);
  }
  
  //lecture de la dimension
  
  fscanf(fic,"%d",&_dimension);
  
  for(i=0;i<_dimension;++i)
  {
    temp = new Ville();
    fscanf(fic,"%d%d%d",&(temp->_node),&(temp->_x),&(temp->_y));
    _ville_restante.push_back(temp);
  }
}

void Pb::maj_dist(Ville * ref)
{
   int i,taille;
   list<Ville *>::iterator it;
   
   taille = _ville_restante.size();
   it = _ville_restante.begin();
   
   for(i=0;i<taille;++i)
   {
     (*it)->_distance = ref->calcul_distance((*it));
     ++it;
   }
   _ville_restante.sort(compare_distance);
}

void Pb::traitement()
{
  Ville * ref;
  while(_ville_restante.empty() == false)
  {
    ref = _ville_restante.front();
    _ville_restante.pop_front();
    _chemin.push_back(ref);
    maj_dist(ref);
  }
}
  
 
void Pb::afficher_res()
{
  int i;
  list<Ville*>::iterator it;
  it = _chemin.begin();
  for(i=0;i<_dimension;++i)
  {
    cout << (*it)->_node << endl;
    ++it;
  }
}
    
 bool compare_distance(Ville * v1, Ville * v2)
 {
   return (v1->_distance < v2->_distance);
 }
