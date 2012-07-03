/* 
 * File:   group.cpp 
 * Author: escourbi
 *
 * Created on November 4, 2010, 10:14 AM
 */

#include "group.h"

Group::Group(int nombre) : _nombre(nombre),_cpt(0)
{
   _tab = new GraphicalObject*[nombre];
   for(int i=0;i<nombre;++i)
      _tab[i] = NULL;
}

bool Group::attach(GraphicalObject * a)
{
   int i = 0;
   bool ret = false;
   if(_cpt< _nombre-1)
   {
      while(_tab[i])
         ++i;
      _tab[i] = a;
      ret = true;
     ++_cpt;
   }
   return ret;
}

void Group::detach(GraphicalObject * a)
{
   int i ;
   i = find(a);
   if(i!=-1)
   {
      _tab[i] = NULL;
      --_cpt;
   }
}

int Group::find(GraphicalObject * a)
{
   int i = 0;
   while( i<_nombre && _tab[i] != a)
      ++i;
   if(i==_nombre)
      i = -1;
   return i;
}
