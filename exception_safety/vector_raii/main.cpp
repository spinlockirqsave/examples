/* 
 * File:   main.cpp
 * Author: peter 
 *
 * Created on April 7, 2014, 3:57 PM
 */

#include <iostream>
#include <algorithm>

/* key resource required by the vector is memory to hold its elements
 * we provide an auxiliary class to represent the notion of memory 
 * decreasing the chance of accidentaly forgetting to release it.
 * Class vector_base deals with *** memory for a type T ***,
 * not for *** objects of type T ***.
 * Consequently, a user of vector_base must *destroy* all constructed objects
 * in vector_base before the vector_base itself is destroyed:
 * call destructors for objects in ~vector(),
 * deallocate memory in ~vector_base().
 * 
 * vector_base is written so that if an exception is thrown
 * (by the allocator's copy ctor or allocate() function)
 * no vector_base object is created and no memory is leaked
 */
template<typename T, typename A = std::allocator<T> >
struct vector_base {
        A alloc;     // allocator
        T* v;        // start of allocation
        T* space;    // end of element sequence, start of space allocated for possible expansion
        T* last;     // end of allocated space
        typedef T       value_type;
        typedef size_t	size_type;
        typedef T* iterator;
        
        vector_base( const A& a, typename A::size_type n) :
        alloc( a), v( a.allocate( n)), space( v + n), last( v + n) {}
        /* as long as v and last are correct vector_base can be destroyed,
           assume destructors have been called already */
        ~vector_base() { alloc.deallocate( v, last - v); }
};

/* swap without copying/destroying a temporary
 * Becuase vector_base is a special-purpose class
 * that wasn't given fool-proof copy semantics,
 * that destruction of temporary would lead to
 * undesirable side effects
 * note: just swaping representation
*/
template<class T>
void swap( vector_base<T>& a, vector_base<T>& b) {
    std::swap( a.alloc, b.alloc);
    std::swap( a.v, b.v);
    std::swap( a.space, b.space);
    std::swap( a.last, b.last);
}

/* improved implementation of vector 
 * using uninitialized_fill directly
 * and vector_base for RAII */
template<typename T, typename A = std::allocator<T> >
class vector : private vector_base<T,A> {

    typedef typename vector_base<T,A>::size_type size_type;

    public:
        explicit vector( size_type n, const T& val = T(), const A& = A());
        vector( const vector& other);
        vector& operator=( const vector& other);
        /* explicitly invoke destructors
         * If element destructor throws an exception, the vector destruction fails.
         * This will be disaster if it happens during stack unwinding caused by an
         * exception, and std::terminate() is called.
         * In the case of normal destruction, throwing an exception from a destructor
         * typically leads to resource leaks and unpredictable behavior of code relying
         * on reasonable behavior of objects. There is no really good way to protect
         * against exceptions thrown from destructors, so the library
         * makes no guarantees if an element destructor throws */
        ~vector() { destroy_elements();}
        
        size_type size() const { return space - v; }  // pointer arithmetic
        size_type capacity() const { return last - v; }
        void push_back( const T&);
        //...
    private:
        using vector_base<T,A>::alloc;
        using vector_base<T,A>::v;
        using vector_base<T,A>::space;
        using vector_base<T,A>::last;
        
        void destroy_elements() {
            for( T* p = v; p != space; ++p) {
                p->~T();
            }
        }
};

/* approach using uninitialized_fill directly */
template<typename T, typename A >
vector<T,A>::vector( size_type n, const T& val, const A& a)
      : vector_base<T,A>( a, n)  // allocate space for n elements
{
        std::uninitialized_fill( v, v + n, val); /* copy elements with (placement new):
                                                  e g. void construct( pointer p, const T& val) 
                                                  { ::new((void *)p) T( val); } */
}

/* Copy constructor differs by using uninitialized_copy
 * instead of uninitialized_fill */
template<typename T, typename A >
vector<T,A>::vector( const vector<T,A>& a)
      : vector_base<T,A>( a.alloc, a.size())  // allocate space for n elements
{
        std::uninitialized_copy( a.begin(), a.end(), v); /* copy elements with (placement new):
                                                  e g. void construct( pointer p, const T& val) 
                                                  { ::new((void *)p) T( val); } */
}

/* optimized, but just the basic guarantee:
 * in case of exception thrown there'll be no leaks,
 * see safe_assign for strong guarantee */
template<typename T, typename A >
vector<T,A>& vector<T,A>::operator=( const vector& other)
{
    if( capacity() < other.size())  // allocate new vector representation
    {
        vector tmp( other);                          // copy
        std::swap< vector_base<T,A> >( *this, tmp);  // swap representations
        return *this;
    }
    
    /* protect against self-assignment */
    if( this == &other) return *this;
    
    /* assign to old elements */
    size_type sz = size();
    size_type osz = other.size();
    alloc = other.get_allocator();  // copy the allocator
    if( sz >= osz)
    {
        /* size is big enough to hold other representation */
        std::copy( other.begin(), other.begin() + osz, v);  // osz!
        for( T* p = v + osz; p != space; ++p) p->~T(); // destroy surplus elements (up to space)
    }
    else {
        /* we have memory for T initialized up to space ( size = space - v)
         * so use assignment operator on this range */
        std::copy( other.begin(), other.begin() + sz, v);   // sz!
        /* and copy ctor via placement new on the rest */
        std::uninitialized_copy( other.begin() + sz, other.end(), space); // construct extra elements
    }
    
    return *this;
}

/* a copy constructor used to initialize *space might throw.
 * If that happens the vaalue of the vector remains unchanged,
 * with space left unincremented. In that case the vector elements
 * are not reallocated so that iterators referring to them are not
 * invalidated. Thus this implementation implements the strong
 * guarantee that an exception thrown by an allocator or even
 * a user-supplied copy constructor leaves the vector unchanged.
 * The standard library offers that guarantee for push_back.
 */
template<typename T, typename A >
void vector<T,A>::push_back( const T& val)
{
    if( space == last)
    {
        /* no more free space: relocate */
        vector_base<T,A> b( alloc, size()? 2 * size() : 2); // double the allocation
        std::uninitialized_copy( v, space, b.v);       // copy old elements
        new( b.space) T( val);                         // place a copy of val in *b.space: might throw
        ++b.space;                                     // point space to correct place (1 past last element)
        destroy_elements();
        swap<vector_base<T,A> >( b, *this);            // swap representations
        return;
    }
    /* there is a free space */
    new( space) T( val);                               // place a copy of val in *b.space
    ++space;                                           // point space to correct place (1 past last element)
}


/* strong guarantee,
 * does not do spurious copies of elements */
template<typename T, typename A >
void safe_assign1( vector<T,A>& a, const vector<T,A>& b)  // "obvious" a = b
{
    vector<T,A> tmp( a.get_allocator());
    tmp.reserve( b.size());
    for( typename vector<T,A>::iterator p = b.begin(); p != b.end(); ++p) {
        tmp.push_back( *p);
    }
    /* note: swap vectors but swap takes vector_base:
     * slicing will happen and only representations will be swapped */
    swap( a, tmp);
}

/* strong guarantee,
 * does not do spurious copies of elements,
 * let the library perform the copy into temporary for us */
template<typename T, typename A >
void safe_assign2( vector<T,A>& a, const vector<T,A>& b)  // "obvious" a = b
{
    vector<T,A> tmp( b);
    /* note: swap vectors but swap takes vector_base:
     * slicing will happen and only representations will be swapped */
    swap( a, tmp);
}

/* strong guarantee,
 * does not do spurious copies of elements,
 * let the library perform the copy into temporary for us,
 * indeed we could simply use call-by-value */
template<typename T, typename A >
void safe_assign3( vector<T,A>& a, const vector<T,A>& b)  // "obvious" a = b
{
    /* note: swap vectors but swap takes vector_base:
     * slicing will happen and only representations will be swapped */
    swap( a, b);
}
/*
 * 
 */
int main(int argc, char** argv) {

    return 0;
}



