#include <interface_qt/idZone.hpp>

#include <algorithm>

const std::string Zone::zone[ ] = {
                                    "Pioche",
                                    "Defausse",
                                    "Dock 1",
                                    "Dock 2",
                                    "Dock 3",
                                    "Dock 4",
                                    "Colonne 1",
                                    "Colonne 2",
                                    "Colonne 3",
                                    "Colonne 4",
                                    "Colonne 5",
                                    "Colonne 6",
                                    "Colonne 7"
                                  };

const std::string & Zone::toString( Enum e )
{
    return zone[ e ];
}

Zone::Enum Zone::stringtoZone( const std::string & inZone )
{
    const std::string * ite = find( zone, zone + nb_zone, inZone );
    return Zone::Enum( std::distance( zone, ite ) );
}
