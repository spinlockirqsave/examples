/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on March 7, 2014, 12:01 AM
 * http://stackoverflow.com/questions/22237322/solve-ax-b-a-lower-triangular-matrix-in-c/22237724?noredirect=1#comment33770886_22237724
 */

#include <iostream>
#include <algorithm>
#include <iterator>

/**
 * solve linear equation system by forward
 * substitution on lower triangular matrix
 * @param n matrix rank (dimension of solution space)
 * @param a lower triangular matrix
 * @param b right side
 * @param x solution
 * http://ktuce.ktu.edu.tr/~pehlivan/numerical_analysis/chap02/BackSubstitution.pdf
 */
void solve1( int n, float a[][4], float b[], float x[]) {
  float s;

  for( int i = 0; i < n; i++) {
        s = 0;
        for( int j = 0; j < i; j++) {
            s = s + a[ i][ j] * x[ j];
        }
        x[ i] = ( b[ i] - s) / a[ i][ i];
   }
}

void solve2( int n, float* a, float b[], float x[]) {
  float s;

  for( int i = 0; i < n; i++) {
        s = 0;
        for( int j = 0; j < i; j++) {
            s = s + a[ i * n + j] * x[ j];
        }
        x[ i] = ( b[ i] - s) / a[ i * n + i];
   }
}

/*
 * 
 */
int main(int argc, char** argv) {

    int n = 4;
    float a[4][4] = { 3, 0, 0, 0, -1, 1, 0, 0, 3, -2, -1, 0, 1, -2, 6, 2};
    float b[4] = { 5, 6, 4, 2};
    float res[4];
    solve1( n, a, b, res);
    std::copy( res, res + 4, std::ostream_iterator<float>( std::cout, ","));
    solve2( n, a[0], b, res); // or solve2( n, &a[0][0], b, res);
    std::copy( res, res + 4, std::ostream_iterator<float>( std::cout, ","));
    return 0;
}