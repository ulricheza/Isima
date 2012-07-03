/* 
 * File:   Iterator.cpp
 * Author: maxime
 * 
 * Created on 11 octobre 2011, 14:26
 */

#include "Iterator.h"
#include "Vecteur.h"

Iterator::Iterator(int * target) : _target(target)
{
}

int Iterator::operator *()
{
    return *_target;
}

bool Iterator::operator ==(const Iterator& it)
{
    return (*_target == *(it._target));
}

Iterator Iterator::operator ++(int)
{
    Iterator res(_target++);
    return res;
}

Iterator & Iterator::operator ++()
{
    ++_target;
    return(*this);
}