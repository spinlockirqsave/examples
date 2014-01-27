/* 
 * File:   Pool.h
 * Author: piter cf16.eu
 *
 * Created on January 26, 2014, 3:34 AM
 */

#ifndef POOL_H
#define	POOL_H

class Pool {
    struct Link { Link* next; };
    struct Chunk {
        enum { size = 9 * 0x400 - 16 };
        Chunk* next;
        char mem[size];
    };
    Chunk* chunks;
    const unsigned int esize;
    Link* head;
    
    Pool( Pool const&);           // copy protection
    void operator=( Pool const&); // copy protection
    void grow();                  // make Pool larger

public:
    Pool ( unsigned int n);       // n is the size of element
    ~Pool();

    /* return current head and adjust the head to the next element */
    void* alloc();                // allocate one element
    void free( void* b);          // put an element back into the pool
    void* alloc( unsigned int n); // allocate n elements
};

inline void* Pool::alloc() {
    if ( head == 0) grow();
    Link* p =head;             // return current first element
    head = p->next;            // move the head to next (free to use) one
    return p;                  // but return previous element (previous head)
}

inline void Pool::free(void* b) {
    Link* p = static_cast< Link*>( b);
    p->next = head;            // put b back as the first element
    head = p;
}

inline void* Pool::alloc( unsigned int  n) {
    Link* p = head;             // return current first element
    Link* tmp = head;
    while(n) {
        if ( tmp == 0) {
            grow();
            tmp = head;
        }
        tmp = tmp->next;            // move the head
        --n;
    }
    head = tmp;
    return p;
}

#endif	/* POOL_H */

