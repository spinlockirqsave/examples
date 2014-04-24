/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 24, 2014, 10:15 PM
 */

/* 
* operator new and operator delete must be written
* in concert so that they share the same assumptions
*/
#include <iostream>

template< class T, class U>
class Pool {
public:

    Pool( size_t blockSize);             // Create an allocator for
                                         // objects of size sizeof( T)


    void * alloc( size_t size);          // Allocate enough memory
                                         // for one object; follow
                                         // operator new conventions
                                         // from Item 8

    void free(  void *p, size_t size);   // Return to the pool the
                                         // memory pointed to by p;
                                         // follow operator delete
                                         // conventions from Item 8

    ~Pool();                             // Deallocate all memory in
                                         // the pool
private:
    
    const int SIZE;
    
    // this class-specific constant specifies how
    // many T objects fit into a big memory block;
    // it's initialized below
    const int BLOCK_SIZE;
    
// this has been moved to template base:
//    union {
//        U *rep;    // for objects in use
//        T *next;   // for objects on free list
//    };

    static T* headOfFreeList;
};

template< class T, class U>
Pool<T,U>::Pool( size_t blockSize) : SIZE( sizeof(T)), BLOCK_SIZE( blockSize) {}

template< class T, class U>
Pool<T,U>::~Pool() {
    if( headOfFreeList)
        ::operator delete( headOfFreeList);
}

class AirplaneRep {             // fake representation for an Airplane object
};

template< class T, class U>
class PoolFriendly {
protected:
    union {
        U *rep;             // for objects in use
        T *next; // for objects on free list
    };    
};

class Airplane : PoolFriendly<Airplane,AirplaneRep> {   // modified class — now supports
public:                                                 // custom memory management

    static void * operator new( size_t size);
    static void operator delete( void* deadObject, size_t size);

    //...

private:
    friend class Pool<Airplane,AirplaneRep>;
    static Pool<Airplane,AirplaneRep> memoryPool;
};

inline void * Airplane::operator new( size_t size) {
    return memoryPool.alloc( size);
}

inline void Airplane::operator delete( void *p, size_t size) {
    memoryPool.free( p, size);
}

template< class Airplane, class AirplaneRep>
Airplane* Pool<Airplane,AirplaneRep>::headOfFreeList;     // static members are initialized to 0 by default

// create a new pool for Airplane objects; this goes in
// the class implementation file
Pool<Airplane,AirplaneRep> Airplane::memoryPool( 512);


template< class T, class U>
void * Pool<T,U>::alloc( size_t size) {
    
    // send requests of the "wrong" size to ::operator new()
    if ( size != SIZE)
        return ::operator new( size);

    T *p =                      // p is now a pointer to the
            headOfFreeList;     // head of the free list

    // if p is valid, just move the list head to the
    // next element in the free list
    if ( p)
        headOfFreeList = p->next;

    else {
        // The free list is empty. Allocate a block of memory
        // big enough to hold BLOCK_SIZE Airplane objects
        T *newBlock =
                static_cast<T*> ( ::operator new( BLOCK_SIZE *
                                                sizeof ( T)));

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
template< class T, class U>
void Pool<T,U>::free(  void *p, size_t size) {
    if ( p == 0) return;    // delete on NULL pointer: OK

    if ( size != SIZE) {    // forward to global delete
        ::operator delete( p);
        return;
    }

    T *carcass =
            static_cast<T*> ( p);

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

