/* 
 * File:   Iterator.h
 * Author: maxime
 *
 * Created on 11 octobre 2011, 14:26
 */

#ifndef _ITERATOR_H
#define	_ITERATOR_H

class Iterator {
public:
    Iterator() {}
    Iterator(int * target);
    virtual ~Iterator() {}

    //surcharge d'operateur
    Iterator & operator++();
    Iterator operator ++(int);
    int operator*();
    bool operator== (const Iterator & it);

private:

    int * _target;

};

#endif	/* _ITERATOR_H */

