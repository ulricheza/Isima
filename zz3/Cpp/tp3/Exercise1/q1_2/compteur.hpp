#ifndef _COMPTEUR_HPP__
#define _COMPTEUR_HPP__

#include <QtCore/QObject>

class Compteur : public QObject
{
    Q_OBJECT
   public:
      explicit Compteur(int valeurInitiale = 0);

      int getValeur() { return valeur_;}

      signals:
      void valeurChangee(int nouvelleValeur);

      public slots:
      void setValeur(int v)
      {
         if(valeur_ != v)
         {
            valeur_ = v;
            emit valeurChangee(valeur_);
         }
      }

   private:
      int valeur_;
};

#endif
