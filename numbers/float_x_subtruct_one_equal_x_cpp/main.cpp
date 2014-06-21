/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on June 21, 2014, 12:27 PM
 * 
 * Cases when x - 1 can't be represented other that x
 * Have a nice day.
 */

#include <iostream>

int main() {
    for( unsigned shift = 0; shift < 32; ++shift) {
        float base = 1u << shift;
        float other = base-1.0;
        std::cout << base << ( base == other? "==" : "!=") << other << '\n';
    }
}

