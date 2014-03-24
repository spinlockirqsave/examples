/*
 * File:   main.cpp
 * Author: piter cf16.eu
 * Created on March 24, 2014, 1:06 AM
 */

#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <iterator>
#include <limits>
#include <stdio.h>
int gcd(int a, int b)
{
    for (;;)
    {
        if (a == 0) return b;
        b %= a;
        if (b == 0) return a;
        a %= b;
    }
}

//int lcm(int a, int b)
//{
//    int temp = gcd(a, b);
//
//    return temp ? (a / temp * b) : 0;
//}

int main( int argc, char** argv)
{
    if ( argc < 3) {
        std::cout << "Program has to be called with 2 integers.\n";
        return -1;
    }
    
    int a = *(argv[1]);
    int b = *(argv[2]);

    std::cout << gcd( a, b) << '\n';
    return 0;
}

