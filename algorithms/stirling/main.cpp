/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 14, 2014, 1:48 PM
 */

#include <iostream>
#include <math.h>

#define _USE_MATH_DEFINES

double stirling_lower_bound( int n) {
    double n_ = n / 2.0;
    double res = pow( 2.0, 2 * n_);
    res /= sqrt( n_ * M_PI);
    return res * exp( ( -1.0) / ( 6 * n_));
}

double stirling_upper_bound( int n) {
    double n_ = n / 2.0;
    double res = pow( 2.0, 2 * n_) ;
    res /= sqrt( n_ * M_PI);
    return res * exp( 1.0 / ( 24 * n_));
}

int stirling_estimate( double x) {
    int n = 1;
    while ( stirling_lower_bound( n) <= x) {
        if ( stirling_upper_bound( n) > x) return n;
        ++n;
    }
    return n;
}
/*
 * 
 */
int main(int argc, char** argv) {

    int n = 1;
    double x1 = 20;
    std::cout << "Stirling estimate: " << stirling_estimate( x1);
    
    double x2 = pow( 10, 100);
    std::cout << "Stirling estimate: " << stirling_estimate( x2);
    return 0;
}

