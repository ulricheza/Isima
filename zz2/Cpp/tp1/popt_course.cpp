/**
 * \file popt_course.cpp
 * \brief fichier de declaration des methodes de la classe Course
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Dimanche 17 octobre 2010 
 */

#include "popt_course.h"



Course :: Course(Paddock * cars,Circuit * circuit, int chrono):
                _cars(cars),_circuit(circuit),_chrono(chrono)
{
}

/**
 * \fn float * Course :: faire_course()
 * \brief effectue une simulation de course sur un circuit et des voitures données
 * \return tab tableau des distances parcouru par les voitures 
 */
float * Course :: faire_course()
{
  int nbre_participant,i;
  float t,regime_max;
  float * distance;
  F1 * temp;
  
  nbre_participant = _cars->getNOMBRE_F1();
  distance = new float [nbre_participant];
  
  //initialisation diu tableau de distance
  for(i=0;i<nbre_participant;++i)
     distance[i] = 0.0; //distance en metre
  
  //simulation de la course
  //on utilisera un pas de simulation a la seconde
  while(t < _chrono*60)
  {
     for(i=0;i<nbre_participant;++i)
     {
        temp = _cars->voir_f1(i);
        if(temp->getRESERVOIR() > 0.0)
        {  
           //MAJ de la distance
           regime_max = (float)_circuit->regime_max_distance(((int)distance[i])%_circuit->getTAILLE());
           distance[i] += (float)temp->getVITESSE_REGIME((int)regime_max)/3.6;
           //MAJ du reservoir
           temp->setRESERVOIR(temp->getRESERVOIR() - temp->getCONSOMMATION()/3600.0);
        }
     }
     ++t;
  }
  
  return distance;
  
}
