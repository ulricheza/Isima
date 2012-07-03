/*
 * test.c
 *
 *  Created on: 2 févr. 2011
 *      Author: Daniel
 */

#include "GraphicalObject.h"
#include "Circle.h"
#include "Rectangle.h"
#include "TextField.h"

int main(int argc, char ** argv) {

   initMetaGraphicalObject();
   initMetaCircle();
   initMetaRectangle();
   initMetaTextField();

   Circle aCircle;
   Rectangle aRectangle;

   metaCircleInstance.init(&aCircle, 0, 0, 10);
   metaRectangleInstance.init(&aRectangle, 0, 0, 10, 5);

   GraphicalObject * ptrCircle;
   ptrCircle = &aCircle;

   GraphicalObject * ptrRectangle;
   ptrRectangle = &aRectangle;

   ptrCircle->myMetaStructure->display(ptrCircle);
   ptrRectangle->myMetaStructure->display(ptrRectangle);

   printf("Rectangle center [X : %d, Y : %d]\n",
         ptrRectangle->myMetaStructure->getCenterX(ptrRectangle),
         ptrRectangle->myMetaStructure->getCenterY(ptrRectangle));

   printf("Circle center [X : %d, Y : %d]\n",
         ptrRectangle->myMetaStructure->getCenterX(ptrCircle),
         ptrRectangle->myMetaStructure->getCenterY(ptrCircle));

   TextField aText;

   metaTextFieldInstance.init(&aText, 0, 0, 15, 10, "Hello");

   printf("TextField [X : %d, Y : %d, Text : %s]\n",
         aText.myMetaStructure->getX(&aText), aText.myMetaStructure->getY(
               &aText), aText.myMetaStructure->getText(&aText));

   Rectangle * ptrTextField;

   ptrTextField = &aText;

   ptrTextField->myMetaStructure->display(ptrTextField);

   ptrTextField->myMetaStructure->rotate(ptrTextField);
   ptrTextField->myMetaStructure->display(ptrTextField);

   Rectangle bRectangle;

   metaRectangleInstance.init(&bRectangle, 0, 0, 10, 5);
   bRectangle.myMetaStructure->display(&bRectangle);
   bRectangle.myMetaStructure->rotate(&bRectangle);
   bRectangle.myMetaStructure->display(&bRectangle);
   return 0;
}
