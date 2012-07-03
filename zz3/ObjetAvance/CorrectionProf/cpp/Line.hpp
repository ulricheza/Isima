#ifndef BOOST_LINE_HPP
#define BOOST_LINE_HPP

#include <istream>
#include <string>

/**
 * Represents a line. The extraction operator use std::getLine to read a whole line.
 * A line can be implicitely converted to a std::string.
 * Lets us use std::istream_iterator< Line > to read an input stream line by line 
 * instead of word by word.
 */
struct Line
{
    operator std::string() const
    {
        return str_;
    }

  private:
    std::string str_;

    friend std::istream & operator>>( std::istream & is, Line & l );
};

#endif //BOOST_LINE_HPP
