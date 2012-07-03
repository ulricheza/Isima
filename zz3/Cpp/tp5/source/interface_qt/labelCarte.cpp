
#include <interface_qt/labelCarte.hpp>

#include <interface_qt/gestionnaireImageCarte.hpp>

LabelCarte::LabelCarte( QWidget * inParent )
    : QLabel( inParent )
{
    chargementCarteVide();

    setMaximumSize( GestionnaireImageCarte::getGestionnaireImageCarte().getPixmapVide().size() );
    setFrameStyle( QFrame::Box );
    setAlignment( Qt::AlignCenter );
}

LabelCarte::LabelCarte( const Valeur::Enum & inVal, const Couleur::Enum & inCoul, bool inEstCoupe, QWidget * inParent )
    : QLabel( inParent )
{
    chargementCarte( inVal, inCoul );
    if ( inEstCoupe )
    {
        setAlignment( Qt::AlignTop );
        setFixedHeight( 25 );
    }
}

void LabelCarte::chargementCarteVide()
{
    setPixmap( GestionnaireImageCarte::getGestionnaireImageCarte().getPixmapVide() );
}

void LabelCarte::chargementCarte( const Valeur::Enum & inVal, const Couleur::Enum & inCoul )
{
    setPixmap( GestionnaireImageCarte::getGestionnaireImageCarte().getPixmap( inVal, inCoul ) );
}

void LabelCarte::chargementDerniereCarte( const QList< std::pair< Valeur::Enum, Couleur::Enum > > & inListeCarte )
{
    if ( inListeCarte.count() > 0 )
    {
        chargementCarte( inListeCarte.last().first, inListeCarte.last().second );
    }
    else
    {
        setPixmap( GestionnaireImageCarte::getGestionnaireImageCarte().getPixmapVide() );
    }
}
