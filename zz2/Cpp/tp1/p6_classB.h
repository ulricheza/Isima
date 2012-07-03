/**
 * \file p6_classB.h
 * \author Maxime Escourbiac
 * \version 1.0
 * \brief fichier d'en-tete de la classe B
 *
 */

#ifndef __P6_CLASSB_H__
#define __P6_CLASSB_H__

#include "p6_classA.h"

class A;
class B
{
   protected:
      int j;
   public:
      B(); 
      ~B() {}
      int getVAL() {return j;}
      void exec(int x) { j+= x;}
      void send(A & a,int x);
};

#endif