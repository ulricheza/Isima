/**
 * \file arme.h
 * \brief fichier de declaration de la classe Arme
 * \author Maxime ESCOURBIAC Jean-Christophe SEPTIER
 * \date 27 Fevrier 2011
 * \version 1.0
 *
 */

#ifndef _ARME_H
#define	_ARME_H

#include "entite.h"

/**
 * \class Arme
 * \brief Specialisation de la classe entite a une role fixe
 *
 */
class Arme : public Entite
{
public:
    Arme(int x,int y,Simulator * simu, World * world);
    virtual ~Arme() {}

    virtual void Afficher();

};

#endif	/* _ARME_H */

