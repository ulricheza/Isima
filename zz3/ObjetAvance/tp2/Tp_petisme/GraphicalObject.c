/*
 * GraphicalObject.c
 *
 *  Created on: 2 févr. 2011
 *      Author: Daniel
 */
#include "GraphicalObject.h"

void setX(GraphicalObject * this, int inX) {
   this->x = inX;
}

int getX(GraphicalObject * this) {
   return this->x;
}

void setY(GraphicalObject * this, int inY) {
   this->y = inY;
}

int getY(GraphicalObject * this) {
   return this->y;
}

void defaultInit(GraphicalObject * this) {
   this->myMetaStructure = &metaGraphicalObjectInstance;
   this->x = 0;
   this->y = 0;
   this->myMetaStructure->NB_GRAPHICAL_OBJECT
         = this->myMetaStructure->NB_GRAPHICAL_OBJECT + 1;
   this->vtable = (this->myMetaStructure->V_TABLE);

}

void init(GraphicalObject * this, int inX, int inY) {

   defaultInit(this);
   this->x = inX;
   this->y = inY;
   this->vtable = this->myMetaStructure->V_TABLE;
}

void reset(GraphicalObject * this) {
   //free(this);
}

int getNbGraphicalObject() {
   return metaGraphicalObjectInstance.NB_GRAPHICAL_OBJECT;
}

int getCenterX(GraphicalObject * this) {
   return (int) ((function) (this->vtable[GET_CENTER_X_INDEX]))(this);
}

int getCenterY(GraphicalObject * this) {
   return (int) ((function) (this->vtable[GET_CENTER_Y_INDEX]))(this);
}

void display(GraphicalObject * this) {
   ((function) (this->vtable[DISPLAY_INDEX]))(this);
}

void setVTable(GraphicalObject * this, void ** inVTable) {
   this->vtable = inVTable;
}

void initMetaGraphicalObject(void) {
   metaGraphicalObjectInstance.setX = setX;
   metaGraphicalObjectInstance.setY = setY;
   metaGraphicalObjectInstance.getX = getX;
   metaGraphicalObjectInstance.getY = getY;
   metaGraphicalObjectInstance.defaultInit = defaultInit;
   metaGraphicalObjectInstance.init = init;
   metaGraphicalObjectInstance.reset = reset;
   metaGraphicalObjectInstance.NB_GRAPHICAL_OBJECT = 0;
   metaGraphicalObjectInstance.getNbGraphicalObject = getNbGraphicalObject;
   metaGraphicalObjectInstance.setVTable = setVTable;
   metaGraphicalObjectInstance.getCenterX = getCenterX;
   metaGraphicalObjectInstance.getCenterY = getCenterY;
   metaGraphicalObjectInstance.display = display;

   //Virtual methods
   metaGraphicalObjectInstance.V_TABLE[GET_CENTER_X_INDEX] = getCenterX;
   metaGraphicalObjectInstance.V_TABLE[GET_CENTER_Y_INDEX] = getCenterY;

   //Abstract methods
   metaGraphicalObjectInstance.V_TABLE[DISPLAY_INDEX] = NULL;

}

