/* 
 * File:   main.cpp
 * Author: piter
 *
 * Created on June 30, 2014, 10:28 PM
 */

#include <stdio.h>
#include <string.h>

    typedef struct STRONGCHECKSUMA { char data[16];
                                    STRONGCHECKSUMA(){}
                                    bool operator==( STRONGCHECKSUMA& other);
                                  } STRONGCHECKSUMA
                                  __attribute__((__aligned__(16)));
    
    typedef struct STRONGCHECKSUMB { char data[16];
                                    STRONGCHECKSUMB(){}
                                    bool operator==( STRONGCHECKSUMB& other);
                                    STRONGCHECKSUMB( STRONGCHECKSUMB const& other);
                                  } STRONGCHECKSUMB
                                  __attribute__((__aligned__(16)));

bool STRONGCHECKSUMA::operator ==( STRONGCHECKSUMA &other)
{
    /* only one byte is compared */
    return ( *data == *other.data);
}

bool STRONGCHECKSUMB::operator ==( STRONGCHECKSUMB &other)
{
    /* now OK */
    return ( 0 == memcmp ( data, other.data, 16));
}

STRONGCHECKSUMB::STRONGCHECKSUMB( const STRONGCHECKSUMB &other)
{
    memcpy( data, other.data, 16);
}
/*
 * 
 */
int main(int argc, char** argv) {
    
    STRONGCHECKSUMA a1, a2;
    memcpy( a1.data, "12775\0", 16);
    memcpy( a2.data, "123456789012345\0", 16);
    if( a1 == a2) printf( "a1 == a2\n");
    
    STRONGCHECKSUMB b1, b2;
    memcpy( b1.data, "12775\0", 16);
    memcpy( b2.data, "123456789012345\0", 16);
    if( b1 == b2) printf( "b1 == b2\n");

    return 0;
}

