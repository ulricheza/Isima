#include <groupeCompteur.hpp>

GroupeCompteur::GroupeCompteur()
{
}

void GroupeCompteur::addCompteur( Compteur * compteur )
{
   QList<Compteur*>::iterator it;

   for(it = _list.begin(); it != _list.end() ; ++it)
   {
       QObject::connect(compteur, SIGNAL(valeurChangee(int)),
                        (*it), SLOT(setValeur(int)));
       QObject::connect((*it), SIGNAL(valeurChangee(int)),
                        compteur, SLOT(setValeur(int)));
   }

   _list.append(compteur);
}

void GroupeCompteur::removeCompteur( Compteur * compteur )
{
   QList<Compteur*>::iterator it;

   _list.removeAll (compteur);

   for(it = _list.begin(); it != _list.end() ; ++it)
   {
       QObject::disconnect(compteur, SIGNAL(valeurChangee(int)),
                           (*it), SLOT(setValeur(int)));
       QObject::disconnect((*it), SIGNAL(valeurChangee(int)),
                           compteur, SLOT(setValeur(int)));
   }
}

