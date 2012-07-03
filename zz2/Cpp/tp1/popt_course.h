/**
 * \file popt_course.h
 * \brief fichier d'en-tete de la classe Course
 * \author Maxime Escourbiac
 * \version 1.0
 * \date Dimanche 17 octobre 2010 
 */


#ifndef __COURSE_H_MAX__
#define __COURSE_H_MAX__

#include "popt_circuit.h"
#include "popt_paddock.h"
#include "popt_f1.h"
// to do: implementer un main pour tester les methodes des differentes classe


class Course
{
   protected:
      Paddock * _cars; //voitures effectuant la course
      Circuit * _circuit; // circuit ou se deroulera la course 
      int _chrono; // temp en minute ou se deroulera la course
   public:
      Course(Paddock * cars,Circuit * circuit, int chrono);
      ~Course() {};
      int getCHRONO() {return _chrono;}
      float * faire_course();
};

#endif
    