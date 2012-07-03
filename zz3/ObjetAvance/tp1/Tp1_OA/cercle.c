
#include <stdlib.h>
#include "cercle.h"

void CsetRayon(Cercle * this, int rayon) {
    this->_rayon = rayon;
}

int CgetRayon(Cercle * this) {
    return this->_rayon;
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
    initMetaOG();
    
    OGCercle.base = &OGmeta;
    OGCercle.new = Cnew;
    OGCercle.delete = Cdelete;
    OGCercle.init = Cinit;
    OGCercle.getRayon = CgetRayon;
    OGCercle.setRayon = CsetRayon;
}
