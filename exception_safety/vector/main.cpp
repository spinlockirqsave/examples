/* 
 * File:   main.cpp
 * Author: piter cf16 eu
 *
 * Created on April 7, 2014, 1:03 PM
 */

#include <iostream>

template<typename T, typename A = std::allocator<T> >
class vector {
    private:
        T* v;        // start of allocation
        T* space;    // end of element sequence, start of space allocated for possible expansion
        T* last;     // end of allocated space
        A alloc;     // allocator
        typedef T       value_type;
        typedef size_t	size_type;
        typedef T* iterator;
    public:
        explicit vector( size_type n, const T& val = T(), const A& = A());
        vector( const vector& other);
        vector& operator=( const vector& other);
        ~vector();
        
        size_type size() const { return space - v; }  // pointer arithmetic
        size_type capacity() const { return last - v; }
        void push_back( const T&);
        //...
};

template<typename T, typename A >
vector<T,A>::vector( size_type n, const T& val, const A& a) : alloc( a)  // copy the allocator
{
    /* keep track of which elements have been constructed
     * and destroy those and only those in case of exception */
    v = alloc.allocate( n); // get memory for elements
    iterator p;             // declared before try{} so it is still valid in catch{} block
    
    try {
        iterator end = v + n;
        for( p = v; p != end; ++p)
            alloc.construct( p, val); /* construct element (placement new):
                                      e g. void construct( pointer p, const T& val) 
                                      { ::new((void *)p) T( val); } */
        last = space = p;
    } catch( ...) {
        for( iterator q = v; q != p; ++q)
            alloc.destroy( q);       /* destroy constructed elements */
        alloc.deallocate( v, n);     /* free memory */
        throw;                       /* re-throw to signal constructor that failed */
    }
   
}

template<typename T, typename A >
void vector<T,A>::push_back( const T& val) {}


/*
 * 
 */
int main(int argc, char** argv) {

    return 0;
}

