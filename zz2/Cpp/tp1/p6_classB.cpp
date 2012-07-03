/**
 * \file p6_classB.cpp
 * \author Maxime Escourbiac
 * \version 1.0
 * \brief fichier d'en-tete de la classe B
 *
 */

#include "p6_classB.h"

B::B () : j(0)
{
}

void B::send(A & a, int x)
{
  a.exec(x);
}

