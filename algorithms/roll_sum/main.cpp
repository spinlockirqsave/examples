/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on April 25, 2014, 11:36 AM
 */

#include <iostream>
#include <cassert>

template< int N>
int f1( int k, int (&a)[N]) {
    int sum = 0;
    for ( int i = 0; i <= N - k; ++i) {
        for (int j = 0; j < k; ++j)
            sum += a[i + j];
    }
    return sum;
}

template< int N>
int f2( int k, int (&a)[N]) {
    if( k < 1) return -1;
    int sum = 0;
    
    /* sum values repeated 1, 2, ..., k times
     * starting from begin */
    for ( int i = 0; i <= k - 2; ++i) {
        sum += ( i + 1) * a[ i];
    }

    /* sum values repeated full k times
     * in the middle */
    for ( int i = k - 1; i <= N - k; ++i) {
        sum += k * a[ i];
    }
    
    /* sum values repeated 1, 2, ..., k - 1 times
     * starting from end  */
    for ( int i = 1; i <= k - 1; ++i) {
        sum += ( k - i) * a[ N - k + i];
    }
    return sum;
} 
/*
 * 
 */
int main(int argc, char** argv) {

    int array[] = { 1, 2, 3, 6, 43, 2, 0, 0, 18, 20};
    int res1 = 0, res2 = 0;
    res1 = f1( 3, array);
    res2 = f2( 3, array);
    
    assert(res1 == res2);
    return 0;
}

