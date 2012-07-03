
#ifndef LABELCARTE_TP5_6_H
#define LABELCARTE_TP5_6_H

#include <QtGui/QLabel>
#include <QtCore/QList>

#include <utility>

#include <interface_qt/idCarte.hpp>

class LabelCarte : public QLabel
{
    Q_OBJECT

    private:
        void chargementCarteVide();
        void chargementCarte( const Valeur::Enum & inVal, const Couleur::Enum & inCoul );

    public:
        explicit LabelCarte( QWidget * inParent = 0 );
        explicit LabelCarte( const Valeur::Enum & inVal, const Couleur::Enum & inCoul, bool inEstCoupe = false, QWidget * inParent = 0 );
        void chargementDerniereCarte( const QList< std::pair< Valeur::Enum, Couleur::Enum > > & inListeCarte );

    signals:

    public slots:

};

#endif // LABELCARTE_TP5_6_H
