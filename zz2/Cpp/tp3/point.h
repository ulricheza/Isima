/* 
 * File:   point.h
 * Author: escourbi
 *
 * Created on November 3, 2010, 10:17 AM
 */

#ifndef _POINT_H
#define	_POINT_H

class Point {
public:
    Point(int x = 0,int y = 0);
    ~Point() {};
    int getX() {return _x;}
    int getY() {return _y;}
    void setX(int x) { _x = x;}
    void setY(int y) {_y = y;}
    void add(Point p);
private:
    int _x;
    int _y;
};

#endif	/* _POINT_H */

