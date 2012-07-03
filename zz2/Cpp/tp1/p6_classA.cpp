/**
 * \file p6_classA.cpp
 * \author Maxime Escourbiac
 * \version 1.0
 * \brief fichier d'en-tete de la classe B
 *
 */

#include "p6_classA.h"

A::A () : i(0)
{
}

void A::send(B & b, int x)
{
  b.exec(x);
}
