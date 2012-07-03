/* 
 * File:   gene_alea.hpp
 * Author: escourbi
 *
 * Created on 23 décembre 2010, 01:39
 */

#ifndef _GENE_ALEA_HPP
#define	_GENE_ALEA_HPP

#include "cstdlib"

class gene_alea {
private:
    int _min;
    int _max;
public:
    gene_alea(int min,int max): _min(min),_max(max) {}
    int operator() (void) { return(rand() %(_max-_min) + _min);}
};

#endif	/* _GENE_ALEA_HPP */

