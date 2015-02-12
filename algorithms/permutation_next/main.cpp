/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on April 21, 2014, 7:38 PM
 */

#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
 
int main()
{
    std::string s = "aba";
    std::sort(s.begin(), s.end());
    do {
        std::cout << s << '\n';
    } while(std::next_permutation(s.begin(), s.end()));
    
    int a[ 4] = { 1, 2, 3, 4};
    std::vector<int> v( a, a + 4);
    std::sort( v.begin(), v.end());
    do {
        std::copy( v.begin(), v.end(), std::ostream_iterator<int>( std::cout, ","));
        std::cout << std::endl << std::flush;
    } while( std::next_permutation(v.begin(), v.end()));
    
}

