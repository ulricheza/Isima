/*
 * Circle.c
 *
 *  Created on: 2 févr. 2011
 *      Author: Daniel
 */

#include "Circle.h"

void setXCircle(Circle * this, int inX) {
   this->super.myMetaStructure->setX(&this->super, inX);
}

int getXCircle(Circle * this) {
   return this->super.myMetaStructure->getX(&this->super);
}

void setYCircle(Circle * this, int inY) {
   this->super.myMetaStructure->setY(&this->super, inY);
}

int getYCircle(Circle * this) {
   return this->super.myMetaStructure->getY(&this->super);
}

void setRadius(Circle * this, int inRadius) {
   this->radius = inRadius;
}
int getRadius(Circle * this) {
   return this->radius;
}

void defaultInitCircle(Circle * this) {

   this->radius = 0;

   this->myMetaStructure = &metaCircleInstance;
   metaGraphicalObjectInstance.defaultInit(&this->super);

   (this->super).vtable = (this->myMetaStructure->V_TABLE);
}

void initCircle(Circle * this, int inX, int inY, int inRadius) {

   defaultInitCircle(this);
   this->radius = inRadius;
   this->super.myMetaStructure->setX(&this->super, inX);
   this->super.myMetaStructure->setY(&this->super, inY);

}

void resetCircle(Circle * this) {
   this->super.myMetaStructure->reset(&this->super);

}

void * displayCircle(Circle * this) {
   printf("Circle [X : %d, Y %d, Radius : %d]\n", this->myMetaStructure->getX(
         this), this->myMetaStructure->getY(this),
         this->myMetaStructure->getRadius(this));
   return NULL;
}

int getCenterXCircle(Circle * this) {
   return this->super.x + this->radius * 0.5;
}

int getCenterYCircle(Circle * this) {
   return this->super.y + this->radius * 0.5;
}

void initMetaCircle(void) {

   metaCircleInstance.setX = setXCircle;
   metaCircleInstance.getX = getXCircle;
   metaCircleInstance.setY = setYCircle;
   metaCircleInstance.getY = getYCircle;
   metaCircleInstance.setRadius = setRadius;
   metaCircleInstance.getRadius = getRadius;
   metaCircleInstance.defaultInit = defaultInitCircle;
   metaCircleInstance.init = initCircle;
   metaCircleInstance.reset = resetCircle;

   int i = 0;
   for (i = 0; i < SIZE; i++) {
      metaCircleInstance.V_TABLE[i] = metaGraphicalObjectInstance.V_TABLE[i];
   }

   metaCircleInstance.V_TABLE[DISPLAY_INDEX] = displayCircle;
   metaCircleInstance.V_TABLE[GET_CENTER_X_INDEX] = getCenterXCircle;
   metaCircleInstance.V_TABLE[GET_CENTER_Y_INDEX] = getCenterYCircle;
}
