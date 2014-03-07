/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 7, 2014, 6:26 PM
 */

double myPow( double a, int b) {
    if ( b < 0) return myPow( 1 / a, -b);
    if ( b == 0) return 1;
    double result = 1;
    double multiplier = a;

    for (double multiplier = a; b != 0; multiplier *= multiplier, b /= 2) {
        if (b % 2 == 1) {
           result *= multiplier;
        }
    }
    return result;
}
/*
 * 
 */
int main(int argc, char** argv) {

    double u = myPow( 0.25, -2);
    return 0;
}

