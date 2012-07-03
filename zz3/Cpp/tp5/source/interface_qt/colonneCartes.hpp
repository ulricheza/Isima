
#ifndef COLONNECARTES_TP5_6_H
#define COLONNECARTES_TP5_6_H

#include <QtGui/QWidget>
#include <QtCore/QList>

#include <utility>

#include <interface_qt/idCarte.hpp>

class ColonneCartes : public QWidget
{
    Q_OBJECT

    public:
        explicit ColonneCartes( QWidget * inParent = 0 );
        explicit ColonneCartes( const QList< std::pair< Valeur::Enum, Couleur::Enum > > & inListeCarte, QWidget * inParent = 0 );

};

#endif // COLONNECARTES_TP5_6_H
