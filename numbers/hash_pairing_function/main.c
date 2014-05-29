/* 
 * File:   main.c
 * Author: piter cf16 eu
 *
 * Created on May 29, 2014, 3:24 PM
 * http://stackoverflow.com/questions/23933808/what-is-a-fast-data-structure-to-implement-a-pair-storage-as-specified-here/23933876#23933876
 * http://en.wikipedia.org/wiki/Cantor_pairing_function#Cantor_pairing_function
 * http://szudzik.com/ElegantPairing.pdf
 */

#include <stdio.h>
#include <stdlib.h>

int cantor_pairing( int k1, int k2) {
    return 0.5 * ( k1 + k2) * ( k1 + k2 + 1) + k2;
}

int szuzik_pairing( int x, int y) {
    if( x < 0 || y < 0) return -1;
    return x >= y ? x * x + x + y : x + y * y;
}
/*
 * 
 */
int main(int argc, char** argv) {

    return (EXIT_SUCCESS);
}

