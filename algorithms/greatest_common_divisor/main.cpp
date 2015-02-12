/*
 * File:   main.cpp
 * Author: peter cf16.eu
 * Created on March 24, 2014, 1:06 AM
 */

#include <iostream>
#include <stdio.h>

/* standard */
int 
gcd ( int a, int b )
{
  int c;
  while ( a != 0 ) {
     c = a; a = b%a;  b = c;
  }
  return b;
}

/* recursive */
int 
gcdr(int a, int b)
{
        if (a == 0) return b;
        return gcdr ( b%a, a );
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

