#include <interface_qt/idCarte.hpp>

const std::string Valeur::valeur[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "jack", "queen", "king" };

const std::string & Valeur::toString( Enum e )
{
    return valeur[ e ];
}

const std::string Couleur::couleur[] = { "spade", "heart", "diamond", "club" };

const std::string & Couleur::toString( Enum e )
{
    return couleur[ e ];
}
