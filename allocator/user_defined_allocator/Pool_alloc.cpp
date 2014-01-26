/* 
 * File:   Pool_alloc.cpp
 * Author: piter cf16.eu
 * 
 * Created on January 26, 2014, 3:34 AM
 */

#include "Pool_alloc.h"
#include "Pool.h"

template< class T> Pool Pool_alloc<T>::mem( sizeof(T));

template< class T> 
typename Pool_alloc<T>::pointer Pool_alloc<T>::allocate( size_type n, const void*) {
    if ( n == 1) return static_cast<T*>( mem.alloc());
    return static_cast<T*>( mem.alloc(n));
    //...
}

template< class T> 
void Pool_alloc<T>::deallocate( pointer p, size_type n) {
    if ( n == 1) {
        mem.free( p);
        return;
    }
    //...
}

