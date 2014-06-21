/* 
 * File:   main.c
 * Author: piter cf16 eu
 *
 * Created on June 21, 2014, 12:20 PM
 * 
 * Cases when x - 1 can't be represented other that x
 * Have a nice day.
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main() {
    
    unsigned shift;
    for( shift = 0; shift < 32; ++shift) {
        float base = 1u << shift;
        float other = base - 1.0;
        if( base == other)
            printf( "%f == %f\n", base, other);
        else
            printf( "%f != %f\n", base, other);
    }
    
    float a = 1u << 31;
    printf( "a=%f\n", a);
    float b = a - 1;
    printf( "b=%f\n");
    if( a == b) printf( "a is equal to a - 1!");
    
    return 0;
}

