
#ifndef GESTIONNAIREIMAGECARTE_TP5_6_H
#define GESTIONNAIREIMAGECARTE_TP5_6_H

#include <QPixmap>

#include <interface_qt/idCarte.hpp>

#include <map>
#include <string>
#include <utility>

class GestionnaireImageCarte
{
    private:
        QPixmap      CarteVide_;
        std::map< std::pair< Valeur::Enum, Couleur::Enum >, QPixmap >   MapCarte_;

        GestionnaireImageCarte();
        void chargementMap();

    public:
        static const GestionnaireImageCarte & getGestionnaireImageCarte();
        const QPixmap & getPixmap( const Valeur::Enum & inVal, const Couleur::Enum & inCoul ) const;
        const QPixmap & getPixmapVide() const;
};

#endif // GESTIONNAIREIMAGECARTE_TP5_6_H
