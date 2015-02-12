/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 * http://stackoverflow.com/questions/21677292/remainder-when-dividing-large-number/21679387#21679387
 * Created on February 11, 2014, 12:07 PM
 */

#include <cstdio>

using namespace std;

/**
 * by Vikram Bhat
 * Call: modexp(30,74,57) to get (30^74 % 57)
 * Time Complexity: O(log(pow))
 * @param a
 * @param pow
 * @param p
 * @return remainder
 */
long modexp( long a, long pow, long p) {

    if (pow == 0) {
        return (1);
    }

    long t = modexp(a, pow / 2, p);
    t = (t * t) % p;

    if (pow % 2 == 1) {
        t = (t * a) % p;
    }

    return (t);

}

/**
 * by cf16 
 * @param base
 * @param exponent
 * @param modulus
 * @return remainder
 */
long modular_pow( long base, long exponent, long modulus) {
    long c = 1;
    for ( long e_prim = 0; e_prim < exponent; ++e_prim) {
        c = (c * base) % modulus;
    }
    return c;
}

int main(int argc, char** argv) {

    // 30^74 % 57
    printf( "modexp: 30^74 % 57:%ld\n", modexp( 30, 74, 57));
    printf( "modular_pow: 30^74 % 57:%ld", modular_pow( 30, 74, 57));
    return 0;
}

