/*
 * Rectangle.h
 *
 *  Created on: 2 févr. 2011
 *      Author: Daniel
 */

#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include "GraphicalObject.h"

enum {
   ROTATE_INDEX = SIZE + 1, SIZE_RECTANGLE
};
typedef struct Rectangle_t {
   GraphicalObject super;
   struct MetaRectangle_t * myMetaStructure;
   int height;
   int width;

   void **vtable;
} Rectangle;

typedef struct MetaRectangle_t {

   void * V_TABLE[SIZE_RECTANGLE];

   MetaGraphicalObject * superMeta;
   void (*display)(Rectangle * this);
   void (* setX)(Rectangle * this, int);
   int (* getX)(Rectangle * this);
   void (* setY)(Rectangle * this, int);
   int (* getY)(Rectangle * this);
   void (* setHeight)(Rectangle * this, int);
   int (* getHeight)(Rectangle * this);
   void (* setWidth)(Rectangle * this, int);
   int (* getWidth)(Rectangle * this);
   void (*defaultInit)(Rectangle * this);
   void (* init)(Rectangle * this, int, int, int, int);
   void (* reset)(Rectangle * this);
   void (*setVTable)(Rectangle *this, void** inVTable);
   void (*rotate)(Rectangle *this);

} MetaRectangle;

MetaRectangle metaRectangleInstance;
void InitMetaRectangle(void);

#endif /* RECTANGLE_H_ */
