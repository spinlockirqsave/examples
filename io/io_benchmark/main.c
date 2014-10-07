/* 
 * File:   main.c
 * Author: peterg
 *
 * Created on October 5, 2014, 1:41 AM
 *
 * Measure & compare io in C or C++ environment.
 
 Results on x64 Windows8 IntelCore2Duo 3.16GHz 3.16GHz
 $ perl run_numbers.pl 
Number of runs:3
Number of numbers to process:500000
C:
real    0m8.352s
user    0m7.035s
sys     0m0.015s

C++:
real    0m9.096s
user    0m7.737s
sys     0m0.015s
-----------------------------------------
C:
real    0m8.270s
user    0m7.144s
sys     0m0.031s

C++:
real    0m9.049s
user    0m7.893s
sys     0m0.015s
-----------------------------------------
C:
real    0m8.168s
user    0m7.160s
sys     0m0.015s

C++:
real    0m9.021s
user    0m7.862s
sys     0m0.046s
-----------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>

#define STDIO

#ifdef STDIO
#include <stdio.h>
#else
#include <iostream>
#include <iomanip>
using namespace std;
#endif


int VALUES;                 // # of values to read/write

/*
 * 
 */
int main(int argc, char** argv)
{
  double d;
  int n = 1;
  if( argc!=2) {
    printf( "usage: program <number of numbers to read>\n");
    return -1;
  }

#ifdef STDIO
    FILE *f;
    f = fopen( "numbers.txt", "r");
    if ( !f) {
      printf( "Cannot open file\n");
      return -1;
}
    VALUES = atoi( argv[1]);

    for ( ; VALUES; --VALUES) {
      fscanf( f,"%lf", &d);
      printf( "%10.5f", d);
#else
      ifstream f( "numbers.txt", ios_base::in);
      if( !f.is_open()) {
          cout << "Cannot open file\n";
          return -1;
      }
    VALUES = atoi( argv[1]);

    for ( ; VALUES; --VALUES) {
      f >> d;
      cout  << setw(10)
      << setprecision(5)
      << setiosflags(ios::showpoint)
      << setiosflags(ios::fixed)
      << d;

#endif

    if (n % 5 == 0) {
#ifdef STDIO
      printf("\n");
#else
      cout << '\n';
#endif
    }
  }

#ifdef STDIO
    fclose( f);
#else
    f.close();
#endif

return (EXIT_SUCCESS);
}

