#include "Line.hpp"

std::istream & operator>>( std::istream & is, Line & l )
{
    std::getline(is, l.str_);
    return is;
}
