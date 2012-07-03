#ifndef _GROUPECOMPTEUR_HPP__
#define _GROUPECOMPTEUR_HPP__

#include <QtCore/QObject>
#include <QList>

#include "compteur.hpp"

class GroupeCompteur : public QObject
{
   private:
      QList<Compteur *> _list;

   public:
      GroupeCompteur();
      void addCompteur( Compteur * compteur );
      void removeCompteur ( Compteur * compteur );
};
#endif
