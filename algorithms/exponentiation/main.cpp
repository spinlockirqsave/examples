/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 7, 2014, 6:26 PM
 */

double myPow( double a, int b) {
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

    double u = myPow( 3, 2);
    return 0;
}

