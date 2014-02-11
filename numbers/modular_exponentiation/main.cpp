/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on February 11, 2014, 12:07 PM
 */

#include <cstdio>

using namespace std;

/**
 * Call: modexp(30,74,57) to get (30^74 % 57)
 * Time Complexity: O(log(pow))
 * @param a
 * @param pow
 * @param p
 * @return 
 */
long modexp(long a, long pow, long p) {

    if (pow == 0) {
        return (1);
    }

    long t = modexp(a, pow / 2, p);
    t = (t * t) % p;

    if (pow % 2 == 1) {
        t = (t * a) % p;
    }

    return (t);

}

int main(int argc, char** argv) {

    // 30^74 % 57
    printf( "30^74 % 57:%ld", modexp( 30, 74, 57));
    return 0;
}

