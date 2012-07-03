/**
 * \file main.cpp
 * \author Maxime Escourbiac Jean Christophe
 * \version 0.1
 * \date 21 novembre 2010
 */

#include "modele.h"

int main(int,char**)
{
  Pb prob;
  prob.lecture_fic("a5.tsp");
  prob.traitement();
  prob.afficher_res();
  return 0;
}