/* 
 * File:   main.c
 * Author: peter 
 *
 * Created on June 26, 2014, 1:11 AM
 * http://stackoverflow.com/questions/726756/print-two-dimensional-array-in-spiral-order
 */

#include <stdio.h>
#include <stdlib.h>



/* function to print the top-right peel of the matrix and 
 * recursively call the print bottom-left on the submatrix */
void printTopRight( size_t sz, int a[][sz], int x1, int y1, int x2, int y2) {
    
    int i = 0, j = 0;

    // print values in the row.
    for( i = x1; i <= x2; i++) {
        printf( "%d ", a[y1][i]);
    }

    // print values in the column.
    for( j = y1 + 1; j <= y2; j++)         {
        printf( "%d ", a[j][x2]);
    }

    /* if more layers need to be printed */
    if( x2 - x1 > 0) {
        
        /* if yes - recursively call the function to
         * print the bottom left of the sub matrix */
        printBottomLeft( sz, a, x1, y1 + 1, x2 - 1, y2);
    }
}

/* function to print the bottom-left peel of the matrix and
 * recursively call the print top-right on the submatrix */
void printBottomLeft( size_t sz, int a[][sz], int x1, int y1, int x2, int y2) {
    
    int i = 0, j = 0;

    /* print the values in the row in reverse order */
    for( i = x2; i >= x1; i--) {
        printf( "%d ", a[y2][i]);
    }

    /* print the values in the col in reverse order */
    for( j = y2 - 1; j >= y1; j--) {
        printf( "%d ", a[j][x1]);
    }

    /* see if more layers need to be printed */
    if( x2 - x1 > 0) {
        
        /* if yes recursively call the function to
         * print the top right of the sub matrix */
        printTopRight( sz, a, x1+1, y1, x2, y2-1);
    }
}

void printSpiral( size_t sz, int arr[][sz]) {
    
    /* do it all */
    printTopRight( sz, arr,0,0, sz - 1, sz - 1);
}

/*
 * 
 */
int main() {
    
    int sz = 4;
    int a[sz][sz];
    
    //populating the array with the corresponding indices from 0 to 15
    int m = 1, i = 0;
    
    for ( i = 0; i < sz; i++){
        
        int j = 0;
        for ( j= 0; j < sz; j++) {
            a[i][j] =  m;
            m++;
        }
    }

    /*
   0  1  2  3
  ----------
0| 1  2  3  4
1| 5  6  7  8
2| 9 10 11 12
3|13 14 15 16
     */

    printSpiral( sz, a); /* do it all */
    // prints: 1 2 3 4 8 12 16 15 14 13 9 5 6 7 11 10 

    return 0;
}
