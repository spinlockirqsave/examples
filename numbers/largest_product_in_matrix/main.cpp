/* 
 * File:   main.cpp
 * Author: peter cf16 eu
 *
 * Created on February 4, 2014, 2:16 AM
 */

#include <cstdio>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
using namespace std;

typedef vector< vector< int> > Matrix;
typedef Matrix::iterator outIt;
typedef vector< int>::iterator inIt;

void fillMatrix( Matrix& matrix) {
    outIt it = matrix.begin();
    (*it).push_back( 1);
    (*it).push_back( 1);
    (*it).push_back( 2);
    (*it).push_back( 5);
    ++it;
    (*it).push_back( 1);
    (*it).push_back( 5);
    (*it).push_back( 2);
    (*it).push_back( 4);
    ++it;
    (*it).push_back( 1);
    (*it).push_back( 7);
    (*it).push_back( 2);
    (*it).push_back( 3);
    ++it;
    (*it).push_back( 1);
    (*it).push_back( 8);
    (*it).push_back( 2);
    (*it).push_back( 1);
}
    
void printMatrix( Matrix& matrix) {
    outIt it = matrix.begin();
    while ( it != matrix.end()) {
        inIt it2 = (*it).begin();
        while ( it2 != (*it).end()) {
            printf( "%d", *it2);
            ++it2;
        }
        printf( "\n");
        ++it;
    }
}
/**
 * 
 * @param matrix
 * Largest product in row using rolling multiplication
 * @param n number of factors
 * @param v factors of largest product
 * @return largest product
 */
int largestProductInRow( Matrix& matrix, int n, vector< int>& v) {
    if ( n > matrix.size()) return -1;
    int res = 0;
    int N = matrix.size() - n + 1; // number of products in row (or column)
    /* search in rows */
    outIt it = matrix.begin();
    while (it != matrix.end()) {
        inIt it2 = (*it).begin();
        int currN = N;
        int product = 1;
        while (currN) {       // rolling product calculation
            inIt it3 = it2;
            int currn = n;
            if (currN == N) { // compute full product first time
                while (currn) {
                    product *= (*it3++);
                    --currn;
                }
            } else {          // rolling computation
                product *= (*(it3 + n - 1)) / (*(it3 - 1));
                it3 += n;
            }
            if (product > res) {
                res = product;
                copy(it3 - n, it3, v.begin());
            }
            --currN;
            ++it2;
        }
        ++it;
    }
    return res;
}

/*
 * 
 */
int main(int argc, char** argv) {
    
    Matrix matrix( 4, vector< int>());
    fillMatrix( matrix);
    printMatrix( matrix);
    vector< int> v(3);
    int res = largestProductInRow( matrix, 3, v);
    printf( "res:%d\n", res);
    copy( v.begin(), v.end(), ostream_iterator<int>(cout, ","));
    int i = v.size();
    if (v.empty());
    return 0;
}

