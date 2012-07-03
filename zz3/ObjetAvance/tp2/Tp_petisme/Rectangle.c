/*
 * Rectangle.c
 *
 *  Created on: 2 févr. 2011
 *      Author: Daniel
 */

#include "Rectangle.h"

void setXRectangle(Rectangle * this, int inX) {
   this->super.myMetaStructure->setX(&this->super, inX);
}

int getXRectangle(Rectangle * this) {
   return this->super.myMetaStructure->getX(&this->super);
}

void setYRectangle(Rectangle * this, int inY) {
   this->super.myMetaStructure->setY(&this->super, inY);
}

int getYRectangle(Rectangle * this) {
   return this->super.myMetaStructure->getY(&this->super);
}

void setHeight(Rectangle * this, int inHeight) {
   this->height = inHeight;
}
int getHeight(Rectangle * this) {
   return this->height;
}

void setWidth(Rectangle * this, int inWidth) {
   this->width = inWidth;
}
int getWidth(Rectangle * this) {
   return this->width;
}

void defaultInitRectangle(Rectangle * this) {

   this->height = 0;
   this->width = 0;
   this->myMetaStructure = &metaRectangleInstance;

   metaGraphicalObjectInstance.defaultInit(&this->super);

   this->vtable = (this->myMetaStructure->V_TABLE);
   (this->super).myMetaStructure->setVTable(&this->super, this->vtable);
}

void initRectangle(Rectangle * this, int inX, int inY, int inHeight,
      int inWidth) {

   defaultInitRectangle(this);
   this->myMetaStructure->setHeight(this, inHeight);
   this->myMetaStructure->setWidth(this, inWidth);
   this->myMetaStructure->setX(this, inX);
   this->myMetaStructure->setY(this, inY);

}

void resetRectangle(Rectangle * this) {
   this->super.myMetaStructure->reset(&this->super);

}

void * displayRectangle(Rectangle * this) {
   printf("Rectangle [X : %d, Y %d, Height : %d, Width : %d]\n",
         this->myMetaStructure->getX(this), this->myMetaStructure->getY(this),
         this->myMetaStructure->getHeight(this),
         this->myMetaStructure->getWidth(this));
   return NULL;
}

int getCenterXRectangle(Rectangle * this) {
   return this->super.x + this->width * 0.5;
}

int getCenterYRectangle(Rectangle * this) {
   return this->super.y + this->height * 0.5;
}

void setVTableRectangle(Rectangle * this, void ** inVTable) {
   this->vtable = inVTable;
   (this->super).myMetaStructure->setVTable(&this->super, this->vtable);
}

void rotateRectangle(Rectangle * this) {
   int height = this->myMetaStructure->getHeight(this);
   this->myMetaStructure->setHeight(this, this->myMetaStructure->getWidth(this));
   this->myMetaStructure->setWidth(this, height);

}
void rotate(Rectangle * this) {
   ((function) (this->vtable[ROTATE_INDEX]))(this);
}

void initMetaRectangle(void) {
   metaRectangleInstance.superMeta = &metaGraphicalObjectInstance;
   metaRectangleInstance.setX = setXRectangle;
   metaRectangleInstance.getX = getXRectangle;
   metaRectangleInstance.setY = setYRectangle;
   metaRectangleInstance.getY = getYRectangle;
   metaRectangleInstance.setHeight = setHeight;
   metaRectangleInstance.getHeight = getHeight;
   metaRectangleInstance.setWidth = setWidth;
   metaRectangleInstance.getWidth = getWidth;
   metaRectangleInstance.setVTable = setVTableRectangle;
   metaRectangleInstance.defaultInit = defaultInitRectangle;
   metaRectangleInstance.init = initRectangle;
   metaRectangleInstance.reset = resetRectangle;
   metaRectangleInstance.rotate = rotate;
   metaRectangleInstance.display = metaRectangleInstance.superMeta->display;

   int i = 0;
   for (i = 0; i < SIZE; i++) {
      metaRectangleInstance.V_TABLE[i] = metaGraphicalObjectInstance.V_TABLE[i];
   }

   metaRectangleInstance.V_TABLE[DISPLAY_INDEX] = displayRectangle;
   metaRectangleInstance.V_TABLE[GET_CENTER_X_INDEX] = getCenterXRectangle;
   metaRectangleInstance.V_TABLE[GET_CENTER_Y_INDEX] = getCenterYRectangle;

   metaRectangleInstance.V_TABLE[ROTATE_INDEX] = rotateRectangle;

}
