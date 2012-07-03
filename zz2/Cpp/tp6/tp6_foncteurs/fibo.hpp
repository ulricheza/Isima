/* 
 * File:   fibo.hpp
 * Author: escourbi
 *
 * Created on 23 décembre 2010, 01:46
 */

#ifndef _FIBO_HPP
#define	_FIBO_HPP

class fibo {
private:
    int x;
    int y;
public:
    fibo(): x(1),y(1) {}
    int operator() (void) {
        int temp;
        temp = x + y;
        x = y;
        y = temp;
        return temp;
    } 

};

#endif	/* _FIBO_HPP */

