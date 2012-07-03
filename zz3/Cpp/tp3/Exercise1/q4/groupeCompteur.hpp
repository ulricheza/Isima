#ifndef _GROUPECOMPTEUR_HPP__
#define _GROUPECOMPTEUR_HPP__

#include <QtCore/QObject>
#include <QList>

#include "compteur.hpp"

class GroupeCompteur : public QObject
{
   Q_OBJECT
   private:
      QList<Compteur *> _list;

   public:
      signals:
         void valeurChangee(int nouvelleValeur);

   public:
      GroupeCompteur();
      void addCompteur( Compteur * compteur );
      void removeCompteur ( Compteur * compteur );

      void setCompteur( int valeur )
      {
         emit valeurChangee(valeur);
      }

};
#endif
