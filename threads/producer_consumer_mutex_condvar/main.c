/* 
 * File:   main.c
 * Author: peter
 *
 * Using threads to solve producer consumer problem
 * Interprocess Communication, p.133
 * Tanenbaum A., S., "Modern Operating Systems, 3rd edition"
 * 
 * Created on June 7, 2014, 6:38 PM
 */

#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#define MAX 100
pthread_mutex_t the_mutex;
pthread_cond_t condc, condp;
int buffer = 0;                 /* buffer used between consumer and producer */

void *producer( void *ptr) {

    int i = 1;

    for ( ; i <= MAX; i++) {
        
        /* get exclusive access to buffer */
        pthread_mutex_lock( &the_mutex);
        while ( buffer != 0) pthread_cond_wait( &condp, &the_mutex);

        /* put item in buffer */
        buffer = i;
        printf( "producer:%d\n", buffer);
        fflush( stdout);
                
        /* wake up consumer */
        pthread_cond_signal( &condc);
        
        /* release access to buffer */
        pthread_mutex_unlock( &the_mutex);
    }

    pthread_exit(0);
}

void *consumer( void *ptr) {

    int i = 1;

    for ( ; i <= MAX; i++) {
        
        /* get exclusive access to buffer */
        pthread_mutex_lock( &the_mutex);
        while ( buffer == 0) pthread_cond_wait( &condc, &the_mutex);

        /* take item out of buffer */
        buffer = 0;
        printf( "consumer:%d\n", buffer);
        fflush( stdout);

        /* wake up producer */
        pthread_cond_signal( &condp);

        /* release access to buffer */
        pthread_mutex_unlock( &the_mutex);
    }

    pthread_exit(0);
}

/*
 * 
 */
int main(int argc, char** argv) {

    pthread_t pro, con;
    pthread_mutex_init( &the_mutex, 0);
    pthread_cond_init( &condc, 0);
    pthread_cond_init( &condp, 0);
    pthread_create( &con, 0, consumer, 0);
    pthread_create( &pro, 0, producer, 0);
    pthread_join( pro, 0);
    pthread_join( con, 0);
    pthread_cond_destroy( &condc);
    pthread_cond_destroy( &condp);
    pthread_mutex_destroy( &the_mutex);

    return (EXIT_SUCCESS);
}

