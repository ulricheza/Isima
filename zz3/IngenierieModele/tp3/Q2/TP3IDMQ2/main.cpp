/* 
 * File:   main.cpp
 * Author: escourbi
 *
 * Created on November 9, 2011, 11:25 AM
 */

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>



#include "CLHEP/Random/MTwistEngine.h"

/*
 * 
 */

using CLHEP::MTwistEngine;
using namespace std;

int main(int argc, char** argv) {

    MTwistEngine * generator = new MTwistEngine();
    ostringstream file;

    for(int i = 0 ; i < 10; ++i )
    {
        for(int j = 0; j < 100 ; ++j)
        {
            generator->flat();
        }
        file <<"status" << i;
        generator->saveStatus((file.str().c_str()));
        file.str("");
    }
    return (EXIT_SUCCESS);
}

