/**
 * \file p6_main.cpp
 * \author Maxime Escourbiac
 * \version 1.0
 * \brief main de la partie 6
 *
 */

#include "p6_classB.h"
#include "p6_classA.h"
#include <iostream>

int main(int, char**)
{
  A una;
  B unb;
  una.exec(10);
  unb.exec(9);
  una.send(unb,6);
  unb.send(una,12);
  std::cout << "val A " << una.getVAL() << std::endl;
  std::cout << "val B " << unb.getVAL() << std::endl;
  return 0;
}