/* 
 * File:   main.c
 * Author: Maxime
 *
 * Created on 31 janvier 2012, 15:47
 */

#include <stdio.h>
#include <stdlib.h>

#include "cercle.h"
#include "objetgraphique.h"

/*
 * 
 */
int main(int argc, char** argv) {

    initMetaOG();
    initMetaCercle();

    //Creation automatique
    ObjetGraphique objAuto;
    OGmeta.init(&objAuto, 0, 0);
    objAuto._classe->setX(&objAuto, 2);
    objAuto._classe->setY(&objAuto, 5);
    printf("Objet Auto x = %d , y = %d \n", objAuto._classe->getX(&objAuto), objAuto._classe->getY(&objAuto));

    //Creation dynamique
    ObjetGraphique * objDyna = OGmeta.new(3, 8);
    objDyna->_classe->setX(objDyna, 10);
    objDyna->_classe->setY(objDyna, 11);
    printf("Objet Dina x = %d , y = %d \n", objDyna->_classe->getX(objDyna), objDyna->_classe->getY(objDyna));

    printf("Nb objet graphique : %d\n", OGmeta.getNBObjetGraphique());
    printf("Delete objet dynamique\n");
    OGmeta.delete(objDyna);
    printf("Nb objet graphique : %d\n", OGmeta.getNBObjetGraphique());

    //Creation automatique d'un cercle
    Cercle cercleAuto;
    OGCercle.init(&cercleAuto, 1, 2, 3);
    cercleAuto._super._classe->setX(&(cercleAuto._super), 5);
    cercleAuto._super._classe->setY(&(cercleAuto._super), 6);
    cercleAuto._classe->setRayon(&cercleAuto, 10);

    printf("Objet Auto x = %d , y = %d , rayon = %d \n",
            cercleAuto._super._classe->getX(&(cercleAuto._super)),
            cercleAuto._super._classe->getY(&(cercleAuto._super)),
            cercleAuto._classe->getRayon(&cercleAuto));

    //Creation dynamique
    Cercle * cercleDyna = OGCercle.new(1, 2, 3);
    cercleDyna->_super._classe->setX(&(cercleDyna->_super), 8);
    cercleDyna->_super._classe->setY(&(cercleDyna->_super), 9);
    cercleDyna->_classe->setRayon(cercleDyna, 11);
    printf("Objet Dyna x = %d , y = %d , rayon = %d \n",
            cercleDyna->_super._classe->getX(&(cercleDyna->_super)),
            cercleDyna->_super._classe->getY(&(cercleDyna->_super)),
            cercleDyna->_classe->getRayon(cercleDyna));
    
    //methodes virtuelle
    printf("Cercle getCentreX: %d Cercle getCentreY: %d ",((int(*)(ObjetGraphique *))cercleDyna->_classe->tableMethodesVirtuelles[GET_CENTRE_X])(cercleDyna),
                                                          ((int(*)(ObjetGraphique *))cercleDyna->_classe->tableMethodesVirtuelles[GET_CENTRE_Y])(cercleDyna));
    
    //methode virtuelle pure
    ((int(*)(ObjetGraphique *))cercleDyna->_classe->tableMethodesVirtuelles[AFFICHER])(cercleDyna);
    return (EXIT_SUCCESS);
}

