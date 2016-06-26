/* 
 * File:   Pool.cpp
 * Author: peter 
 * 
 * Created on January 26, 2014, 3:34 AM
 */

#include "Pool.h"

Pool::Pool(unsigned int sz) : esize( sz < sizeof( Link*)? sizeof( Link*): sz) {
    head = 0;
    chunks = 0;
}

Pool::~Pool() {                // free all chunks
    Chunk* n = chunks;
    while ( n) {
        Chunk* p = n;
        n = n->next;
        delete p;
    }
}

/* allocate new chunk, organize it as a linked list of elements of size esize */
void Pool::grow() {
    Chunk* n = new Chunk;
    n->next = chunks;
    chunks = n;
    
    const int nelem = Chunk::size / esize;
    char* start = n->mem;
    char* last = &start[ (nelem-1)*esize];
    for ( char* p = start; p < last; p += esize)
        reinterpret_cast< Link*>(p)->next = reinterpret_cast< Link*>( p + esize);
    reinterpret_cast< Link*>( last)->next = 0;
    head = reinterpret_cast< Link*>( start);
}

