/*
 * GraphicalObject.h
 *
 *  Created on: 2 févr. 2011
 *      Author: Daniel
 */

#ifndef GRAPHICALOBJECT_H_
#define GRAPHICALOBJECT_H_

#include <stdio.h>
#include <stdlib.h>

enum {
   DISPLAY_INDEX, GET_CENTER_X_INDEX, GET_CENTER_Y_INDEX, SIZE
};

typedef void * (*function)(void *);

typedef struct GraphicalObject_t {
   struct MetaGraphicalObject_t * myMetaStructure;
   int x;
   int y;

   void ** vtable;

} GraphicalObject;

typedef struct MetaGraphicalObject_t {

   int NB_GRAPHICAL_OBJECT;
   void * V_TABLE[SIZE];
   void (* setX)(GraphicalObject * this, int);
   int (* getX)(GraphicalObject * this);
   void (* setY)(GraphicalObject * this, int);
   int (* getY)(GraphicalObject * this);
   void (* defaultInit)(GraphicalObject * this);
   void (* init)(GraphicalObject * this, int, int);
   void (* reset)(GraphicalObject * this);
   int (* getNbGraphicalObject)();
   void (*display)(GraphicalObject * this);
   int (* getCenterX)(GraphicalObject * this);
   int (* getCenterY)(GraphicalObject * this);
   void (*setVTable)(GraphicalObject *this, void** inVTable);

} MetaGraphicalObject;

MetaGraphicalObject metaGraphicalObjectInstance;

void initMetaGraphicalObject(void);

#endif /* GRAPHICALOBJECT_H_ */
