
#include <stdlib.h>
#include "objetgraphique.h"


void IsetX(ObjetGraphique * this, int x) {
    this->_x = x;
}

void IsetY(ObjetGraphique * this, int y) {
    this->_y = y;
}

int IgetX(ObjetGraphique * this) {
    return this->_x;
}

int IgetY(ObjetGraphique * this) {
    return this->_y;
}

int IgetNbObjetGraphique() {
    return OGmeta._nbObjetGraphique;
}

ObjetGraphique * Inew(int x, int y) {
    ObjetGraphique * this =  malloc(sizeof(ObjetGraphique));
    this->_classe = &OGmeta;
    (this->_classe)->_nbObjetGraphique++;
    this->_x = x;
    this->_y = y;
    return this;
}

void Idelete(ObjetGraphique * this)
{
    (this->_classe)->_nbObjetGraphique--;
    free(this);
}

void Iinit(ObjetGraphique * object, int x, int y)
{
    object->_classe = &OGmeta;
    (object->_classe)->_nbObjetGraphique++;
    object->_x = x;
    object->_y = y;
}

void initMetaOG(void) {
    OGmeta._nbObjetGraphique = 0;
    OGmeta.getNBObjetGraphique = IgetNbObjetGraphique;
    OGmeta.getX = IgetX;
    OGmeta.getY = IgetY;
    OGmeta.setX = IsetX;
    OGmeta.setY = IsetY;
    OGmeta.new = Inew;
    OGmeta.delete = Idelete;
    OGmeta.init = Iinit;
}
