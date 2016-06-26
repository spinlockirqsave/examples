/* 
 * File:   main.c
 * Author: peter 
 *
 * Created on June 21, 2014, 12:20 PM
 * 
 * Cases when x - 1 can't be represented other that x
 * Have a nice day.
 * 
 * http://stackoverflow.com/questions/15440052/largest-number-x
 * http://coliru.stacked-crooked.com/view?id=cc0ae3f34df4c559275ba1290458f077-61c3814520a8d4318f681038dc4b4da7
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

