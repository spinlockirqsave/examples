/*
 * File:   main.cpp
 * Author: peter cf16.eu
 * Created on March 24, 2014, 1:06 AM
 */

#include <iostream>
#include <numeric>
#include <algorithm>
#include <vector>
#include <iterator>

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

int lcm(int a, int b)
{
    int temp = gcd(a, b);

    return temp ? (a / temp * b) : 0;
}

int main( int argc, char** argv)
{
    if ( argc < 3) std::cout << "Program has to be called with 2 arguments at least\n";
    
    std::vector<int> v;
    std::copy( std::istream_iterator<int>( std::cin), std::istream_iterator<int>(),
                                                         std::back_inserter( v));

    int result = std::accumulate( v.begin(), v.end(), 1, lcm);

    std::cout << result << '\n';
}