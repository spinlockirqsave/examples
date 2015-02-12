/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on June 21, 2014, 12:27 PM
 * 
 * Cases when x - 1 can't be represented other that x
 * Have a nice day.
 * 
 * http://stackoverflow.com/questions/15440052/largest-number-x
 * http://coliru.stacked-crooked.com/view?id=cc0ae3f34df4c559275ba1290458f077-61c3814520a8d4318f681038dc4b4da7
 */

#include <iostream>

int main() {
    for( unsigned shift = 0; shift < 32; ++shift) {
        float base = 1u << shift;
        float other = base-1.0;
        std::cout << base << ( base == other? "==" : "!=") << other << '\n';
    }
}

