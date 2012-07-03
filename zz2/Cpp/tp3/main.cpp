/* 
 * File:   main.cpp
 * Author: escourbi
 * 
 * Created on November 4, 2010, 10:14 AM
 */

#include "circle.h"
#include "line.h"
#include "rectangle.h"


int main(int, char**)
{
   Point B(2,3);
   Circle A(B,4);
   A.display();
   std::string s = A.toString();
   std::cout << s << std::endl;
   return 0;
}