/* 
 * File:   main.cpp
 * Author: piter
 *
 * Created on April 18, 2014, 8:24 PM
 */

#include <iostream>
#include <cmath>

/**
 * generates intervals for a uniform distribution
 * with a given mean and deviation
 * @param mi    mean
 * @param d     deviation
 * @param a     left bound
 * @param b     right bound
 * @return 
 */
void uniform_distribution_intervals( double mi, double d, double& a, double& b) {
    a = mi - d * std::sqrt(3.0);
    b = mi + d * std::sqrt(3.0);
}
/*
 * 
 */
int main(int argc, char** argv) {

    double a = 0.0;
    double b = 0.0;
    uniform_distribution_intervals( 60/84, 1.7, a, b);
    return 0;
}

