/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 14, 2014, 1:48 PM
 */

#include <iostream>
#include <math.h>

#define _USE_MATH_DEFINES

/**
 * Calculates the binomial coefficient, $\choose{n, k}$, i.e., the number of
 * distinct sets of $k$ elements that can be sampled with replacement from a
 * population of $n$ elements.
 *
 * @tparam T
 *   Numeric type. Defaults to unsigned long.
 * @param n
 *   Population size.
 * @param k
 *   Number of elements to sample without replacement.
 *
 * @return
 *   The binomial coefficient, $\choose{n, k}$.
 *
 * @note
 *    Modified from: http://etceterology.com/fast-binomial-coefficients
 */
template <class T>
T binomial_coefficient(unsigned long n, unsigned long k) {
    unsigned long i;
    T b;
    if (0 == k || n == k) {
        return 1;
    }
    if (k > n) {
        return 0;
    }
    if (k > (n - k)) {
        k = n - k;
    }
    if (1 == k) {
        return n;
    }
    b = 1;
    for (i = 1; i <= k; ++i) {
        b *= (n - (k - i));
        if (b < 0) return -1; /* Overflow */
        b /= i;
    }
    return b;
}

double stirling_lower_bound( int n) {
    double n_ = n / 2.0;
    double res = pow( 2.0, 2 * n_);
    res /= sqrt( n_ * M_PI);
    return res * exp( ( -1.0) / ( 6 * n_));
}

double stirling_upper_bound( int n) {
    double n_ = n / 2.0;
    double res = pow( 2.0, 2 * n_) ;
    res /= sqrt( n_ * M_PI);
    return res * exp( 1.0 / ( 24 * n_));
}

int stirling_estimate( double x) {
    int n = 1;
    while ( stirling_lower_bound( n) <= x) {
        if ( stirling_upper_bound( n) > x) return n;
        ++n;
    }
    return n;
}

long int search_coefficient( unsigned long int &n, unsigned long int x) {
    unsigned long int k = n / 2;
    long long middle_coefficient = binomial_coefficient<long long>( n, k);
    if( middle_coefficient == x) return k;

    unsigned long int right = binomial_coefficient<unsigned long>( n, ++k);
    while ( x != right) {
        
        while( x < right ||  x < ( right * ( n + 1) / ( k + 1))) {
            //right = binomial_coefficient<unsigned long>( n, ++k);
            right = right * ( n + 1) / ( ++k) - right;
        }
        if ( right == x) return k;
        right = right * ( ++n) / ( ++k);
        if( right > x) return -1;
    }
    return k;
}
/*
 * 
 */
int main(int argc, char** argv) {
    
    long long x2 = 1365;
    unsigned long int n = stirling_estimate( x2);
    long int k = search_coefficient( n, x2);
    std::cout << "row:" << n <<", column: " << k; 
    return 0;
}

