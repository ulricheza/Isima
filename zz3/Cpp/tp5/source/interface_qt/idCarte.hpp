#ifndef IDCARD_TP5_6_H
#define IDCARD_TP5_6_H

#include <string>

struct Valeur
{
    enum Enum
    {
        un,
        deux,
        trois,
        quatre,
        cinq,
        six,
        sept,
        huit,
        neuf,
        dix,
        valet,
        reine,
        roi,
        nb_valeur,
        dos_v
    };

    static const std::string & toString( Enum e );

    private:
       static const std::string valeur[];
};

struct Couleur
{
    enum Enum
    {
        pique,
        coeur,
        carreau,
        trefle,
        nb_couleur,
        dos_c
    };

    static const std::string & toString( Enum e );

    private:
       static const std::string couleur[];
};

#endif
