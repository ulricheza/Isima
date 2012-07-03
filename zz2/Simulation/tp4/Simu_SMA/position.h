/**
 * \file  position.h
 * \author Maxime Escourbiac
 * \brief fichier d'en-tete de la classe Position
 * \date 1 mars 2010
 * \version 1.0
 * 
 */

#ifndef _POSITION_H
#define	_POSITION_H

/**
 * \class Position
 * \brief Classe avec membres public pour localiser une entite
 *
 */

class Position {
public:
    Position(int x = 0, int y = 0);
    void operator= (const Position & pos);
    int _x;
    int _y;
};

#endif	/* _POSITION_H */

