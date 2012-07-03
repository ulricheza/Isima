
#include <stdlib.h>
#include <stdio.h>
#include "cercle.h"

void CsetRayon(Cercle * this, int rayon) {
    this->_rayon = rayon;
}

int CgetRayon(Cercle * this) {
    return this->_rayon;
}

void Cdisplay(Cercle * this) {
   printf("Circle [X : %d, Y %d, Radius : %d]\n", this->_super._x,this->_super._y,this->_rayon);
}

int getCenterXCircle(Cercle * this) {
   return this->_super._x + this->_rayon * 0.5;
}

int getCenterYCircle(Cercle * this) {
   return this->_super._y + this->_rayon * 0.5;
}

Cercle * Cnew(int x, int y, int rayon) {
    Cercle * this =  malloc(sizeof(Cercle));
    this->_classe = &OGCercle;
    OGmeta.init(&(this->_super), x, y);
    (this->_classe->base)->_nbObjetGraphique++;
    this->_rayon = rayon;
    return this;
}

void Cdelete(Cercle * this)
{
    (this->_classe->base)->_nbObjetGraphique--;
    free(this);
}

void Cinit(Cercle * object, int x, int y,int rayon)
{
    object->_classe = &OGCercle;
    OGmeta.init(&(object->_super), x, y);
    (object->_classe->base)->_nbObjetGraphique++;
    object->_rayon = rayon;
}

void initMetaCercle(void) {
    int i = 0;
    initMetaOG();
    
    OGCercle.base = &OGmeta;
    OGCercle.new = Cnew;
    OGCercle.delete = Cdelete;
    OGCercle.init = Cinit;
    OGCercle.getRayon = CgetRayon;
    OGCercle.setRayon = CsetRayon;
    
    
   for (i = 0; i < TAILLE; i++) {
      OGCercle.tableMethodesVirtuelles[i] = OGmeta.tableMethodeVirtuelle[i];
   }

   OGCercle.tableMethodesVirtuelles[AFFICHER] = Cdisplay;
   OGCercle.tableMethodesVirtuelles[GET_CENTRE_X] = getCenterXCircle;
   OGCercle.tableMethodesVirtuelles[GET_CENTRE_Y] = getCenterYCircle;
}
