/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 * by Prokopi Nikolaev
 * http://geom3d.com/data/documents/Calculation=20of=20Euler=20angles.pdf
 * Created on February 7, 2014, 9:57 AM
 */

#include <math.h> 
#include <float.h> 
 
#define PI 3.141592653589793 

/**
 * @function
 * @param X1x
 * @param X1y
 * @param X1z X1 vector coordinates
 * @param Y1x
 * @param Y1y
 * @param Y1z Y1 vector coordinates
 * @param Z1x
 * @param Z1y
 * @param Z1z Z1 vector coordinates
 * @param pre precession rotation
 * @param nut nutation rotation
 * @param rot intrinsic rotation
 */
void lcs2Euler(
        double X1x, double X1y, double X1z,
        double Y1x, double Y1y, double Y1z,
        double Z1x, double Z1y, double Z1z,
        double *pre, double *nut, double *rot) {
    double Z1xy = sqrt(Z1x * Z1x + Z1y * Z1y);
    if (Z1xy > DBL_EPSILON) {
        *pre = atan2(Y1x * Z1y - Y1y*Z1x, X1x * Z1y - X1y * Z1x);
        *nut = atan2(Z1xy, Z1z);
        *rot = -atan2(-Z1x, Z1y);
    }
    else {
        *pre = 0.;
        *nut = (Z1z > 0.) ? 0. : PI;
        *rot = -atan2(X1y, X1x);
    }
}

int main( int argc, char** argv) {
    return 0;
}

