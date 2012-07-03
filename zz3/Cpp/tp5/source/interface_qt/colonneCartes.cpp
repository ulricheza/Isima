
#include <interface_qt/colonneCartes.hpp>

#include <QtGui/QVBoxLayout>
#include <QLayout>
#include <QtGui/QImage>
#include <QtGui/QPixmap>

#include "labelCarte.hpp"

ColonneCartes::ColonneCartes( QWidget * inParent )
    : QWidget( inParent )
{
    QVBoxLayout *   layout      = new QVBoxLayout;

    layout->addWidget( new LabelCarte );

    setLayout( layout );
}

ColonneCartes::ColonneCartes( const QList< std::pair< Valeur::Enum, Couleur::Enum > > & inListeCarte, QWidget * inParent )
    : QWidget( inParent )
{
    QVBoxLayout *   layout      = new QVBoxLayout;

    if ( inListeCarte.count() != 0 )
    {
        layout->setSpacing( 0 );
        for ( int i = 0; i < inListeCarte.count() - 1; ++i )
        {
            layout->addWidget(
                               new LabelCarte(
                                               inListeCarte.at( i ).first,
                                               inListeCarte.at( i ).second,
                                               true
                                             )
                             );
        }
        layout->addWidget(
                           new LabelCarte(
                                           inListeCarte.last().first,
                                           inListeCarte.last().second
                                         )
                         );
        layout->addStretch( 1 );
    }
    else
    {
        layout->addWidget( new LabelCarte );
        layout->addStretch( 1 );
    }

    setLayout( layout );
}
