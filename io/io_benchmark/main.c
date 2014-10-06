/* 
 * File:   main.c
 * Author: peterg
 *
 * Created on October 5, 2014, 1:41 AM
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
      printf( "%lf", d);
#else
      ifstream f( "numbers.txt", ios_base::in);
      if( !f.is_open()) {
          cout << "Cannot open file\n";
          return -1;
      }
    VALUES = atoi( argv[1]);

    for ( ; VALUES; --VALUES) {
      f >> d;
      cout << d << "\t";
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

