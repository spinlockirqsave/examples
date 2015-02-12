/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on March 16, 2014, 12:55 AM
 */

#include <iostream>
#include <cmath>

/**
 * 
 * @return area of triangle based on Heron formula
 */
double areaOfTriangle( double edge1, double edge2, double edge3) {
    double s = 0.5 * ( edge1 + edge2 + edge3);
    return std::sqrt( s * ( s - edge1) * ( s - edge2) * ( s - edge3));
}

/**
 * U, V, W, u, v, w are lengths of edges of the tetrahedron
 * as in 
 * http://en.wikipedia.org/wiki/Tetrahedron
 * @param U basis edge 1
 * @param V basis edge 2
 * @param W basis edge 3
 * @param u opposite to U
 * @param v opposite to V
 * @param w opposite to W
 * @return boolean value indicating if 4 points belong to the same plane or not
 */
bool heron_3d( double U, double V, double W,
               double u, double v, double w) {
    double areas[4] = { areaOfTriangle( U, V, W),
                        areaOfTriangle( U, v, w),
                        areaOfTriangle( V, u, w),
                        areaOfTriangle( W, u, v)};
    for ( int i = 0; i < 4; ++i) {
        double area = areas[ i];
        double sum = 0;
        for ( int j = 1; j < 4; ++j) {
            sum += areas[ (i + j) % 4];
        }
        if ( area == sum) return true;
    }
    return false;
}
/*
 * 
 */
int main(int argc, char** argv) {

    bool b0 = heron_3d( 3, 3, 0, 5, 5, 4);  // true
    bool b1 = heron_3d( 3, 3.1, 0.1, 5.1, 5, 4); // false
    bool b2 = heron_3d( 3, 5, 2, std::sqrt( 16 + 25), 5, 4); // true
    bool b3 = heron_3d( 9.8994949366, 12.3288280059, 11.0453610172,
                           2.8284271247, 8.8317608663, 12.3288280059);  // fail due to floating point arithmetic
    return 0;
}

