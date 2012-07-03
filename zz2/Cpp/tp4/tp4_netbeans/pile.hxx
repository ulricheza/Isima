/* 
 * File:   pile.hxx
 * Author: escourbi
 *
 * Created on November 10, 2010, 11:31 AM
 */

#ifndef _PILE_HXX
#define	_PILE_HXX

template <typename T>
class Pile{
    private:
        T * _tab;
        int _index;
        int _taille_max;
    public:
        Pile(int taille_max = 50);
        virtual ~Pile();
        //getter
        int getTAILLE_MAX() const {return _taille_max;}
        int size()          const {return (_index+1);}
        T   head()          const {return _tab[_index];}
        //methodes specifique a la pile
        bool empty()        const {return (_index==-1);}
        bool full()         const {return (_index==_taille_max-1);}
        bool empiler(const T&);
        T depiler();
};

#include "pile.cxx"

#endif	/* _PILE_HXX */

