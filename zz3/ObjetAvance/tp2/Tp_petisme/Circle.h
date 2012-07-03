/*
 * Circle.h
 *
 *  Created on: 2 févr. 2011
 *      Author: Daniel
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "GraphicalObject.h"

typedef struct Circle_t {
   GraphicalObject super;
   struct MetaCircle_t * myMetaStructure;
   int radius;
} Circle;

typedef struct MetaCircle_t {

   void * V_TABLE[SIZE];

   MetaGraphicalObject * superMeta;
   void (* setX)(Circle * this, int);
   int (* getX)(Circle * this);
   void (* setY)(Circle * this, int);
   int (* getY)(Circle * this);
   void (* setRadius)(Circle * this, int);
   int (* getRadius)(Circle * this);
   void (*defaultInit)(Circle * this);
   void (* init)(Circle * this, int, int, int);
   void (* reset)(Circle * this);

} MetaCircle;

MetaCircle metaCircleInstance;
void InitMetaCircle(void);

#endif /* CIRCLE_H_ */
