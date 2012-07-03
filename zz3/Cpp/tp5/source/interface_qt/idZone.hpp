#ifndef IDZONE_TP5_6_H
#define IDZONE_TP5_6_H

#include <string>


struct Zone
{
    enum Enum
    {
        pioche,
        defausse,
        dock1,
        dock2,
        dock3,
        dock4,
        colonne1,
        colonne2,
        colonne3,
        colonne4,
        colonne5,
        colonne6,
        colonne7,
        nb_zone
    };

    static const std::string & toString( Enum e );
    static Zone::Enum stringtoZone( const std::string & inZone );

    private:
       static const std::string zone[];
};

#endif
