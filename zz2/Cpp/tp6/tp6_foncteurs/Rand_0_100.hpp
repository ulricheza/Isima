/* 
 * File:   Rand_0_100.hpp
 * Author: escourbi
 *
 * Created on 22 décembre 2010, 16:47
 */

#ifndef _RAND_0_100_HPP
#define	_RAND_0_100_HPP

#include <cstdlib>

class Rand_0_100 {
private :
    unsigned short a;
public:
    Rand_0_100(){}
    unsigned short operator() (void) {return (rand() %101);}
};

#endif	/* _RAND_0_100_HPP */

