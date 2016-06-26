/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on April 25, 2014, 1:26 PM
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

bool bp (int left, int right) { return ( left + right == 2);
}

template<class ForwardIt, class BinaryPredicate>
ForwardIt removeif1(ForwardIt first, ForwardIt last, BinaryPredicate p) {

    ForwardIt result = first;
    while ( first != last - 1) {
        if ( !p( *first, *( first + 1))) {
            *result = *first;
            ++result;
        }
        if( first == last - 1) return result;
        ++first;
    }
    return result;
}

template<class ForwardIt, class BinaryPredicate>
ForwardIt removeif2(ForwardIt first, ForwardIt last, BinaryPredicate p) {

    ForwardIt result = first;
    while (first != last - 1) {
        if (!p(*first, *(first + 1))) {
            *result++ = *first++;
            *result++ = *first++;
        } else {
            if (first == last - 1) return result;
            ++first;
            ++first;
        }
    }
    return result;
}

/*
 * 
 */
int main(int argc, char** argv) {
    {
    int a[] = { 0, 2, 1, 3, 0, 2, 3, 2, 0, 3, 8};
    std::vector<int> v( a, a + 11);
    std::copy( v.begin(), v.end(), std::ostream_iterator<int>( std::cout, ","));
    std::cout << std::endl;
    std::vector<int>::iterator it = removeif1( v.begin(), v.end(), bp);
    std::copy( v.begin(), v.end(), std::ostream_iterator<int>( std::cout, ","));
    v.erase( it, v.end()); std::cout << std::endl;
    std::copy( v.begin(), v.end(), std::ostream_iterator<int>( std::cout, ","));
    }
    {
    std::cout << std::endl;
    std::cout << std::endl;
    int a[] = { 0, 2, 1, 3, 0, 2, 3, 2, 0, 3, 8};
    std::vector<int> v( a, a + 11);
    std::copy( v.begin(), v.end(), std::ostream_iterator<int>( std::cout, ","));
    std::cout << std::endl;
    std::vector<int>::iterator it = removeif2( v.begin(), v.end(), bp);
    std::copy( v.begin(), v.end(), std::ostream_iterator<int>( std::cout, ","));
    v.erase( it, v.end()); std::cout << std::endl;
    std::copy( v.begin(), v.end(), std::ostream_iterator<int>( std::cout, ","));
    }
    return 0;
}

