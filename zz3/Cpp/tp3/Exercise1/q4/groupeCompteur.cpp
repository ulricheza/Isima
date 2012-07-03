#include "groupeCompteur.hpp"

GroupeCompteur::GroupeCompteur()
{
}

void GroupeCompteur::addCompteur( Compteur * compteur )
{
   QObject::connect(this, SIGNAL(valeurChangee(int)),
                    compteur, SLOT(setValeur(int)));
   _list.append(compteur);
}

void GroupeCompteur::removeCompteur( Compteur * compteur )
{
   QObject::disconnect(this, SIGNAL(valeurChangee(int)),
                       compteur, SLOT(setValeur(int)));
   _list.removeAll (compteur);
}

