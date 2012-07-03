
#include <interface_qt/gestionnaireImageCarte.hpp>

#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtSvg/QSvgRenderer>

GestionnaireImageCarte::GestionnaireImageCarte()
{
    QImage          image( 82, 115, QImage::Format_ARGB32 );

    image.fill( 0 );

    CarteVide_      = QPixmap::fromImage( image );

    chargementMap();
}

void GestionnaireImageCarte::chargementMap()
{
    QSvgRenderer    renderer( QString( ":/svg-cards.svg" ) );
    QPixmap         pixmap( 82, 115 );
    QPainter        painter( &pixmap );

    for ( int i = 0; i < Valeur::nb_valeur; ++i )
    {
        for ( int j = 0; j < Couleur::nb_couleur; ++j )
        {
            std::string     carte       = Valeur::toString( Valeur::Enum( i ) ) + "_" + Couleur::toString( Couleur::Enum( j ) );

            renderer.render( &painter, carte.c_str() );

            MapCarte_[ std::make_pair( Valeur::Enum( i ), Couleur::Enum( j ) ) ]   = pixmap;
        }
    }

    // Gestion de la face cachée
    renderer.render( &painter, "back" );

    MapCarte_[ std::make_pair( Valeur::dos_v, Couleur::dos_c ) ]   = pixmap;
}

const GestionnaireImageCarte & GestionnaireImageCarte::getGestionnaireImageCarte()
{
    static GestionnaireImageCarte     cardImagesHolder;
    return cardImagesHolder;
}

const QPixmap & GestionnaireImageCarte::getPixmap( const Valeur::Enum & inVal, const Couleur::Enum & inCoul ) const
{
    return MapCarte_.find( std::make_pair( inVal, inCoul ) )->second;
}

const QPixmap & GestionnaireImageCarte::getPixmapVide() const
{
    return CarteVide_;
}
