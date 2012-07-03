/**
 * \file p6_classA.h
 * \author Maxime Escourbiac
 * \version 1.0
 * \brief fichier d'en-tete de la classe A
 *
 */

#ifndef __P6_CLASSA_H__
#define __P6_CLASSA_H__

#include "p6_classB.h"

class B;
class A
{
   protected:
      int i;
   public:
      A();
      ~A() {}
      int getVAL() {return i;}
      void exec(int x) { i+= x;}
      void send(B & ,int x); 
};

#endif