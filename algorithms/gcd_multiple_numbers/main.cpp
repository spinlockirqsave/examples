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
    std::cout << "numbers:\t";
    std::vector<int> v;
    v.push_back(15);
    v.push_back(5);
    v.push_back(10);
    
    //std::copy( std::istream_iterator<int>( std::cin), std::istream_iterator<int>(),
    //                                                     std::back_inserter( v));

    int result = std::accumulate( v.begin(), v.end(), v[0], gcd);

    std::cout << result << '\n';
    std::cout << v.size() << '\n';
    return 0;
}