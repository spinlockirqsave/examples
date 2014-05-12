/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on May 12, 2014, 12:26 PM
 * 
 * perform circular shift
 */

#include <bitset>
#include <iostream>
#include <stdint.h>

/*
 * 
 */
int main(int argc, char** argv) {

    uint32_t _arg1 = 0xc2034000;
    uint32_t _arg2 = 2;
    std::cout << std::bitset<32>( _arg1) << '\n';
    std::cout << std::bitset<32>( _arg2) << '\n';

    /* c = ((_arg1 << _arg2) | (_arg1 >>> (32 - _arg2))) */
    uint32_t a = _arg1 << _arg2;
    std::cout << std::bitset<32>( a) << '\n';
    
    uint32_t b = _arg1 >> ( 32 - _arg2);
    std::cout << std::bitset<32>( b) << '\n';
    
    uint32_t c = a | b;
    std::cout << std::bitset<32>( c) << '\n';

    std::cout << sizeof(int);
    std::cout << sizeof( uint32_t);
    std::cout << sizeof(double);
    return 0;
}

