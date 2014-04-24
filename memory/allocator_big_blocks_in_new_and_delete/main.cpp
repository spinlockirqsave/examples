/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 24, 2014, 1:24 PM
 */

     /* 
     * operator new and operator delete must be written
     * in concert so that they share the same assumptions
     */
#include <iostream>

class AirplaneRep {             // representation for an Airplane object
};

class Airplane {                // modified class — now supports
public:                         // custom memory management

    static void * operator new( size_t size);
    static void operator delete( void* deadObject, size_t size);

    //...

private:

    union {
        AirplaneRep *rep; // for objects in use
        Airplane *next; // for objects on free list
    };

    // this class-specific constant specifies how
    // many Airplane objects fit into a big memory block;
    // it's initialized below
    static const int BLOCK_SIZE;

    static Airplane *headOfFreeList;

};

Airplane *Airplane::headOfFreeList;     // static members are initialized to 0 by default
const int Airplane::BLOCK_SIZE = 512;

void * Airplane::operator new( size_t size) {
    
    // send requests of the "wrong" size to ::operator new()
    if ( size != sizeof( Airplane))
        return ::operator new(size);

    Airplane *p =               // p is now a pointer to the
            headOfFreeList;     // head of the free list

    // if p is valid, just move the list head to the
    // next element in the free list
    if ( p)
        headOfFreeList = p->next;

    else {
        // The free list is empty. Allocate a block of memory
        // big enough to hold BLOCK_SIZE Airplane objects
        Airplane *newBlock =
                static_cast<Airplane*> ( ::operator new( BLOCK_SIZE *
                                                sizeof ( Airplane)));

        // form a new free list by linking the memory chunks
        // together; skip the zeroth element, because you'll
        // return that to the caller of operator new
        for ( int i = 1; i < BLOCK_SIZE - 1; ++i)
            newBlock[ i].next = &newBlock[ i + 1];

        // terminate the linked list with a null pointer
        newBlock[BLOCK_SIZE - 1].next = 0;

        // set p to front of list, headOfFreeList to
        // chunk immediately following
        p = newBlock;
        headOfFreeList = &newBlock[ 1];
    }

    return p;
}

// operator delete is passed a memory chunk, which,
// if it's the right size, is just added to the
// front of the list of free chunks

void Airplane::operator delete( void *deadObject,
        size_t size) {
    if ( deadObject == 0) return;    // delete on NULL pointer: OK

    if ( size != sizeof( Airplane)) { // forward to global delete
        ::operator delete( deadObject);
        return;
    }

    Airplane *carcass =
            static_cast<Airplane*> ( deadObject);

    carcass->next = headOfFreeList;
    headOfFreeList = carcass;
    
    /* memory leak: we are never returning allocated blocks
     * what should be done when application exits or similar
     * For this purpose we should use static Pool object 
     */
}





/*
 * 
 */
int main(int argc, char** argv) {
    
    Airplane *pa = new Airplane;        // calls Airplane::operator new

    /* calls ::operator delete
     * if delete was not overloaded for Airplane
     * to accompany overloaded new then oooooops,
     * problem: pa doesn't contain header information
     * 
     * operator new and operator delete must be written
     * in concert so that they share the same assumptions
     */
    delete pa;  // OK as delete is overloaded properly

     /* memory leak: we are never returning allocated blocks
     * what should be done when application exits or similar
     * For this purpose we should use static Pool object 
     */
    return 0;
}