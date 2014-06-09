/* 
 * File:   main.c
 * Author: piter
 *
 * Created on June 9, 2014, 1:50 PM
 * 
 * Get prime numbers by exclusion of multiples of 2, 3, ..., n
 * http://en.wikipedia.org/wiki/Sieve_of_Eratosthenes
 */

#include<stdio.h>
#include<math.h>

/*
 * 
 */
int main()
{
    int i, a[50], b[50], j, n = 0, s;
    
    for( i = 0; i < 50; i++)
        a[i] = 1;
    
    a[0] = a[1] = 0; // marked

    for( i = 2; i < sqrt(50); i++)
        if( a[i]) // if not marked
            /* mark starting from i*i because i*j for j<i
             * has been already marked when i was j */
            for( j = i * i; j < 50; j += i)
                a[j] = 0;

    /* choose values based on unmarked elements
     * and put them into result table */
    for( i = 0; i < 50; i++)
        if( a[i]) {
            b[n] = i;
            n++;
        }

    for( j = 0; j < n; j++)
        printf( "%d\n", b[j]);
    
    return 0;
}


