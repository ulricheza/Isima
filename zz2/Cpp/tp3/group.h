/* 
 * File:   group.h
 * Author: escourbi
 *
 * Created on November 4, 2010, 10:14 AM
 */

#include "graphicalobject.h"


class Group
{
   private:
      GraphicalObject ** _tab;
      int _nombre;
      int _cpt;
   public:
      Group(int nombre = 50);
      ~Group() {delete[] _tab;}

      bool attach(GraphicalObject * a);
      void detach(GraphicalObject * a);
      int find(GraphicalObject * a);
};